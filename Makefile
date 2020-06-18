EXEC = main
CFILES = main.c Agente.c Mapa.c Lista.c Simulacion.c tools.c
CFILES := $(addprefix Proyecto/,$(CFILES))
HEADERS = Agente.h Mapa.h Lista.h Simulacion.h tools.h
HEADERS := $(addprefix Proyecto/,$(HEADERS))
CC = gcc
COPTIONS = -o $(EXEC) -lncurses -lpthread -lm

all: run clean

$(EXEC): $(CFILES) $(HEADERS)
	$(CC) $(CFILES) $(COPTIONS)

.PHONY: clean ru 

run: $(EXEC) 
	./$(EXEC)

