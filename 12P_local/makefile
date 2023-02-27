CC = g++
DEBUG = -g
EXECUTABLE = mynetwork
SOURCES = mynetwork.cpp


all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(DEBUG) $< -o $@ 
	
clean:
	rm -f $(EXECUTABLE)
	