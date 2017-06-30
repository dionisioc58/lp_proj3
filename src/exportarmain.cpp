/**
* @file   main.cpp
* @brief 	Arquivo fonte para execução do projeto
* @author Dionísio Carvalho (dionisio@naracosta.com.br)
* @author Airton Neto (netoairton@yahoo.com.br)
* @since	25/04/2017
* @date	  29/06/2017
*/

#include <iostream>
#include <string>
#include <getopt.h>
#include <map>
using std::cout;
using std::cerr;
using std::endl;
using std::map;
using std::string;

#include "bancodados.h"
using namespace qlevetudo;

/**
* @brief      Função principal do programa
* @param[in]	argc	Quantidade de argumentos
* @param[in]  *argv[]	Argumento com o caminho/nome do arquivo de dados a ser lido
* @return	  	Retorno
*/
int main(int argc, char* argv[]) {
    static struct option long_options[] = {
        {"full", no_argument, 0, 'l'},
        {0, 0, 0, 0}
    };
    int tflag = 0, fflag = 0, lflag = 0;
    char *tvalue = NULL, *fvalue = NULL;
    int index, c, conta = 0;

    opterr = 0;
    while ((c = getopt_long(argc, argv, "t:f:", long_options, &index)) != -1) {
        switch (c) {
        case 't':
            tflag = 1;
            tvalue = optarg;
            conta += 2;
            break;
        case 'f':
            fflag = 1;            
            fvalue = optarg;
            conta += 2;
            break;
        case 'l':
            lflag = 1;
            conta++;
            break;
        case '?':
            if ((optopt == 't') || (optopt == 'f'))
                cerr << "Opção -" << char(optopt) << " requer um argumento." << endl;
            else if(optopt == 'l')
                cerr << "Opção --full requer um argumento." << endl;
            else if (isprint (optopt))
                cerr << "Opção desconhecida -" << char(c) <<  endl;
            else
                cerr << "Caractere de opção desconhecido " << char(optopt) << endl;
            return 1;
        default:
            abort();
        }
    }

    try {
        if((lflag == 1) && (tflag == 0)) //Argumentos --full sem -t
            throw ArgumentoInvalido();
        if(conta >= (argc - 1))
            throw NomeArquivo();
        map<string, Fornecedor*> forns;                         /**< Cadastro com map<CNPJ, Fornecedor> */
        abrirBD("./data/banco.dat", forns, false);              /**< Recuperar o cadastro a partir de um arquivo */
        exportarBD(argv[argc - 1], forns, (tflag == 1 ? tvalue : ""), (fflag == 1 ? fvalue : ""), lflag);       /**< Exportar com as opções selecionadas */
        //Liberar a memória
        for(auto &lista : forns)
            delete lista.second;
    } catch (ArgumentoInvalido &ex) {  
        cerr << ex.what() << endl;
        return 1;
    } catch (NomeArquivo &ex) {
        cerr << ex.what() << endl;
        return 1;
    }
    return 0;
}