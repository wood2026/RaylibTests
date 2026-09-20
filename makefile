CC = gcc
WINDRES = windres

TARGET = game

CFLAGS = -IC:/raylib/raylib/src
LDFLAGS = -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

$(TARGET).exe: test001.c resources.o
	$(CC) test001.c resources.o -o $(TARGET).exe $(CFLAGS) $(LDFLAGS)

resources.o: resources.rc icon.ico
	$(WINDRES) resources.rc -O coff -o resources.o

run: $(TARGET).exe
	./$(TARGET).exe

clean:
	rm -f $(TARGET).exe resources.o