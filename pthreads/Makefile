.PHONY: default

LIBS := -lpthread

default: stress

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

stress: stress.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
