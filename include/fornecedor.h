/**
 * @file	fornecedor.h
 * @brief	Definição da classe Fornecedor
 * @author	Dionísio Carvalho (dionisio@naracosta.com.br)
 * @author  Airton Neto (netoairton@yahoo.com.br)
 * @since	30/05/2017
 * @date	29/06/2017
 */

#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <map>
using std::string;
using std::endl;
using std::map;

#include "produto.h"
#include "subproduto.h"
namespace qlevetudo{
/**
    * @class   Fornecedor fornecedor.h
    * @brief   Classe que representa um Fornecedor
    * @details Os atributos da QLeveTudo são: RSocial, CNPJ
    */  
    class Fornecedor {
        private:
            string RSocial;                                     /**< Razao social */
            string CNPJ;                                        /**< CNPJ */
            map<string, Produto*> produtos;                     /**< Lista de produtos (codigo, produto) */
    public:
        Fornecedor();                                           /**< Construtor padrão */
        ~Fornecedor();                                          /**< Destrutor padrão */
        
        string getRSocial();                                    /**< Retorna o RSocial */
        void setRSocial(string n);                              /**< Modifica o RSocial */

        string getCNPJ();                                       /**< Retorna o CNPJ */
        void setCNPJ(string c);                                 /**< Modifica o CNPJ */
        
        int getQtde();                                          /**< Retorna a quantidade de Produtos */
        
        map<string, Produto*> getProdutos();                    /**< Retorna a lista de Produtos */
        void setProdutos(map<string, Produto*> p);              /**< Modifica a lista de Produtos */
        
        bool addProduto(Produto *p);                            /**< Adiciona um Produto */
        bool delProduto(string cod);                            /**< Remove um Produto */
        
        bool pertenceFornecedor(string n);                      /**< Verifica se um codigo de barra pertence à lista de Produto */
        
        string exportar(bool vazio = true, string tp = "", bool full = true);      /**< Retorna uma string com os dados para exportação CSV */
        bool operator>(Fornecedor &p);                          /** @brief Sobrecarga do operador de comparação > */
        bool operator!=(Fornecedor &f);                         /** @brief Sobrecarga do operador de comparação != */
		friend ostream& operator<<(ostream& os, Fornecedor &f); /** @brief Sobrecarga do operador de extração em stream */
		friend istream& operator>>(istream& is, Fornecedor &f); /** @brief Sobrecarga do operador de inserção de stream */
    };
}
#endif