CC = gcc

GIBBY = src/gibby.c
SERVER = src/server/server.c
CLIENT = src/client/client.c 

ERROR_HANDLER = src/error_handler.c

FLAGS = -pthread -Wall -Wextra

all:
	$(CC) -I include $(FLAGS) $(GIBBY) $(SERVER) $(CLIENT) $(ERROR_HANDLER) -o build/gib

clean:
	rm -rf build