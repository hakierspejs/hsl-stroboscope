SRC := main.c
OBJ := $(SRC:.c=.o)
EXE := hsl-stroboscope

$(EXE): $(OBJ)
	gcc $(OBJ) -o $(EXE) -Wall `pkg-config --cflags --libs SDL2_image`

main.o: main.c
	gcc main.c -c -o main.o -Wall `pkg-config --cflags --libs SDL2_image`

clean:
	rm -f $(EXE) $(OBJ)

