/**
* @file 	bancodados.cpp
* @brief	Arquivo de corpo com a definição de funções para o controle dos dados
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @author	Eduardo Rique (luiseduardorique@gmail.com)
* @since    30/05/2017
* @date     30/05/2017
*/

#include "bancodados.h"

#define qtde_tipos 8                 /**< Quantidade de opções de tipos no menu */

string tipos_prods[qtde_tipos] = {
    "Bebida",   //1  - ok
    "Fruta",    //2  - ok
    "Doce",     //3  - ok
    "Salgado",  //4  - ok
    "CD",       //5  - ok
    "DVD",      //6  - ok
    "Livro",    //7  - ok
    "(Cancelar)"
};                /**< Opções de tipos de produtos */

/**
* @brief        Função que coleta os dados para o cadastro de um fornecedor
* @return       Fornecedor coletado
*/
Fornecedor *inputFornecedor() {
    string input;
    Fornecedor *novo = new Fornecedor();

    cout << "Digite a razão social do fornecedor: ";
    getline(cin, input);
    novo->setRSocial(input);

    cout << "Digite o CNPJ do fornecedor: ";
    getline(cin, input);
    novo->setCNPJ(input);

    return novo;
}

/**
* @brief        Função que coleta os dados para cadastro de um produto
* @param[in]    *f Fornecedor que vai receber o produto
* @return       Produto coletado
*/
void inputProduto(Fornecedor *f) {
    //Coleta dados do produto
    //cout << "Digite o tipo do produto: ";
    //getline(cin, input);
    int selecao = showMenu("Selecione um tipo de produto", tipos_prods, qtde_tipos);
    if(selecao <= 0)
        return;
    string tipo = tipos_prods[--selecao];
    minusculas(tipo);
    Produto *novo;

    if(tipo == "bebida") {
        novo = new Bebida();
        novo->capturar();
        dynamic_cast<Bebida*>(novo)->capturar();
    }
    if(tipo == "fruta") {
        novo = new Fruta();
        novo->capturar();
        dynamic_cast<Fruta*>(novo)->capturar();
    }
    if(tipo == "doce") {
        novo = new Doce();
        novo->capturar();
        dynamic_cast<Doce*>(novo)->capturar();
    }
    if(tipo == "salgado") {
        novo = new Salgado();
        novo->capturar();
        dynamic_cast<Salgado*>(novo)->capturar();
    }
    if(tipo == "cd") {
        novo = new CD();
        novo->capturar();
        dynamic_cast<CD*>(novo)->capturar();
    }
    if(tipo == "dvd") {
        novo = new DVD();
        novo->capturar();
        dynamic_cast<DVD*>(novo)->capturar();
    }
    if(tipo == "livro") {
        novo = new Livro();
        novo->capturar();
        dynamic_cast<Livro*>(novo)->capturar();
    }
    if(!f->addProduto(novo))
        cout << "Produto já cadastrado" << endl;
    else
        cout << "Cadastro realizado com sucesso!" << endl;
    parar();        
}

/**
* @brief        Função que realiza o cadastro um Fornecedor
* @param[in]    *e Lista de Fornecedores do cadastro
*/
void cadFornecedor(map<string, Fornecedor*> &forns) {
    Fornecedor *novo = inputFornecedor();
    map<string, Fornecedor*>::iterator it = forns.find(novo->getCNPJ());
    if(it != forns.end()) {
        cout << "Fornecedor já cadastrado" << endl;
        parar();
    } else
        forns[novo->getCNPJ()] = novo;    
}

/**
* @brief        Função que remove uma Fornecedor do cadastro
* @param[in]    *e Lista de Fornecedores do cadastro
*/
void delFornecedor(map<string, Fornecedor*> &forns) {
    string cnpj = selecionaFornecedor(forns, "Digite o CNPJ do fornecedor para a remoção (0 para cancelar): ");
    if(cnpj != "@@") { //@@ = sinal de cancelar operação
        map<string, Fornecedor*>::iterator it = forns.find(cnpj);
        if(it != forns.end())
            forns.erase(it);
        else
            cout << "CNPJ não encontrado!" << endl;
    }
}

