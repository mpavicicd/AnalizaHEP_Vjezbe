CC=g++
CFLAGS=-I.
DEPS = ElementaryParticle.h
OBJ = analyzer.o ElementaryParticle.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyzer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm *.o