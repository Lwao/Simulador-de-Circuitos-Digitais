#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include "circuito.h"

using namespace std;


//PORTA


Porta::Porta(unsigned int NI)
{
    Nin = NI;
    saida = UNDEF_3S;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=UNDEF_3S;
}
Porta::Porta(const Porta &P)
{
    Nin = P.Nin;
    saida = P.saida;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=P.id_in[i];    
}
void Porta::setSaida(bool_3S s)
{
    if ((s>=-1) && (s<=1)) saida=s;
    else 
    {
        cerr << "Sinal digital inválido!" << endl;
    }
}
int Porta::getId_in(unsigned int i) const
{
    if ((i>0) && (i<NUM_MAX_INPUTS_PORTA)) return id_in[i]=N;
    else 
    {
        cerr << "Número de entradas inválida!" << endl;
        return ;
    }
}
void Porta::setId_in(unsigned int i, int N)
{
    if ((i>0) && (i<NUM_MAX_INPUTS_PORTA)) id_in[i]=N;
    else 
    {
        cerr << "Número de entradas inválida!" << endl;
    }
}
void Porta::digitar()
{
    do
    {
    cout << "Digite o número de entradas da porta: ";
    cin >> Nin;
    } while ((Nin<0) || (Nin>NUM_MAX_INPUTS_PORTA));
    
    
    
    /*
    do
    {
    cout << "Digite a saída da porta: ";
    cin >> saida;
    } while ((saida<-1) || (saida>1));
    
    cout << "Digite o sinal de cada porta: ";
    for (unsigned i=0; i<Nin; i++) 
    {
        cout << "Origem do sinal da entrada " << i+1 << " : ";
        cin >> id_in[i];
    }
    */
}
bool Porta::ler(istream& I)
{
    I.ignore(numeric_limits<streamsize>::max(), ' ');
    I >> Nin;
    for (unsigned i=0; i<Nin; i++)
    {
        I.ignore(numeric_limits<streamsize>::max(), ' ');
        I >> id_in[i];       
    }
    
    return *this;
}
ostream &Porta::imprimir(ostream &O) const
{
    O << Nin << ": ";
    for (unsigned i=0; i<Nin; i++) O << id_in[i] << " ";

    return O;
}


//PORTA_NOT


