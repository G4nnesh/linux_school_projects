all : infini infini_v2 signal1 signal2 signal3 signal4 signal5 signal5b Q18/Synthese

infini : infini.c
	gcc infini.c -o infini
	
infini_v2 : infini_v2.c
	gcc infini_v2.c -o infini_v2
	
signal1 : signal1.c
	gcc -Wall signal1.c -o signal1

signal2 : signal2.c
	gcc -Wall signal2.c -o signal2

signal3 : signal3.c
	gcc -Wall signal3.c -o signal3

signal4 : signal4.c
	gcc -Wall signal4.c -o signal4

signal5 : signal5.c
	gcc -Wall signal5.c -o signal5
	
signal5b : signal5b.c
	gcc -Wall signal5b.c -o signal5b

Q18/Synthese :	Q18/Synthese.c
	gcc -Wall $< -o $@

clean : 
	rm -f infini infini_v2 signal1 signal2 signal3 signal4 signal5 signal5b Q18/Synthese

