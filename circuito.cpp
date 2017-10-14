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
}
bool Porta::ler(istream& I)
{
    unsigned temp(0); //mostra a quantidade de entradas que já foram lidas
    //Nin
    I.ignore(numeric_limits<streamsize>::max(), ' ');
    I >> Nin;
    do
    {
        I.ignore(numeric_limits<streamsize>::max(), ' ');
        I >> id_in[temp];
        temp++;        
    } while((temp<4) && ()); //para de ler ao chegar no num max de entradas ou quando chega no \n
    
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
bool_3S Porta_NOT::simular(const bool_3S [] in)
{
}


//PORTA_AND


ostream &Porta_AND::imprimir(ostream& O) const
{
    O << "AN ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_AND::simular(const bool_3S [] in)
{
}


//PORTA_NAND


ostream &Porta_NAND::imprimir(ostream& O) const
{
    O << "NA ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NAND::simular(const bool_3S [] in)
{
}


//PORTA_OR


ostream &Porta_OR::imprimir(ostream& O) const
{
    O << "OR ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_OR::simular(const bool_3S [] in)
{
}


//PORTA_NOR


ostream &Porta_NOR::imprimir(ostream& O) const
{
    O << "NO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOR::simular(const bool_3S [] in)
{
}


//PORTA_XOR


ostream &Porta_XOR::imprimir(ostream& O) const
{
    O << "XO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_XOR::simular(const bool_3S [] in)
{
}


//PORTA_NXOR


ostream &Porta_NXOR::imprimir(ostream& O) const
{
    O << "NX ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NXOR::simular(const bool_3S [] in)
{
}


//CIRCUITO 


void Circuito::limpar()
{
}
void Circuito::alocar(unsigned int NI, unsigned int NO, unsigned int NP)
{
}
void Circuito::copiar(const Circuito& C)
{
}
void Circuito::digitar()
{
}
void Circuito::ler(const char*)
{
}
ostream &Circuito::imprimir(ostream& O) const
{
}
void Circuito::salvar(const char*) const
{
}
void Circuito::digitarEntradas()
{
}
void Circuito::imprimirEntradas() const
{
}
void Circuito::imprimirSaidas() const
{
}
void Circuito::simular()
{
}
void Circuito::gerarTabela()
{
}











