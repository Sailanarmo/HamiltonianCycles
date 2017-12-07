OBJS1 = parallelDriver.cpp
OBJS2 = serialDriver.cpp 

CC = g++
DEBUG_FLAGS = -O0 -g3 -fsanitize=address
RELEASE_FLAGS = -O3 -g0
FLAGS = -std=c++14 -Wall -Wextra

parallel: $(OBJS1)
	g++ $(RELEASE_FLAGS) $(FLAGS) -pthread $(OBJS2) -o notExtendable.out

parallelDebug: $(OBJS1)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS) -o debug.out

serial: $(OBJS2)
	$(CC) $(RELEASE_FLAGS) $(FLAGS) $(OBJS2) -o cycle.out

serialDebug: $(OBJS2)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS2) -o debug.out

clean:
	rm *.out

all: $(OBJS)
	make release debug
