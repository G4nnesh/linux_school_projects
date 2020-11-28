all : thread1 thread2 thread3 thread4


thread1 : thread1.c
	gcc thread1.c -Wall -o $@ -lpthread

thread2 : thread2.c
	gcc thread2.c -Wall -o $@ -lpthread

thread3 : thread3.c
	gcc thread3.c -Wall -o $@ -lpthread

thread4 : thread4.c
	gcc thread4.c -Wall -o $@ -lpthread
	
	
clean :
	rm -f thread1 thread2 thread3 thread4