/**
* @brief        Função que adiciona um produto à um fornecedor (apresenta escolha)
* @param[in]    *e Lista de fornecedores do cadastro
*/
void addPr(map<string, Fornecedor*> &forns) {
    string cnpj = selecionaFornecedor(forns, "Digite o CNPJ do fornecedor para a adição (0 para cancelar): ");
    if(cnpj != "@@") {   //@@ = cancelar
        map<string, Fornecedor*>::iterator it = forns.find(cnpj);
        if(it != forns.end()) {
            inputProduto(it->second);
            cout << "Produto adicionado com sucesso!" << endl;
        } else
            cout << "CNPJ não encontrado!" << endl;
    }
}

/**
* @brief        Função que remove um produto de um fornecedor (apresenta escolha)
* @param[in]    *e Lista de fornecedores do cadastro
*/
void delPr(map<string, Fornecedor*> &forns) {
    string cnpj = selecionaFornecedor(forns, "Digite o CNPJ do fornecedor para a adição (0 para cancelar): ");
    if(cnpj != "@@") {   //@@ = cancelar
        map<string, Fornecedor*>::iterator it = forns.find(cnpj);
        if(it != forns.end()) {
            map<string, Produto*> f = dynamic_cast<Fornecedor*>(it->second)->getProdutos();
            int i = 0;
            for(auto &lista : f) {
                cout << "   (" << ++i << ") ";
                imprimir(dynamic_cast<Produto*>(lista.second));
            }
            string selecao = recebeString("Digite o código do produto para a remoção (0 para cancelar): ");
            map<string, Produto*>::iterator it2 = f.find(selecao);
            if(it2 != f.end())
                dynamic_cast<Fornecedor*>(it->second)->delProduto(selecao);
            else
                cout << "Código não encontrado!" << endl;
        } else
            cout << "CNPJ não encontrado!" << endl;
    }
}

/**
* @brief        Função que edita um produto de um Fornecedor (apresenta escolha)
* @param[in]    *e Lista de Fornecedores do cadastro
*/
void editPr(map<string, Fornecedor*> &forns) {
    string cnpj = selecionaFornecedor(forns, "Digite o CNPJ do fornecedor para a adição (0 para cancelar): ");
    if(cnpj != "@@") {   //@@ = cancelar
        map<string, Fornecedor*>::iterator it = forns.find(cnpj);
        if(it != forns.end()) {
            Fornecedor *f = it->second;
            map<string, Produto*> prods = f->getProdutos();
            string cod = selecionaProduto(prods, "Selecione o código do produto para a edição (0 para cancelar): ");
            if(cod != "@@") {
                map<string, Produto*>::iterator pr = prods.find(cod);
                if(pr != prods.end()) {
                    Produto *p = pr->second;
                    
                    string input;
                    
                    cout << "O código é: " << p->getCb() << " (ENTER para manter): ";
                    getline(cin, input);
                    if(input != "")
                        p->setCb(input);

                    cout << "A descrição é: " << p->getDescricao() << " (ENTER para manter): ";
                    getline(cin, input);
                    if(input != "")
                        p->setDescricao(input);

                    cout << "O tipo é: " << p->getTipo() << " (ENTER para manter): ";
                    getline(cin, input);
                    if(input != "")
                        p->setTipo(input);

                    stringstream ss;
                    ss << "O preço é: " << p->getPreco() << " (0 para manter): ";
                    input = ss.str();
                    float preco = recebeFloat(input, 0);
                    if(preco > 0)
                        p->setPreco(preco);

                    ss.clear();
                    ss << "A quantidade é: " << p->getQtde() << " (0 para manter): ";
                    input = ss.str();
                    float qtde = recebeInt(input, 0);
                    if(qtde > 0)
                        p->setQtde(qtde);
                } else
                    cout << "Código não encontrado!" << endl;
            }
        } else
            cout << "CNPJ não encontrado!" << endl;
    }
}

