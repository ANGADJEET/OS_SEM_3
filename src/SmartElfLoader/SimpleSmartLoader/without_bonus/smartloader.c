#include "loader.h"

Elf32_Ehdr *ehdr;
Elf32_Phdr *phdr;
int fd;
#define PAGE_SIZE 4096 // 4KB
int page_faults = 0;
int pages_used = 0;
size_t fragmentation = 0;

void clean_phdr()
{
    if (phdr != NULL)
    {
        for (int i = 0; i < ehdr->e_phnum; i++)
        {
            if (phdr[i].p_type == PT_LOAD)
            {
                void *mem = (void *)(phdr[i].p_vaddr);
                size_t memsz = phdr[i].p_memsz;
                munmap(mem, memsz);
            }
        }
        free(phdr);
        phdr = NULL;
    }
}

void clean_ehdr()
{
    if (ehdr != NULL)
    {
        free(ehdr);
        ehdr = NULL;
    }
}
void close_fd()
{
    if (fd != -1)
    {
        close(fd);
        fd = -1;
    }
}

void loader_cleanup()
{
    printf("------------------------------------------------------\n");
    printf("Starting cleaning resources...\n");

    clean_phdr();
    clean_ehdr();
    close_fd();

    printf("All resources cleaned up.\n");
    printf("------------------------------------------------------\n");
}

size_t calculate_fragmentation(Elf32_Phdr *phdr, int num_pages)
{
    size_t total_size = num_pages * PAGE_SIZE;
    size_t allocated_size = phdr->p_memsz;
    size_t fragmentation = total_size - allocated_size;
    return fragmentation;
}

void print_details(int pages_used, int page_faults, size_t fragmentation)
{
    printf("Pages used: %d\n", pages_used);
    printf("Page faults: %d\n", page_faults);
    printf("Fragmentation: %zu bytes\n", fragmentation);
}

void custom_handler(int signum, siginfo_t *info, void *context)
{
    printf("------------------------------------------------------\n");
    printf("Page fault caught (SIGSEGV)-->Invoking custom handler\n");
    printf("Address Causing SegFault: %p\n", info->si_addr);

    // Identify the segment containing that address
    uintptr_t addr = (uintptr_t)info->si_addr;
    int num_pages;
    size_t current_fragmentation = 0;

    for (int i = 0; i < ehdr->e_phnum; i++)
    {
        if (addr >= phdr[i].p_vaddr && addr <= phdr[i].p_vaddr + phdr[i].p_memsz)
        {
            if (phdr[i].p_memsz % PAGE_SIZE == 0)
            {
                num_pages = phdr[i].p_memsz / PAGE_SIZE;
            }
            else
            {
                num_pages = phdr[i].p_memsz / PAGE_SIZE + 1;
            }

            void *mem = mmap((void *)phdr[i].p_vaddr, num_pages * PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

            if (mem == MAP_FAILED)
            {
                perror("mmap failed for program headers");
                printf("Error: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            current_fragmentation = calculate_fragmentation(&phdr[i], num_pages);
            fragmentation += current_fragmentation;

            printf("Size of the segment: %d\n", phdr[i].p_memsz);
            printf("Number of pages: %d\n", num_pages);
            printf("Memory allocated at: %p\n", mem);
            printf("Fragmentation: %zu\n", current_fragmentation);

            lseek(fd, phdr[i].p_offset, SEEK_SET);
            read(fd, mem, phdr[i].p_filesz);
        }
    }

    pages_used += num_pages;
    page_faults++;
    print_details(pages_used, page_faults, fragmentation);
    printf("------------------------------------------------------\n");
}

void check_heapoverflow_ehdr(Elf32_Ehdr *ehdr)
{
    if (ehdr == NULL)
    {
        printf("Malloc failure, condition of heap overflow!\n");
        exit(EXIT_FAILURE);
    }
}

void check_heapoverflow_phdr(Elf32_Phdr *phdr)
{
    if (phdr == NULL)
    {
        printf("Malloc failure, condition of heap overflow!\n");
        exit(EXIT_FAILURE);
    }
}

void allocate_memory_ehdr()
{
    ehdr = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));
}

void allocate_memory_phdr()
{
    phdr = malloc(ehdr->e_phnum * sizeof(Elf32_Phdr));
}

void load_and_run_elf(char **exe)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = custom_handler;

    sigaction(SIGSEGV, &sa, NULL);

    printf("------------------------------------------------------\n");
    printf("Opening ELF file: %s\n", exe[1]);
    fd = open(exe[1], O_RDONLY);

    if (fd < 0)
    {
        printf("Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("Opened the ELF file successfully.\n");
    allocate_memory_ehdr();
    check_heapoverflow_ehdr(ehdr);
    printf("Allocated memory for ELF header.\n");

    if (read(fd, ehdr, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
    {
        printf("Failed to read ELF header.\n");
        exit(EXIT_FAILURE);
    }

    printf("Successfully read ELF header.\n");
    allocate_memory_phdr();

    int lseek_result = lseek(fd, ehdr->e_phoff, SEEK_SET);
    if (lseek_result == -1)
    {
        perror("lseek failed for program headers");
        exit(EXIT_FAILURE);
    }
    if (read(fd, phdr, sizeof(Elf32_Phdr) * ehdr->e_phnum) != sizeof(Elf32_Phdr) * ehdr->e_phnum)
    {
        printf("Failed to read program headers.\n");
        exit(EXIT_FAILURE);
    }

    check_heapoverflow_phdr(phdr);

    printf("Allocated memory for program headers.\n");

    lseek_result = lseek(fd, ehdr->e_phoff, SEEK_SET);
    if (lseek_result == -1)
    {
        perror("lseek failed for program headers");
        exit(EXIT_FAILURE);
    }

    int (*_start)(void) = (int (*)(void))ehdr->e_entry;
    int result = _start();

    printf("Return value of _start: %d\n", result);
    if (result == -1)
    {
        printf("Can't execute _start.\n");
    }
    printf("Final values--->\n");
    print_details(pages_used, page_faults, fragmentation);
    printf("Total Fragmentation (in KB): %.2f KB\n", (double)fragmentation / 1024.0);

    printf("------------------------------------------------------\n");
}

bool check_elf_file(const char *filename)
{
    FILE *file_name = fopen(filename, "rb");
    uint8_t magic_number[4] = {0x7F, 'E', 'L', 'F'};
    uint8_t Starting_bits[4];

    fread(Starting_bits, sizeof(uint8_t), 4, file_name);
    fclose(file_name);

    if (memcmp(Starting_bits, magic_number, sizeof(magic_number)) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <ELF Executable>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argv[1] == NULL)
    {
        printf("Wrong file\n");
        exit(EXIT_FAILURE);
    }

    printf("------------------------------------------------------\n");
    printf("Loading and running ELF file: %s\n", argv[1]);

    if (!check_elf_file(argv[1]))
    {
        fprintf(stderr, "The provided file is not in ELF format.\n");
        exit(EXIT_FAILURE);
    }

    load_and_run_elf(argv);
    loader_cleanup();

    return 0;
}
