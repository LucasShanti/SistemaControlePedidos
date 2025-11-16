# ============================================================
# Makefile — Sistema de Controle de Pedidos (SCP)
# Projeto em C com múltiplos módulos e interface ncurses
# ============================================================
# === CONFIGURAÇÕES GERAIS ===
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LIBS = lib/pdcurses.a
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
EXEC = $(BUILD_DIR)/scp
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
# ============================================================
# REGRAS PRINCIPAIS
# ============================================================
all: dirs $(EXEC)
	@echo "Compilação concluída com sucesso!"
dirs:
	@if not exist build mkdir build
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC) lib/pdcurses.a -mconsole
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(BUILD_DIR)
	@echo "Limpeza concluída."
run: all
	@echo "Executando o Sistema de Controle de Pedidos..."
	@$(EXEC)
help:
	@echo "Comandos disponíveis:"
	@echo " make → compila o projeto"
	@echo " make run → compila e executa"
	@echo " make clean → remove arquivos compilados"
	@echo " make help → mostra esta ajuda"
.PHONY: all clean run help dirs