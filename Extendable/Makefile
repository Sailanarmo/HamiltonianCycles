OBJS1 = parallelDriver.cpp
OBJS2 = serialDriver.cpp

CC = g++
DEBUG_FLAGS = -O0 -g3 -fsanitize=thread
RELEASE_FLAGS = -O3 -g0
FLAGS = -std=c++14 -Wall -Wextra

parallel: $(OBJS1)
	g++ $(RELEASE_FLAGS) $(FLAGS) -pthread $(OBJS1) -o notExtendableParallel.out

parallelDebug: $(OBJS1)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS1) -o parallelDebug.out

serial: $(OBJS2)
	$(CC) $(RELEASE_FLAGS) $(FLAGS) $(OBJS2) -o notExtendableSerial.out

serialDebug: $(OBJS2)
	$(CC) $(DEBUG_FLAGS) $(FLAGS) $(OBJS2) -o serialDebug.out

clean:
	rm *.out

all: $(OBJS)
	make parallel serial
