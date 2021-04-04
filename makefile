all:main
#cosas que no tienen archivos
.PHONY:all clean
#directorios
SRC  = src
INCL    = include

SRC_NAMES = block game tetrominoe
SRC_O = $(SRC_NAMES:%=$(SRC)/%.o)

#Compilador
CC = g++

#opciones de compilacion
CCFLAGS = -Wall -I$(INCL) -g

main.o: main.cpp 
	$(CC) $(CCFLAGS) -c $< -o $@

$(SRC)/%.o: $(SRC)/%.cpp $(INCL)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

main: main.o $(SRC_O) -lSDL2
