#include <iostream>
#include <string>
#include "circuito.h"

using namespace std;


//PORTA


Porta::Porta(unsigned int NI)
{
}
Porta::Porta(const Porta&)
{
}
void Porta::setSaida(bool_3S s)
{
}
int Porta::getId_in(unsigned int i) const
{
}
void Porta::setId_in(unsigned int i, int N)
{
}
void Porta::digitar()
{
}
bool Porta::ler(istream& I)
{
}
ostream &Porta::imprimir(ostream &O) const
{
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
}
bool_3S Porta_NOT::simular(const bool_3S [] in)
{
}


//PORTA_AND


ostream &Porta_AND::imprimir(ostream& O) const
{
}
bool_3S Porta_AND::simular(const bool_3S [] in)
{
}


//PORTA_NAND


ostream &Porta_NAND::imprimir(ostream& O) const
{
}
bool_3S Porta_NAND::simular(const bool_3S [] in)
{
}


//PORTA_OR


ostream &Porta_OR::imprimir(ostream& O) const
{
}
bool_3S Porta_OR::simular(const bool_3S [] in)
{
}


//PORTA_NOR


ostream &Porta_NOR::imprimir(ostream& O) const
{
}
bool_3S Porta_NOR::simular(const bool_3S [] in)
{
}


//PORTA_XOR


ostream &Porta_XOR::imprimir(ostream& O) const
{
}
bool_3S Porta_XOR::simular(const bool_3S [] in)
{
}


//PORTA_NXOR


ostream &Porta_NXOR::imprimir(ostream& O) const
{
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











