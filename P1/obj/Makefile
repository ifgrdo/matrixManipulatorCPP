CC := g++
CCFLAGS := -std=c++14
INCLUDE := ../src

ROOT_FLAGS := $(shell echo $$(root-config --cflags --libs) )
ROOT_FLAGS := $(shell echo $(ROOT_FLAGS) | sed 's/-std=c++11//;s/-stdlib=libc++//g' )

VPATH = ../src:../serie_problemas
SOURCES := $(wildcard ../src/*.cpp ../serie_problemas/*.cpp)
OBJECTS := $(notdir $(SOURCES:.cpp=.o))

#####################################################

all: ../bin/main

../bin/main: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) -o $@ $^ -I $(INCLUDE) $(ROOT_FLAGS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ -I $(INCLUDE) $(ROOT_FLAGS)

run:
	../bin/main

clean:
	rm *.o ../bin/main