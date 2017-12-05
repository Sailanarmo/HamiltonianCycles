OBJS = cycleFinder.cpp 
OBJS2 = notExtendable1.cpp

CC = g++
DEBUG_FLAGS = -O0 -g3 -fsanitize=address
RELEASE_FLAGS = -O3 -g0
FLAGS = -std=c++14 -Wall -Wextra

release: $(OBJS)
	$(CC) $(RELEASE_FLAGS) $(FLAGS) $(OBJS) -o cycle.out

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS) -o debug.out

ext: $(OBJS2)
	g++ $(DEBUG_FLAGS) $(FLAGS) -pthread $(OBJS2) -o ext.out

clean:
	rm *.out

all: $(OBJS)
	make release debug
