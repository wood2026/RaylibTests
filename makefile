CC = gcc
TARGET = game
CFLAGS = -IC:/raylib/raylib/src
LDFLAGS = -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

$(TARGET).exe: test001.c
	$(CC) test001.c -o $(TARGET).exe $(CFLAGS) $(LDFLAGS)

run: $(TARGET).exe
	./$(TARGET).exe

clean:
	rm -f $(TARGET).exe