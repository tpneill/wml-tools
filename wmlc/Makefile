OBJS = wmlc.o

all: wmlc

re: clean all

.c.o:
	$(CC) $(CC_OPS) $(XML_CC_OPS) -c $*.c

wmlc: $(OBJS)
	$(CC) $(CC_OPS) $(XML_CC_OPS) -o wmlc $(OBJS) $(LD_OPS) $(XML_LD_OPS)

clean:
	rm -f $(OBJS) wmlc core *~
