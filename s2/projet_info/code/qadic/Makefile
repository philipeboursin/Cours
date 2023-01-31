BIN_DIR := bin
OBJ_DIR := obj
CC := gcc
CC_ARGS := -Wall -Wextra -Werror
INCLUDE := -I.
LINK := gcc
LINK_ARGS := -lflint -lgmp

SRC := $(shell find test -type f)
TARGETS :=  $(SRC:test/%.c=$(BIN_DIR)/%.out)
# TARGETS := bin/t-ctx_init.out bin/t-init.out bin/t-reduce.out bin/t-inv.out bin/t-div_eucl.out bin/t-frobenius_substitution.out bin/t-artin_schreier_root.out
SRC := $(shell find n2adic -type f)
# OBJ := $(patsubst n2adic/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ := $(SRC:n2adic/%.c=$(OBJ_DIR)/%.o)

all: $(TARGETS)
.PHONY: all

run: $(TARGETS)
	for f in $^; do ./$$f; done
.PHONY: run

memory_check: $(TARGETS)
	for f in $^; do valgrind ./$$f; done
.PHONY: memory_check

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
.PHONY: clean

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Création des objets pour les fonctions du module n2adic et des tests
obj/%.o: n2adic/%.c n2adic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

obj/%.o: test/%.c n2adic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

# Création des binaires pour les tests
bin/t-ctx_init.out: obj/t-ctx_init.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-init.out: obj/t-init.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-reduce.out: obj/t-reduce.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-inv.out: obj/t-inv.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-div_eucl.out: obj/t-div_eucl.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-frobenius_substitution.out: obj/t-frobenius_substitution.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

bin/t-artin_schreier_root.out: obj/t-artin_schreier_root.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)

# bin/t-%.out: obj/t-%.o $(OBJ) | $(BIN_DIR)
# 	$(LINK) -o $@ $^ $(LINK_ARGS)