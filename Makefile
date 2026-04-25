CC = g++
CXXFLAGS = -Wall -Wextra -Iinclude -std=c++17

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin/lunara

all: $(BIN)

# Rule to compile the executable
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

# Rule to compile every src/*.cpp to src/*.o
src/%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f src/*.o $(BIN)
