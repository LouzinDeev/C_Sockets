all:
	gcc client/main.c WSASock.c -lWs2_32 -o client
	gcc server/*.c WSASock.c -lWs2_32 -o server

