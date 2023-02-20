BIN_DIR := bin
OBJ_DIR := obj
CC := gcc
CC_ARGS := -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE := -I.
LINK := gcc
LINK_ARGS := -lflint -lgmp -fsanitize=address

SRC := $(shell find test -type f)
TARGETS := $(SRC:test/%.c=$(BIN_DIR)/%.out) # Contient tous les noms des binaires de chaque test dans bin
SRC := $(shell find zqadic -type f)
OBJ := $(SRC:zqadic/%.c=$(OBJ_DIR)/%.o) # Contient tous les noms des objets de chaque fichier .c dans zqadic


# Pour tout compiler
all: $(TARGETS)
.PHONY: all


# Pour tout compiler et run
run: $(TARGETS)
	for f in $^; do ./$$f; done
.PHONY: run


# Pour tout compiler et chercher les fuites mémoires
memory_check: $(TARGETS)
	for f in $^; do valgrind ./$$f; done
.PHONY: memory_check


# Pour nettoyer les objets et les binaires
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
.PHONY: clean


# Création des dossiers objets et binaires
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


# Création des objets pour les fonctions du module zqadic et les tests
obj/%.o: zqadic/%.c zqadic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

obj/%.o: test/%.c zqadic.h | $(OBJ_DIR)
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<
.PRECIOUS: obj/%.o


# Création des binaires pour les tests
bin/t-%.out: obj/t-%.o $(OBJ) | $(BIN_DIR)
	$(LINK) -o $@ $^ $(LINK_ARGS)
