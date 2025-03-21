CC=gcc-14
INCDIRS=-I/opt/homebrew/include
LIBDIRS=-L/opt/homebrew/lib
OPT=-O0
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
CFLAGS=-Wall -Wextra $(INCDIRS) $(LIBDIRS) $(OPT)

BINARY=bin

TEST=tests
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))
TEST_OBJS=$(filter-out $(OBJ)/main.o, $(OBJS))

all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BINARY)

$(OBJS): | $(OBJ)

$(OBJ):
	mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/bin: 
	mkdir -p $@

$(TEST)/bin/%: $(TEST)/%.c $(TEST_OBJS) | $(TEST)/bin
	$(CC) $(CFLAGS) -lcriterion $< $(TEST_OBJS) -o $@

test: $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	rm -r obj
	rm -rf $(BINARY)
	rm -r tests/bin
