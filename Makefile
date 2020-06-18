EXEC = main
CFILES = main.c Agente.c Mapa.c Lista.c Simulacion.c tools.c
CFILES := $(CFILES)
HEADERS = Agente.h Mapa.h Lista.h Simulacion.h tools.h
HEADERS := $(HEADERS)
CC = gcc
COPTIONS = -o $(EXEC) -w -lncurses -lpthread -lm

$(EXEC): $(CFILES) $(HEADERS)
	$(CC) $(CFILES) $(COPTIONS)

.PHONY: clean run

run: $(EXEC)

