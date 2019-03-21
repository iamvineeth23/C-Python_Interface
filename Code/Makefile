CC = gcc
NP_PATH = $(CONDA_PREFIX)/lib/python3.6/site-packages/numpy/core/include
CFLAGS = -I ${NP_PATH}
SAN_FLAGS = -fsanitize=address
LDFLAGS = -fno-lto
LD_SAN_FLAGS = -static-libasan
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c $(CFLAGS) -o $(TARGET) $(LDFLAGS)  `python3-config --includes --ldflags`

debug:
	$(CC) -g $(TARGET).c $(CFLAGS) $(LDFLAGS) -o $(TARGET) `python3-config --includes --ldflags`
asan:
	$(CC) -g $(TARGET).c $(CFLAGS) $(SAN_FLAGS) -o $(TARGET) $(LDFLAGS) $(LD_SAN_FLAGS) `python3-config --includes --ldflags`

clean:
	$(RM) $(TARGET)

run:
	./$(TARGET)
