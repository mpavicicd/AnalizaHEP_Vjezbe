CC=g++
CFLAGS=-I.
DEPS = ElementaryParticle.h Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

analyzer: analyze.o ElementaryParticle.o Analyzer.o
	$(CC) -o analyzer analyze.o ElementaryParticle.o Analyzer.o

clean:
	rm -rf *.o analyzer