/**
* @brief        Função que imprime os objetos na lista
* @param[in]    *e Lista de objetos
* @param[in]    pausa True para apresentar uma pausa após a impressão
*/
void impLista(map<string, Fornecedor*> forns, bool pausa) {
    for(auto &lista : forns)
        cout << *lista.second << endl;
    if(pausa)
        parar();
}

/**
* @brief        Função que imprime a lista de produtos de um ou todos
                os fornecedores do cadastro
* @param[in]    *e Lista de fornecedores do cadastro
* @param[in]    all "true" imprime todos os produtos de todos os fornecedores
                "false" imprime apenas os produtos de um fornecedor (apresenta escolha)
* @param[in]    pausa True para apresentar uma pausa após a impressão
* @return       -1 ou o número do fornecedor selecionado
*/
string impPr(map<string, Fornecedor*> forns, bool all, bool pausa) {
    if(!all) {      //Imprime todos os produtos de um fornecedor
        string cnpj = selecionaFornecedor(forns, "Digite o CNPJ do fornecedor para a adição (0 para cancelar): ");
        if(cnpj != "@@") {   //@@ = cancelar
            map<string, Fornecedor*>::iterator it = forns.find(cnpj);
            if(it != forns.end()) {
                if(dynamic_cast<Fornecedor*>(it->second)->getQtde() > 0) {
                    cout << "Produtos do fornecedor " << dynamic_cast<Fornecedor*>(it->second)->getRSocial() << endl;
                    map<string, Produto*> prods = dynamic_cast<Fornecedor*>(it->second)->getProdutos();
                    int i = 0;
                    for(auto &lista : prods) {
                        cout << "   (" << ++i << ") ";
                        imprimir(dynamic_cast<Produto*>(lista.second));
                        cout << endl;
                        cout << "______________________________________________" << endl;
                    }
                } else
                    cout << "Nenhum produto no fornecedor selecionado." << endl;
                
                if(pausa)
                    parar();
            } else
                cout << "CNPJ não encontrado!" << endl;
        }
        return cnpj;
    } else {        //Imprime todos os produtos de todos os fornecedores
        for(auto &lista : forns) {
            cout << "Produtos do fornecedor " << dynamic_cast<Fornecedor*>(lista.second)->getRSocial() << endl;
            map<string, Produto*> f = dynamic_cast<Fornecedor*>(lista.second)->getProdutos();
            int i = 0;
            for(auto &lista2 : f) {
                cout << "   (" << ++i << ") ";
                imprimir(dynamic_cast<Produto*>(lista2.second));
                cout << endl;
                cout << "______________________________________________" << endl;
            }
        }

        /*Lista<Fornecedor> *tmp = e->getProximo();
        while(tmp) {
            cout << "Produtos do fornecedor " << tmp->getValor()->getRSocial() << endl;
            Lista<Produto*> f = *(tmp->getValor())->getProdutos();
            Produto *produt;
            for(int i = 0; i < tmp->getValor()->getQtde(); i++) {
                f = *f.getProximo();
                produt = *f.getValor();
                cout << "   (" << (i + 1) << ") ";
                imprimir(produt);
                cout << endl;
                cout << "______________________________________________" << endl;
            }
            tmp = tmp->getProximo();
        }*/
    }
        
    if(pausa)
        parar();
    return "";

}

/**
* @brief        Função que imprime um produto
* @param[in]    *p Produto
* @param[in]    detalhes True para apresentar os detalhes do produto
*/
void imprimir(Produto *p, bool detalhes) {
    string tipo = p->getTipo();
    minusculas(tipo);
    if(detalhes) {
        if(tipo == "bebida")
            cout << *dynamic_cast<Bebida*>(p);
        else if(tipo == "fruta")
            cout << *dynamic_cast<Fruta*>(p);
        else if(tipo == "doce")
            cout << *dynamic_cast<Doce*>(p);
        else if(tipo == "salgado")
            cout << *dynamic_cast<Salgado*>(p);
        else if(tipo == "cd")
            cout << *dynamic_cast<CD*>(p);
        else if(tipo == "dvd")
            cout << *dynamic_cast<DVD*>(p);
        else if(tipo == "livro")
            cout << *dynamic_cast<Livro*>(p);
        else
            cout << *dynamic_cast<Produto*>(p);
    } else
        cout << *p;
}

