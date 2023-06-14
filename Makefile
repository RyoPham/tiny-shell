SOURCE_DIR = ./src
SOURCES = $(SOURCE_DIR)/main.c \
	  $(SOURCE_DIR)/run.c \
	  $(SOURCE_DIR)/commands1.c \
	  $(SOURCE_DIR)/commands2.c
INCLUDES = -I ./include

OBJS = $(SOURCES:.c=.o)

TARGET = shell

.PHONY: build clean

build: $(OBJS)
	gcc $(INCLUDES) $(OBJS) -o $(TARGET).out

%.o: %.c
	gcc $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SOURCE_DIR)/*.o $(TARGET).out
