BIN_DIR := bin
OBJ_DIR := obj
CC := gcc
CC_ARGS := -Wall -Wextra -Werror
INCLUDE := -I.
LINK := gcc
LINK_ARGS := -lflint -lgmp

TARGETS := bin/t-ctx_init.out bin/t-init.out bin/t-reduce.out
SRC := $(shell find n2adic -type f -name '*.c')
OBJ := $(patsubst n2adic/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGETS)
.PHONY: all

run: $(TARGETS)
	./bin/t-ctx_init.out
	./bin/t-init.out
	./bin/t-reduce.out
.PHONY: run

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
.PHONY: clean

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

obj/%.o: n2adic/%.c n2adic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

obj/%.o: test/%.c n2adic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

bin/t-ctx_init.out: obj/t-ctx_init.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-init.out: obj/t-init.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-reduce.out: obj/t-reduce.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)