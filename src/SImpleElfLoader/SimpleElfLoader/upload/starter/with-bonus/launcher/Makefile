all: /home/angad/OS_ASSIGNMENTS/ASSIGNMENT-1-MODIFIVE/upload/starter/with-bonus/bin/launch

/home/angad/OS_ASSIGNMENTS/ASSIGNMENT-1-MODIFIVE/upload/starter/with-bonus/bin/launch: launch.c /home/angad/OS_ASSIGNMENTS/ASSIGNMENT-1-MODIFIVE/upload/starter/with-bonus/bin/lib_simpleloader.so
	gcc -m32 -o $@ $< -I../loader -L/home/angad/OS_ASSIGNMENTS/ASSIGNMENT-1-MODIFIVE/upload/starter/with-bonus/bin -Wl,-rpath,'/home/angad/OS_ASSIGNMENTS/ASSIGNMENT-1-MODIFIVE/upload/starter/with-bonus/bin'lib_simpleloader.so

clean:
	-rm -f /home/angad/OS_ASSIGNMENTS/ASSIGNMENT-1-MODIFIVE/upload/starter/with-bonus/bin/launch
