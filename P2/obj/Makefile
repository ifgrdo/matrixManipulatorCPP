CC := g++
CCFLAGS := -std=c++14
INCLUDE := ../src

VPATH = ../../exercicio41/src:../../exercicio43/src:../serie_problemas
SOURCES := $(wildcard ../../exercicio41/src/*.cpp ../../exercicio43/src/*.cpp ../serie_problemas/*.cpp)
OBJECTS := $(notdir $(SOURCES:.cpp=.o))

#####################################################

all: ../bin/main

../bin/main: $(OBJECTS)
	@echo $(OBJECTS)
	$(CC) -o $@ $^ -I $(INCLUDE) 

#--- Now every .cpp file can easily be found from VPATH !
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $^ -I $(INCLUDE) 
run:
	../bin/main

clean:
	rm *.o ../bin/main


