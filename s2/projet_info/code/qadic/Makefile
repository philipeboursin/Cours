BIN_DIR := bin
OBJ_DIR := obj
CC := gcc
CC_ARGS := -Wall -Wextra -Werror
INCLUDE := -I.
LINK := gcc
LINK_ARGS := -lflint -lgmp

TARGETS := bin/t-ctx_init.out bin/t-init.out bin/t-reduce.out
SRC := $(shell find qadic -type f -name '*.c')
OBJ := $(patsubst qadic/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGETS)
.PHONY: all

run: $(TARGETS)
	./bin/t-ctx_init
	./bin/t-init
	./bin/t-reduce
.PHONY: run

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
.PHONY: clean

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

obj/%.o: qadic/%.c qadic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

obj/%.o: test/%.c qadic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

bin/t-ctx_init.out: obj/t-ctx_init.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@.out $^ $(LINK_ARGS)

bin/t-init.out: obj/t-init.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@.out $^ $(LINK_ARGS)

bin/t-reduce.out: obj/t-reduce.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@.out $^ $(LINK_ARGS)
