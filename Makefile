CC=gcc
CFLAGS=-DSTACK_DEBUG -DLLIST_DEBUG
PROGNAME=dsalg
run_args=hello world

.PHONY: link_all make_bin clean run 

link_all : make_bin main linked_list stack
	$(CC) -o bin/$(PROGNAME) bin/*.o 

run: link_all
	./bin/$(PROGNAME)

main : src/main.c 
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o 

stack: box src/ds/linked_list.c
	$(CC) $(CFLAGS) -c src/ds/stack.c -o bin/stack.o

box: src/ds/box.c
	$(CC) $(CFLAGS) -c src/ds/box.c -o bin/box.o

linked_list: make_bin src/ds/linked_list.c
	$(CC) $(CFLAGS) -c src/ds/linked_list.c -o bin/linked_list.o

make_bin:
	mkdir -p bin

clean:
	rm -rf bin/

show_flags:
	echo "current: $(CFLAGS)"
	echo "available : -DLLIST_DEBUG : for debuging linked_list -DSTACK_DEBUG: to debug stack"
