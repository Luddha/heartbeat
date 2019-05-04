CC=gcc
CFLAGS=-Iinclude/
DEPS = common.h
OBJDIR=./build/
SRCDIR=./src/
OBJ = $(addprefix $(OBJDIR), heartbeat.o common.o hb_server.o)
BINDIR=./bin/


$(OBJDIR)%.o: $(SRCDIR)%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

heartbeat: $(OBJ)
	$(CC) -o $(BINDIR)heartbeat $(OBJ)

clean:
	rm ./build/*.o
	rm ./bin/*
