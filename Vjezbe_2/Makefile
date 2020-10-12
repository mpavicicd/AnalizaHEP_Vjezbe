CC=g++
CFLAGS=-I.
DEPS = ElementaryParticle.h

%.o: %.cpp $(DEPS)
	$(CC) -cpp -o $@ $< $(CFLAGS)

all: analyzer.o ElementaryParticle.o
	$(CC) -o analyzer.exe analyzer.o ElementaryParticle.o
clean:
	rm *.exe