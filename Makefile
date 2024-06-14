CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion
LDFLAGS = -L. -lpthread

SRCS = board.cpp catan.cpp player.cpp startgame.cpp
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = test_catan.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

INCLUDES = board.hpp catan.hpp player.hpp doctest.h

all: startgame test_catan

startgame: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_catan: $(TEST_OBJS) board.o catan.o player.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run test valgrind

run: startgame
	./startgame

test: test_catan
	./test_catan

valgrind: startgame
	valgrind --leak-check=full --track-origins=yes ./startgame

clean:
	rm -f $(OBJS) $(TEST_OBJS) startgame test_catan
