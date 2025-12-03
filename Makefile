CC = gcc
CFLAGS = -g -Wall
TARGET = courseproject
SRCS = pl.c act.c main.c
OBJS = $(SRCS:.c=.o)  
DEPS = nec.h
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TARGET) $(OBJS)
