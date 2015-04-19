EXEC = bubble
CC = g++
CFLAGS = -Wall
DEBUGFLAGS = -g
SRC = example.cpp $(wildcard cmd/*.cpp)
OBJS = $(SRC:.cpp=.o)

all: $(EXEC)

debug: CFLAGS += $(DEBUGFLAGS)
debug: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(OBJS)
