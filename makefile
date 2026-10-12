CC = gcc

GIBBY = src/gibby.c
SERVER = src/server/server.c
CLIENT = src/client/client.c 

ERROR_HANDLER = src/error_handler.c

all:
	$(CC) -I include $(GIBBY) $(SERVER) $(CLIENT) $(ERROR_HANDLER) -o build/gib

clean:
	rm -rf build