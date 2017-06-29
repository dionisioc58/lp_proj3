#Makefile for "Projeto 3 de LP 1" C++ aplication
#Created by Dionísio Carvalho & Airton Neto

# Comandos do sistema operacional
# Linux: rm -rf
# Windows: cmd //C del
RM = rm -rf

# Compilador
CC = g++

# Variaveis para os subdiretorios
BIN_DIR = ./bin
OBJ_DIR = ./build
DOC_DIR = ./doc
INC_DIR = ./include
SRC_DIR = ./src
LIB_DIR = ./lib

# Opcoes de compilacao
CFLAGS = -Wall -pedantic -ansi -std=c++11 -I $(INC_DIR)
ARCHIVE = ar
# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean distclean doxy

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
linux: qlevetudo.so prog_dinamico

windows: qlevetudo.dll prog_dinamico.exe
debug: CFLAGS += -g -O0
debug: clean prog_dinamico prog_dinamico.exe


qlevetudo.so: $(SRC_DIR)/main.cpp $(SRC_DIR)/fornecedor.cpp $(SRC_DIR)/produto.cpp $(SRC_DIR)/pereciveis.cpp $(SRC_DIR)/npereciveis.cpp $(SRC_DIR)/venda.cpp $(SRC_DIR)/menu.cpp $(SRC_DIR)/bancodados.cpp $(SRC_DIR)/funcoes.cpp $(INC_DIR)/fornecedor.h $(INC_DIR)/produto.h $(INC_DIR)/subproduto.h $(INC_DIR)/venda.h $(INC_DIR)/menu.h $(INC_DIR)/bancodados.h $(INC_DIR)/funcoes.h
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/fornecedor.cpp -o $(OBJ_DIR)/fornecedor.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/produto.cpp -o $(OBJ_DIR)/produto.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/pereciveis.cpp -o $(OBJ_DIR)/pereciveis.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/npereciveis.cpp -o $(OBJ_DIR)/npereciveis.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/venda.cpp -o $(OBJ_DIR)/venda.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/menu.cpp -o $(OBJ_DIR)/menu.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/bancodados.cpp -o $(OBJ_DIR)/bancodados.o
	$(CC) $(CFLAGS) -fPIC -c $(SRC_DIR)/funcoes.cpp -o $(OBJ_DIR)/funcoes.o
	$(CC) -shared -fPIC -o $(LIB_DIR)/$@ $(OBJ_DIR)/fornecedor.o $(OBJ_DIR)/produto.o $(OBJ_DIR)/pereciveis.o $(OBJ_DIR)/npereciveis.o $(OBJ_DIR)/venda.o $(OBJ_DIR)/bancodados.o $(OBJ_DIR)/funcoes.o $(OBJ_DIR)/menu.o
	@echo "+++ [Biblioteca dinamica criada em $(LIB_DIR)/$@] +++"

prog_dinamico:
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp $(LIB_DIR)/qlevetudo.so -o $(BIN_DIR)/$@

qlevetudo.dll: $(SRC_DIR)/main.cpp $(SRC_DIR)/fornecedor.cpp $(SRC_DIR)/produto.cpp $(SRC_DIR)/pereciveis.cpp $(SRC_DIR)/npereciveis.cpp $(SRC_DIR)/venda.cpp $(SRC_DIR)/menu.cpp $(SRC_DIR)/bancodados.cpp $(SRC_DIR)/funcoes.cpp $(INC_DIR)/fornecedor.h $(INC_DIR)/produto.h $(INC_DIR)/subproduto.h $(INC_DIR)/venda.h $(INC_DIR)/menu.h $(INC_DIR)/bancodados.h $(INC_DIR)/funcoes.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/fornecedor.cpp -o $(OBJ_DIR)/fornecedor.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/produto.cpp -o $(OBJ_DIR)/produto.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pereciveis.cpp -o $(OBJ_DIR)/pereciveis.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/npereciveis.cpp -o $(OBJ_DIR)/npereciveis.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/venda.cpp -o $(OBJ_DIR)/venda.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/menu.cpp -o $(OBJ_DIR)/menu.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/bancodados.cpp -o $(OBJ_DIR)/bancodados.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/funcoes.cpp -o $(OBJ_DIR)/funcoes.o
	$(CC) -shared -o $(LIB_DIR)/$@ $(OBJ_DIR)/fornecedor.o $(OBJ_DIR)/produto.o $(OBJ_DIR)/pereciveis.o $(OBJ_DIR)/npereciveis.o $(OBJ_DIR)/venda.o $(OBJ_DIR)/bancodados.o $(OBJ_DIR)/funcoes.o $(OBJ_DIR)/menu.o
	@echo "+++ [Biblioteca dinamica criada em $(LIB_DIR)/$@] +++"

prog_dinamico.exe:
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp $(LIB_DIR)/qlevetudo.dll -o $(BIN_DIR)/$@


# Alvo (target) para a geração automatica de documentacao usando o Doxygen.
# Sempre remove a documentacao anterior (caso exista) e gera uma nova.
doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos binarios/executaveis.
clean:
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
