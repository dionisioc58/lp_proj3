/**
* @file 	bancodados.h
* @brief	Arquivo de cabeçalho com a definição de funções para o controle dos dados
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @author   Airton Neto (netoairton@yahoo.com.br)
* @since	30/05/2017
* @date	    29/06/2017
*/

#ifndef BANCODADOS_H
    #define BANCODADOS_H

    #include <iostream>
    #include <map>
    using std::cin;
    using std::cout;
    using std::endl;
    using std::map;

    #include <fstream>
    using std::ifstream;
    using std::ofstream;

    #include <string>
    using std::string;

    #include <sstream>
    
    #include "fornecedor.h"
    #include "produto.h"
    #include "subproduto.h"
    #include "venda.h"
    #include "funcoes.h"
    #include "menu.h"

/**
* @brief        Função que coleta os dados para o cadastro de um fornecedor
* @return       Fornecedor coletado
*/
Fornecedor *inputFornecedor();

/**
* @brief        Função que coleta os dados para cadastro de um produto
* @param[in]    *f Fornecedor que vai receber o produto
* @return       Produto coletado
*/
void inputProduto(Fornecedor *f);

/**
* @brief        Função que realiza o cadastro um Fornecedor
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void cadFornecedor(map<string, Fornecedor*> &forns);

/**
* @brief        Função que remove uma Fornecedor do cadastro
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void delFornecedor(map<string, Fornecedor*> &forns);

/**
* @brief        Função que adiciona um produto à um fornecedor (apresenta escolha)
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void addPr(map<string, Fornecedor*> &forns);

/**
* @brief        Função que remove um produto de um fornecedor (apresenta escolha)
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void delPr(map<string, Fornecedor*> &forns);

/**
* @brief        Função que edita um produto de um Fornecedor (apresenta escolha)
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void editPr(map<string, Fornecedor*> &forns);

/**
* @brief        Função que imprime os objetos na lista
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[in]    pausa True para apresentar uma pausa após a impressão
*/
void impLista(map<string, Fornecedor*> forns, bool pausa);

/**
* @brief        Função que imprime a lista de produtos de um ou todos
                os fornecedores do cadastro
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[in]    all "true" imprime todos os produtos de todos os fornecedores
                "false" imprime apenas os produtos de um fornecedor (apresenta escolha)
* @param[in]    pausa True para apresentar uma pausa após a impressão
* @return       "" ou o CNPJ do fornecedor selecionado
*/
string impPr(map<string, Fornecedor*> forns, bool all = true, bool pausa = true);

/**
* @brief        Função que imprime um produto
* @param[in]    *p Produto
* @param[in]    detalhes True para apresentar os detalhes do produto
*/
void imprimir(Produto *p, bool detalhes = true);

/**
* @brief        Função que imprime a lista de produtos
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[in]    filtro Filtro de listagem (0 = sem filtro, 1 = filtrar por tipo, 
*               2 = filtrar por codigo, 3 = exibir menos detalhes)
* @param[in]    pausa True para apresentar uma pausa após a impressão
* @return       -1 ou o número do fornecedor selecionada
*/
int impPrLista(map<string, Fornecedor*> forns, int filtro = 0, bool pausa = true);

/**
* @brief        Função que salva o cadastro completo em arquivo
* @param[in]    nome Caminho/nome do arquivo de dados
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void salvarBD(string nome, map<string, Fornecedor*> &forns);

/**
* @brief        Função que recupera o cadastro completo a partir de um arquivo
* @param[in]    nome Caminho/nome do arquivo de dados
* @param[inout] forns Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
*/
void abrirBD(string nome, map<string, Fornecedor*> &forns);

/**
* @brief        Função que exibe uma mensagem para manter a tela congelada
*/
void parar();

/**
* @brief        Função que exibe uma mensagem e uma lista numerada para a escolha de um fornecedor
* @param[inout] forn Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[in]    msg Mensagem à exibir
*/
string selecionaFornecedor(map<string, Fornecedor*> forn, string msg);

/**
* @brief        Função que exibe uma mensagem e uma lista numerada para a escolha de um produto
* @param[inout] prod Lista de Produtos à exibir (código, Produto*)
* @param[in]    msg Mensagem à exibir
*/
string selecionaProduto(map<string, Produto*> prod, string msg);

/**
* @brief        Função que exibe opções para realizar uma venda
* @param[inout] forn Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[inout] v Lista de Venda com seus itens (código, Venda*)
*/
void venda(map<string, Fornecedor*> forn, map<string, Venda*> &v);

/**
* @brief        Função que adiciona um produto à venda
* @param[inout] forn Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[inout] v Lista de Venda com seus itens (código, Venda*)
*/
void venda_add(map<string, Fornecedor*> forn, map<string, Venda*> &v);

/**
* @brief        Função que exibe os produtos adicionados à venda
* @param[in]    pausa True para manter a tela congelada após a impressão
* @param[inout] v Lista de Venda com seus itens (código, Venda*)
*/
void venda_lis(map<string, Venda*> v, bool pausa = true);

/**
* @brief        Função que remove um produto da venda
* @param[inout] v Lista de Venda com seus itens (código, Venda*)
*/
void venda_del(map<string, Venda*> &v);

/**
* @brief        Função para encerrar a venda
* @param[inout] v Lista de Venda com seus itens (código, Venda*)
*/
void venda_enc(map<string, Venda*> &v);

/**
* @brief        Função que imprime a lista de estoque
* @param[inout] forn Lista de Fornecedores do cadastro (cnpj, Fornecedor*)
* @param[in]    pausa True para apresentar uma pausa após a impressão
* @return       -1 ou o número do fornecedor selecionada
*/
int impPrListaEstoque(map<string, Fornecedor*> forn, bool pausa = true);

#endif