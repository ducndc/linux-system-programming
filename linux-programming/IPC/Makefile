all:
	gcc -o 1_pipe.o 1_pipe.c 
	gcc -o 2_pipe_child.o 2_pipe_child.c 
	gcc -o simple_pipe.o simple_pipe.c
	gcc -o 3_pipe_child.o 3_pipe_child.c
	gcc -o 1_write_fifo.o 1_write_fifo.c
	gcc -o 2_read_fifo.o 2_read_fifo.c
	gcc -o 3_write_fifo.o 3_write_fifo.c
	gcc -o 1_sem.o 1_sem.c -lpthread
	gcc -o msg_q_rec.o msg_q_rec.c -lrt
	gcc -o msg_q_send.o msg_q_send.c  -lrt
clean:
	rm -f *.o