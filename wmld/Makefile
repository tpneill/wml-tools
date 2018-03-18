OBJS = wmld.o

all: wmld

re: clean all

.c.o:
	$(CC) $(CC_OPS) -c $*.c

wmld: $(OBJS)
	$(CC) $(CC_OPS) -o wmld $(OBJS)

clean:
	rm -f $(OBJS) wmld core *~