/**
* @brief        Função que imprime a lista de produtos
* @param[inout] *e Lista de Fornecedores do cadastro
* @param[in]    filtro Filtro de listagem (0 = sem filtro, 1 = filtrar por tipo, 
*               2 = filtrar por codigo, 3 = exibir menos detalhes)
* @param[in]    pausa True para apresentar uma pausa após a impressão
* @return       -1 ou o número do fornecedor selecionada
*/
int impPrLista(map<string, Fornecedor*> forns, int filtro, bool pausa) {
    string ftipo = "", fcod = "";
    if(filtro == 1) {
        int selecao = showMenu("Selecione um tipo de produto", tipos_prods, qtde_tipos);
        if(selecao <= 0)
            return -1;
        ftipo = tipos_prods[--selecao];
        minusculas(ftipo);
    }
    if(filtro == 2) {
        cout << "Digite o código que você quer procurar: ";
        getline(cin, fcod);
    }
    
    int j = 0;
    for(auto &lista : forns) {
        map<string, Produto*> f = dynamic_cast<Fornecedor*>(lista.second)->getProdutos();
        for(auto &lista2 : f) {
            Produto *produt = dynamic_cast<Produto*>(lista2.second);
            string tip = produt->getTipo();
            minusculas(tip);
            switch(filtro) {
                case 1:
                    if(tip == ftipo) {
                        cout << "   (" << ++j << ") ";
                        imprimir(produt);
                        cout << endl;
                        cout << "______________________________________________" << endl;
                    }
                    break;
                case 2:
                    if(produt->getCb() == fcod) {
                        cout << "   (" << ++j << ") ";
                        imprimir(produt);
                        cout << endl;
                        cout << "______________________________________________" << endl;
                    }
                    break;
                case 3:
                    cout << "   (" << ++j << ") ";
                    imprimir(produt, false);
                    cout << endl;
                    cout << "______________________________________________" << endl;
                    break;
                default:
                    cout << "   (" << ++j << ") ";
                    imprimir(produt);
                    cout << endl;
                    cout << "______________________________________________" << endl;
            }
        }
    }
        
    if(pausa)
        parar();
    return j;
}

/**
* @brief        Função que salva o cadastro completo em arquivo
* @param[in]    nome Caminho/nome do arquivo de dados
* @param[in]    *e Lista de fornecedores do cadastro
*/
void salvarBD(string nome, map<string, Fornecedor*> &forns) {
    ofstream saida(nome);
    if(!saida) {
        cout << "Não foi possível abrir o arquivo para salvar." << endl;
        return;
    }
    for(auto &lista : forns)
        saida << dynamic_cast<Fornecedor*>(lista.second)->exportar() << endl;

    saida.close();
    cout << "Banco de dados salvo com sucesso!" << endl;
}

