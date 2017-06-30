/**
* @file     main.cpp
* @brief 	Arquivo fonte para execução do projeto
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @author   Airton Neto (netoairton@yahoo.com.br)
* @since	25/04/2017
* @date	    29/06/2017
*/

#include <iostream>
#include <string>
#include <map>
using std::cout;
using std::cerr;
using std::endl;
using std::map;
using std::string;

#include "menu.h"
#include "bancodados.h"
using namespace qlevetudo;
#define qtde 13                 /**< Quantidade de opções no menu */

string opcoes[qtde] = {
    "Cadastrar um fornecedor", //1  - ok
    "Remover um fornecedor", //2  - ok
    "Listar os fornecedores", //3  - ok
    "Cadastrar um produto", //4  - ok
    "Remover um produto", //5  - ok
    "Alterar um produto", //6  - ok
    "Listar todos os produtos por fornecedor", //7  - ok
    "Listar todos os produtos de um fornecedor", //8  - ok
    "Listar produtos por tipo", //9  - ok
    "Listar produtos por codigo", //10 - ok
    "Realizar uma venda", //11
    "Controle de estoque", //12
    "Sair"  //0  - ok
};                /**< Opções do menu */

/**
* @brief        Função principal do programa
* @param[in]	argc	Quantidade de argumentos
* @param[in]    *argv[]	Argumento com o caminho/nome do arquivo de dados a ser lido
* @return		Retorno
*/
int main(int argc, char* argv[]) {
    map<string, Fornecedor*> forns;                         /**< Cadastro com map<CNPJ, Fornecedor> */
    map<string, Venda*> itens;                              /**< Lista de itens da venda */
    
    abrirBD("./data/banco.dat", forns);                     /**< Recuperar o cadastro a partir de um arquivo */

    while(1) {
        switch(showMenu("Q Leve Tudo - A Sua Conveniência", opcoes, qtde)) { //Exibir o menu
            case 0:             //Sair
                cout << endl;
                salvarBD("./data/banco.dat", forns); 
                //Libera memória
                for(auto &lista : forns)
                    delete lista.second;
                for(auto &lista : itens)
                    delete lista.second;
                return 0;

            case 1:              //Cadastrar um fornecedor
                cadFornecedor(forns);
                break;
            case 2:              //Excluir um fornecedor
                delFornecedor(forns);
                break;
            case 3:              //Listar os fornecedores
                impLista(forns, true);
                break;

            case 4:              //Adicionar um produto
                addPr(forns);
                break;
            case 5:              //Excluir um produto
                delPr(forns);
                break;
            case 6:              //Alterar um produto
                editPr(forns);
                break;
            
            case 7:              //Listar todos os produtos de todos os fornecedores
                impPr(forns);
                break;
            case 8:             //Listar todos os produtos de um fornecedor
                impPr(forns, false);
                break;
            case 9:             //Listar produtos por tipo
                impPrLista(forns, 1);
                break;
            case 10:             //Listar produtos por codigo
                impPrLista(forns, 2);
                break;
            
            case 11:            //Realizar uma venda
                venda(forns, itens);              
                break;
            case 12:            //Controle de estoque
                impPrListaEstoque(forns);
                break;
        }
    }
    cout << endl;
    salvarBD("./data/banco.dat", forns); 
    //Libera memória
    for(auto &lista : forns)
        delete lista.second;
    for(auto &lista : itens)
        delete lista.second;
    return 0;
}