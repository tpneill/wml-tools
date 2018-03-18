OBJS = wmlhtml.o

all: wmlhtml

re: clean all

.c.o:
	$(CC) $(CC_OPS) $(XML_CC_OPS) -c $*.c

wmlhtml: $(OBJS)
	$(CC) $(CC_OPS) $(XML_CC_OPS) -o wmlhtml $(OBJS) $(LD_OPS) $(XML_LD_OPS)

clean:
	rm -f $(OBJS) wmlhtml core *~