void Porta_NOT::digitar()
{
    
}
bool Porta_NOT::ler(istream& I)
{
    
}
ostream &Porta_NOT::imprimir(ostream& O) const
{
    O << "NT ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOT::simular(const bool_3S in[])
{
}


//PORTA_AND

void Porta_AND::digitar()
{
}
bool Porta_AND::ler(istream& I)
{
}
ostream &Porta_AND::imprimir(ostream& O) const
{
    O << "AN ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_AND::simular(const bool_3S in[])
{
}


//PORTA_NAND

void Porta_NAND::digitar()
{
}
bool Porta_NAND::ler(istream& I)
{
}
ostream &Porta_NAND::imprimir(ostream& O) const
{
    O << "NA ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NAND::simular(const bool_3S in[])
{
}


//PORTA_OR

void Porta_OR::digitar()
{
}
bool Porta_OR::ler(istream& I)
{
}
ostream &Porta_OR::imprimir(ostream& O) const
{
    O << "OR ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_OR::simular(const bool_3S in[])
{
}


//PORTA_NOR

void Porta_NOR::digitar()
{
}
bool Porta_NOR::ler(istream& I)
{
}
ostream &Porta_NOR::imprimir(ostream& O) const
{
    O << "NO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOR::simular(const bool_3S in[])
{
}


//PORTA_XOR


void Porta_XOR::digitar()
{
}
bool Porta_XOR::ler(istream& I)
{
}
ostream &Porta_XOR::imprimir(ostream& O) const
{
    O << "XO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_XOR::simular(const bool_3S in[])
{
}


//PORTA_NXOR

void Porta_NXOR::digitar()
{
}
bool Porta_NXOR::ler(istream& I)
{
}
ostream &Porta_NXOR::imprimir(ostream& O) const
{
    O << "NX ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NXOR::simular(const bool_3S in[])
{
}


//CIRCUITO 


void Circuito::limpar()
{
    if (inputs!=NULL)
    {
        delete[] inputs;
        inputs = NULL;
    }
    if (id_out!=NULL)
    {
        delete[] id_out;
        id_out = NULL;
    }
    if (portas!=NULL)
    {
        for (unsigned i=0; i<Nportas; i++) delete portas[i];
        delete[] portas;
        portas = NULL;
    }
    Nin = 0;
    Nout = 0;
    Nportas = 0;
}
void Circuito::alocar(unsigned int NI, unsigned int NO, unsigned int NP)
{
    limpar();
    
    Nin = NI;
    Nout = NO;
    Nportas = NP;
    
    inputs = new bool_3S[Nin];
    id_out = new int[Nout];
    portas = new ptr_Porta[Nportas];
}
void Circuito::copiar(const Circuito& C)
{
    limpar();
    alocar(C.Nin, C.Nout, C.Nportas);
    
    for (unsigned i=0; i<Nin; i++) inputs[i]=C.inputs[i];
    for (unsigned i=0; i<Nout; i++) id_out[i]=C.id_out[i];
    for (unsigned i=0; i<Nportas; i++) portas[i] = C.portas[i]->clone();
}
void Circuito::digitar()
{
    int op;
    
    do 
    {
        cout << "Digite o número de entradas do circuito: ";
        cin >> Nin;
    } while (Nin<=0);
    do 
    {
        cout << "Digite o número de saídas do circuito: ";
        cin >> Nout;
    } while (Nout<=0);
    do 
    {
        cout << "Digite o número de portas lógicas do circuito: ";
        cin >> Nportas;
    } while (Nportas<=0);
    
    alocar(Nin, Nout, Nportas);
    
    digitarEntradas();
    
    //Definição das portas
    
    for (unsigned i=0; i<Nportas; i++)
    {
        cout << "\nINSERIR UMA PORTA:\n";
        do {
            cout << "0 - Porta NOT\n";
            cout << "1 - Porta AND\n";
            cout << "2 - Porta NAND\n";
            cout << "3 - Porta OR\n";
            cout << "4 - Porta NOR\n";
            cout << "5 - Porta XOR\n";
            cout << "6 - Porta NXOR\n";
            cout << "Qual sua opção? ";
            cin >> op;
        } while(op<0 || op>7);
        
        switch (op)
        {
            case 0:
                portas[i]->digitar();
                break;
            case 1:
                Porta_AND::digitar();
                break;
            case 2:
                Porta_NAND::digitar();
                break;
            case 3:
                Porta_OR::digitar();
                break;
            case 4:
                Porta_NOR::digitar();
                break;
            case 5:
                Porta_XOR::digitar();
                break;
            case 6:
                Porta_NXOR::digitar();
                break;
            default:
                break;
        }
    }
    

}
void Circuito::ler(const char*nome)
{
    ifstream arquivo(nome);
    if (arquivo.is_open())
    {
        string prov;

        //Lendo cabeçalho geral
        arquivo >> prov;
        if (prov != "CIRCUITOS:")
        {
            cerr << "Arquivo com cabeçalho principal inválido\n";
        }
        else //Prever erros para a falta de algum dos elementos
        {
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nin;
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nout;
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nportas;
        }
        
        alocar(Nin, Nout, Nportas);
        
        arquivo >> prov;
        if (prov != "PORTAS:")
        {
            cerr << "Arquivo com cabeçalho de portas inválido\n";
        }
        else
        {
            for (unsigned i=0; i<Nportas; i++)
            {
                arquivo >> prov;
                portas[i]->ler(arquivo);
            }
        }
        
        arquivo >> prov;
        if (prov != "SAIDAS:")
        {
            cerr << "Arquivo com cabeçalho de saídas inválido\n";
        }
        else
        {
            for (unsigned i=0; i<Nout; i++)
            {
                arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
                arquivo >> id_out[i];
            }
        }
        
        //Fechando arquivo
        arquivo.close();
    }
    else
    {
        cerr << "Erro na abertura do arquivo \"" << nome << "\" para leitura\n";
    }
}
ostream &Circuito::imprimir(ostream& O) const
{
    O << "CIRCUITO: " << Nin << " " << Nout << " " << Nportas << endl;
    O << "PORTAS:" << endl;
    for (unsigned i=0; i<Nportas; i++) 
    {
        O << i+1 << ") ";
        portas[i]->imprimir(O);
        O << endl;
    }
    O << "SAIDAS:" << endl;
    for (unsigned i=0; i<Nout; i++)
    {
        O << i+1 << ") ";
        O << id_out[i] << endl;
    }
    return O;
}
void Circuito::salvar(const char*nome) const
{
    ofstream arquivo(nome);
    //arquivo.is_open();
    if (arquivo.is_open())
    {
        arquivo << imprimir(cout);
        arquivo.close();
    }
    else
    {
      cerr << "Erro na abertura do arquivo \"" << nome << "\" para escrita\n";
    }
}
void Circuito::digitarEntradas()
{
    cout << "Digite os valores lógicos das entradas: " << endl;
    for (unsigned i=0; i<Nin; i++)
    {
        do
        {
            cout << "Valor lógico da entrada " << i+1 << ": ";
            cin >> inputs[i];
        } while ((inputs[i]!=FALSE_3S) || (inputs[i]!=TRUE_3S) || (inputs[i]!=UNDEF_3S));
    }
}
void Circuito::imprimirEntradas() const
{
    cout << "Valores das entradas do circuito: " << endl;
    for (unsigned i=0; i<Nin; i++) cout << "Entrada " << i+1 << " : " << inputs[i] << endl; 
}
void Circuito::imprimirSaidas() const
{
    cout << "Valores das saídas do circuito: " << endl;
    for (unsigned i=0; i<Nout; i++) cout << "Saída " << i+1 << " : " << id_out[i] << endl; 
}
void Circuito::simular()
{
    bool tudo_def, alguma_def, in_portas;
    
    for (unsigned i=0; i<Nportas; i++) portas[i]->saida = UNDEF;
    
    do 
    {
        tudo_def = TRUE_3S;
        alguma_def = FALSE_3S;
        for (unsigned i=0; i<Nportas; i++)
        {
            if (portas[i]->saida == UNDEF_3S)
            {
                in_portas = /*entradas booleanas da porta i;*/ portas[i].simular(in_porta)-;
                if (portas[i].saida == UNDEF_3S)
                {
                    tudo_def = FALSE_3S;
                }
                else
                {
                    alguma_def = true
                }
            }
        }
    } while (!tudo_def && alguma_def)
    
}
void Circuito::gerarTabela()
{    
    for (unsigned i=0; i<Nin; i++) *(inputs[i]) = FALSE_3S;
    
    do
    {
        simular_circuito(inputs);
        
        //Qual input incrementar?
        i = Nin-1;
        while ((i>=0) && (inputs[i]==UNDEF_3S))
        {
            *(inputs[i])=FALSE_3S;
            i--;
        }
        
        //Incrementa a input escolhida
        if (i>=0)
        {
            if (*(inputs[i])==FALSE_3S)
            {
                *(inputs[i])=TRUE_3S;
            }
            else //é true
            {
                *(inputs[i])=UNDEF_3S
            }
        }
    } while (i>=0);
}











