# Nome do executável
TARGET = sig-nails

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wformat=2 -std=c99

# Lista de diretórios do projeto (ignora 'servicoss')
SRC_DIRS := $(filter-out ./servicoss,$(shell find . -type d))

# Encontra todos os .c (exceto da pasta servicoss)
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRC := $(filter-out ./servicoss/%.c,$(SRC))

# Encontra todos os diretórios que possuem headers
INCLUDE_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} \; | sort -u)
CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))

# Gera os objetos correspondentes
OBJS := $(SRC:.c=.o)

# Regra padrão: compilar tudo
all: $(TARGET)

# Linka todos os objetos no executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compila cada .c individualmente
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa os arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Recompila tudo do zero
rebuild: clean all

.PHONY: all clean rebuild