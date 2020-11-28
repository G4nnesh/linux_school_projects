all : lectRedac1-2_DNOWrite lectRedac1-2_DNORead lectRedac1-2 lectRedac1-1_DNOWrite lectRedac1-1_DNORead lectRedac1-1 lectRedac0 mutexThread1 mutexThread2

mutexThread1 : mutexThread1.c
	gcc -Wall $^ -o $@ -lpthread

mutexThread2 : mutexThread2.c
	gcc -Wall $^ -o $@ -lpthread

lectRedac0 : lectRedac0.c
	gcc -Wall $^ -o $@ -lpthread

lectRedac1-1 : lectRedac1-1.c
	gcc -Wall $^ -o $@ -lpthread

lectRedac1-1_DNORead : lectRedac1-1.c
	gcc -DNOREADER -Wall $^ -o $@ -lpthread

lectRedac1-1_DNOWrite : lectRedac1-1.c
	gcc -DNOWRITER -Wall $^ -o $@ -lpthread

lectRedac1-2 : lectRedac1-2.c
	gcc -Wall $^ -o $@ -lpthread

lectRedac1-2_DNORead : lectRedac1-2.c
	gcc -DNOREADER -Wall $^ -o $@ -lpthread

lectRedac1-2_DNOWrite : lectRedac1-2.c
	gcc -DNOWRITER -Wall $^ -o $@ -lpthread

clean :
	rm -f lectRedac1-2_DNOWrite lectRedac1-2_DNORead lectRedac1-2 lectRedac1-1_DNOWrite lectRedac1-1_DNORead lectRedac0 lectRedac1-1 mutexThread1 mutexThread2
