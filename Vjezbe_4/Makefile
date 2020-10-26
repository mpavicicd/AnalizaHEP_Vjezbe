CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = ElementaryParticle.h Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyzer: analyze.o ElementaryParticle.o Analyzer.o
	$(CC) $(LDFLAGS) -o analyzer analyze.o ElementaryParticle.o Analyzer.o

clean:
	rm -rf *.o analyzer