/**
* @brief        Função que recupera o cadastro completo a partir de um arquivo
* @param[in]    nome Caminho/nome do arquivo de dados
* @param[in]    *e Lista de Fornecedores do cadastro
*/
void abrirBD(string nome, map<string, Fornecedor*> &forns) {
    ifstream entrada(nome);
    if(!entrada) {
        cout << "Não foi possível abrir o arquivo de dados." << endl;
        return;
    }
    string texto;
    stringstream info, detalhe;
    bool tem_forn = false;
    Fornecedor *tmp;
    
    int conta1 = 0, conta2 = 0;
    entrada.clear();
    entrada.seekg(0);
    Produto *pp;
    
    while(!entrada.eof()) {
        getline(entrada, texto);
        if(texto != "") {
            info.clear();
            info << texto;
            
            if(texto.substr(0, 7) == "fornec;") {
                tmp = new Fornecedor();
                string tipo;
                getline(info, tipo, ';');
                info >> *tmp;
                forns[tmp->getCNPJ()] = tmp;
                tem_forn = true;
                conta1++;
            }

            if(texto.substr(0, 7) == "produt;") {
                if(tem_forn) {
                    string tipo;
                    getline(info, tipo, ';');
                    getline(info, tipo, ';');
                    minusculas(tipo);
                    if(tipo == "bebida") {
                        pp = new Bebida();
                        info >> *dynamic_cast<Bebida*>(pp);
                    } else if(tipo == "fruta") {
                        pp = new Fruta();
                        info >> *dynamic_cast<Fruta*>(pp);
                    } else if(tipo == "doce") {
                        pp = new Doce();
                        info >> *dynamic_cast<Doce*>(pp);
                    } else if(tipo == "salgado") {
                        pp = new Salgado();
                        info >> *dynamic_cast<Salgado*>(pp);
                    } else if(tipo == "cd") {
                        pp = new CD();
                        info >> *dynamic_cast<CD*>(pp);
                    } else if(tipo == "dvd") {
                        pp = new DVD();
                        info >> *dynamic_cast<DVD*>(pp);
                    } else if(tipo == "livro") {
                        pp = new Livro();
                        info >> *dynamic_cast<Livro*>(pp);
                    } else
                        info >> *pp;
                    tmp->addProduto(pp);
                    forns[tmp->getCNPJ()] = tmp;
                    conta2++;
                }
            }
        }
    }
    entrada.close();
    cout << "Banco de dados aberto com sucesso!" << endl;
    cout << conta1 << " fornecedores e " << conta2 << " produtos encontrados." << endl;
}

/**
* @brief        Função que exibe uma mensagem para manter a tela congelada
*/
void parar() {
    cin.clear();
    fflush(stdin);
    cout << "Pressione ENTER para continuar...";
    string p;
    getline(cin, p);
}

/**
* @brief        Função que exibe uma mensagem e uma lista numerada para a escolha de um objeto
* @param[in]    *e Lista de objeto
* @param[in]    msg Mensagem à exibir
*/
string selecionaFornecedor(map<string, Fornecedor*> forn, string msg) {
    for(auto &item : forn)
        cout << "CNPJ: " << item.first << " " << *item.second << endl;
    
    string selecao = recebeString(msg);
    if(selecao == "0")
        return "@@";

    return selecao;
}

/**
* @brief        Função que exibe uma mensagem e uma lista numerada para a escolha de um objeto
* @param[in]    *e Lista de objeto
* @param[in]    msg Mensagem à exibir
*/
string selecionaProduto(map<string, Produto*> prod, string msg) {
    for(auto &item : prod)
        cout << *item.second << endl;
    
    string selecao = recebeString(msg);
    if(selecao == "0")
        return "@@";

    return selecao;
}

#define qtde_vendas 5                 /**< Quantidade de opções de tipos no menu */

string opcoes_vendas[qtde_vendas] = {
    "Adicionar um produto",   //1  - ok
    "Remover um produto",    //2  - ok
    "Listar os produtos",     //3  - ok
    "Encerrar a venda",  //4  - ok
    "(Voltar ao menu)"       //5  - ok
};                /**< Opções de tipos de produtos */

/**
* @brief        Função que exibe opções para realizar uma venda
* @param[in]    *e Lista de fornecedores com seus produtos
* @param[in]    *v Lista de venda com seus itens
*/
void venda(map<string, Fornecedor*> forn, map<string, Venda*> &v) {
    while(1) {
        switch(showMenu("Venda de Produtos", opcoes_vendas, qtde_vendas)) {
            case 0: //Voltar ao menu
                return;
                break;
            case 1: //Adicionar um produto
                venda_add(forn, v);
                break;
            case 2: //Remover um produto
                venda_del(v);
                break;
            case 3: //Listar os produtos
                venda_lis(v);
                break;
            case 4: //Encerrar a venda
                venda_enc(v);
                break;
        }
    }
}

