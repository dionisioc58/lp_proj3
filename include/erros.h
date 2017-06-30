/**
* @file     erros.h
* @brief 	Arquivo com definições de classes de erro
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @author   Airton Neto (netoairton@yahoo.com.br)
* @since    25/06/2017
* @date     29/06/2017
*/

#ifndef ERROS_H
    #define ERROS_H

    #include <stdexcept>
    using std::range_error;
    using std::length_error;
    using std::overflow_error;
    using std::logic_error;
    using std::invalid_argument;
    
    /**
    * @brief Erro de manipulação de arquivos
    **/
    class ErroArquivo : public logic_error {
    public:
        ErroArquivo() : logic_error("Erro na manipulação do arquivo!") {}
    };

    /**
    * @brief Erro de manipulação de arquivos
    **/
    class ArgumentoInvalido : public invalid_argument {
    public:
        ArgumentoInvalido() : invalid_argument("Argumento(s) inválido(s)!") {}
    };

    /**
    * @brief Erro de falta do argumento com o nome do arquivo de exportação
    **/
    class NomeArquivo : public invalid_argument {
    public:
        NomeArquivo() : invalid_argument("Faltando nome do arquivo de exportação!") {}
    };
    
#endif