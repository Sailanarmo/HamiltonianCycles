OBJS = main.cpp 
OBJS2 = oldHam.cpp

CC = g++
DEBUG_FLAGS = -O0 -g3 -fsanitize=address
RELEASE_FLAGS = -O3 -g0
FLAGS = -std=c++14 -Wall -Wextra -Werror

oldDebug: $(OBJS2)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS2) -o oldham.out

old: $(OBJS2)
	$(CC) $(RELEASE_FLAGS) $(FLAGS) $(OBJS2) -o oldham.out

release: $(OBJS)
	$(CC) $(RELEASE_FLAGS) $(FLAGS) $(OBJS) -o ham.out

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS) -o debug.out


clean:
	rm *.out

all: $(OBJS)
	make release debug