/**
* @brief        Função que adiciona um produto à venda
* @param[in]    *e Lista de fornecedores com seus produtos
* @param[in]    *v Lista de venda com seus itens
*/
void venda_add(map<string, Fornecedor*> forn, map<string, Venda*> &v) {
    //Lista todos os itens do cadastro
    int maximo = impPrLista(forn, 3, false);
    if(maximo == -1)
        return;
    //Seleciona um deles
    map<string, Produto*> prods;
    string cod = recebeString("Digite o código do produto para a adição (0 para cancelar): ");
    if(cod != "0") {
        map<string, Produto*>::iterator pr;
        for(auto &lista : forn) {
            prods = dynamic_cast<Fornecedor*>(lista.second)->getProdutos();
            pr = prods.find(cod);
            if(pr != prods.end())
                break;
        }
        if(!pr->second) {
            cout << "Código não encontrado!" << endl;
            return;
        }
        Venda *nova = new Venda();
        nova->setProduto(pr->second);

        int qtd = recebeInt("Digite a quantidade: ", 1, prods.size());
        nova->setQtde(qtd);
        
        v[nova->getProduto()->getCb()] = nova;
    }
}

/**
* @brief        Função que exibe os produtos adicionados à venda
* @param[in]    pausa True para manter a tela congelada após a impressão
* @param[in]    *v Lista de venda com seus itens
*/
void venda_lis(map<string, Venda*> v, bool pausa) {
    cout << "Nº  Código" << string(4, ' ') << "\t|Descrição" << string(22, ' ') << "\t|Qtde  " << "\t|Total" << endl;
    int i = 1;
    for(auto &lista : v)
        cout << i++ << "   " << *dynamic_cast<Venda*>(lista.second) << endl;

    if(pausa)
        parar();
}

/**
* @brief        Função que remove um produto da venda
* @param[in]    *v Lista de venda com seus itens
*/
void venda_del(map<string, Venda*> &v) {
    venda_lis(v, false);
    string cod = recebeString("Digite o código do produto para a remoção: ");
    map<string, Venda*>::iterator it = v.find(cod);
    if(it != v.end()) {
        v.erase(it);
    }
}

/**
* @brief        Função para encerrar a venda
* @param[in]    *v Lista de venda com seus itens
*/
void venda_enc(map<string, Venda*> &v) {
    if(v.size() == 0)
        return;

    venda_lis(v, false);
    float total = 0;
    for(auto &lista : v)
        total += (dynamic_cast<Venda*>(lista.second)->getProduto()->getPreco() * dynamic_cast<Venda*>(lista.second)->getQtde());

    cout << "_____________________________________" << endl;
    cout << "Total da compra: " << total << endl;
    cout << "_____________________________________" << endl << endl;
    parar();

    string sim_nao[2] = {"Sim", "Não"};
    int ret = showMenu("Encerrar a venda?", sim_nao, 2);
    if(ret == 0) //Escolheu 'não'
        return;

    for(auto &lista : v) {
        Produto *p = dynamic_cast<Venda*>(lista.second)->getProduto();
        p->setQtde(p->getQtde() - dynamic_cast<Venda*>(lista.second)->getQtde());
    }

    v.clear();
}

/**
* @brief        Função que imprime a lista de estoque
* @param[inout] *e Lista de Fornecedores do cadastro
* @param[in]    pausa True para apresentar uma pausa após a impressão
* @return       -1 ou o número do fornecedor selecionada
*/
int impPrListaEstoque(map<string, Fornecedor*> forn, bool pausa) {
    bool primeiro = true;
    for(auto &lista : forn) {
        if(primeiro) {
            cout << endl;
            cout << "  Código" << string(4, ' ') << "\t|Descrição" << string(21, ' ') << "\t|Quantidade" << endl;
            primeiro = false;
        }
        map<string, Produto*> f = dynamic_cast<Fornecedor*>(lista.second)->getProdutos();
        
        for(auto &lista2 : f)
            cout << "  " << dynamic_cast<Produto*>(lista2.second)->getEstoque() << endl;
    }
    
    cout << endl;
    
    if(pausa)
        parar();
    return -1;

}