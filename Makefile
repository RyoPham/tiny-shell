SOURCE_DIR = ./src
SOURCES = $(SOURCE_DIR)/main.c \
	  $(SOURCE_DIR)/run.c \
	  $(SOURCE_DIR)/commands1.c \
	  $(SOURCE_DIR)/commands2.c \
	  $(SOURCE_DIR)/process.c \
	  $(SOURCE_DIR)/list.c \
	  $(SOURCE_DIR)/help.c
INCLUDES = -I ./include

OBJS = $(SOURCES:.c=.o)

TARGET = shell

.PHONY: build clean run

run: $(TARGET).out
	./$(TARGET).out

build: clean $(TARGET).out

$(TARGET).out: $(SOURCES)
	gcc $(INCLUDES) $(SOURCES) -Wall -o $@
	# gcc $(INCLUDES) $(OBJS) -Wall -o $@

%.o: %.c
	gcc $(INCLUDES) -c -Wall $< -o $@

clean:
	rm -f $(TARGET).out
