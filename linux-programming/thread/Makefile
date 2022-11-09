all:
	gcc -o 1_thread_create.o 1_thread_create.c -lpthread
	gcc -o 2_thread_create.o 2_thread_create.c -lpthread
	gcc -o 3_thrjoin.o 3_thrjoin.c -lpthread
	gcc -o 4_thrdetch.o 4_thrdetch.c -lpthread
	gcc -o 1_mut.o 1_mut.c -lpthread
	gcc -o 2_mut.o 2_mut.c -lpthread
	gcc -o 3_mut.o 3_mut.c -lpthread
	gcc -o sig_cond.o sig_cond.c -lpthread

clean:
	rm -f *.o
