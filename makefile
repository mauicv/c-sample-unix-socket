# build an executable named myprog from myprog.c
server: server.c
	gcc -o serve server.c

client: client.c
	gcc -o client client.c

clean:
	$(RM) serve
	$(RM) client
