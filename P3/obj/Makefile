CC := g++
CCFLAGS := -std=c++14
INCLUDE := ../src

#--- VPATH contains the search path for the src files !
VPATH = ../../exercicio41/src:../../exercicio43/src:../../exercicio44/src:../serie_problemas

#--- Now find & list all cpp files on directories
SOURCES := $(wildcard ../../exercicio41/src/*.cpp ../../exercicio43/src/*.cpp ../../exercicio44/src/*.cpp ../serie_problemas/*.cpp)

#--- Object files shouldn’t have the full path of
#--- SOURCES when we replace the .cpp by .o !
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


