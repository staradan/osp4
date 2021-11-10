all: Assign4_mon server

client: Assign4_mon.c
	gcc Assign4_mon.c -o Assign4_mon

server: Assign4_sem.c
	gcc Assign4_sem.c -o Assign4_sem