CXX = g++
CXXFLAGS = -Wall -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
EXEC = vm

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS) -lncurses

clean:
	rm -rf $(OBJ) $(EXEC)