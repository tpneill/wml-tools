SRC = rdfwml.c

all: rdfwml rdfwml.cgi

re: clean all

rdfwml:
	$(CC) $(CC_OPS) $(XML_CC_OPS) -o rdfwml $(SRC) $(LD_OPS) $(XML_LD_OPS)

rdfwml.cgi:
	$(CC) $(CC_OPS) $(XML_CC_OPS) -DCGI_BIN -o rdfwml.cgi $(SRC) $(LD_OPS) $(XML_LD_OPS)

clean:
	rm -f *.o rdfwml rdfwml.cgi *~
