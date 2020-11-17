CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = PDFGenerator.h Analyzer.o

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

PDFGenerator: main.o PDFGenerator.o Analyzer.o
	$(CC) $(LDFLAGS) -o PDFGenerator main.o PDFGenerator.o Analyzer.o

clean:
	rm -rf *.o PDFGenerator