OBJS = wmlv.o

all: wmlv

re: clean all

.c.o:
	$(CC) $(CC_OPS) $(XML_CC_OPS) -c $*.c

wmlv: $(OBJS)
	$(CC) $(CC_OPS) $(XML_CC_OPS) -o wmlv $(OBJS) $(LD_OPS) $(XML_LD_OPS)

clean:
	rm -f $(OBJS) wmlv core *~
