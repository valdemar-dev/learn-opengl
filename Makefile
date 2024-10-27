CC = gcc
CFLAGS = -Wall -I./include
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
SRC = src/main.c src/glad.c src/shaders/sourceReader.c src/shaders/shader.c
OBJ = $(SRC:.c=.o)
TARGET = main
COMPILE_COMMANDS = compile_commands.json

all: $(TARGET) $(COMPILE_COMMANDS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

	@echo "[" > $(COMPILE_COMMANDS)
	@for src in $(SRC); do \
		echo "  {" >> $(COMPILE_COMMANDS); \
		echo "    \"directory\": \"$(shell pwd)\"," >> $(COMPILE_COMMANDS); \
		echo "    \"command\": \"$(CC) $(CFLAGS) -c $$src -o $$src.o\"," >> $(COMPILE_COMMANDS); \
		echo "    \"file\": \"$$src\"" >> $(COMPILE_COMMANDS); \
		echo "  }," >> $(COMPILE_COMMANDS); \
	done
	@sed -i '$$ s/,$$//' $(COMPILE_COMMANDS)
	@echo "]" >> $(COMPILE_COMMANDS)

clean:
	rm -f $(OBJ) $(TARGET) $(COMPILE_COMMANDS)

