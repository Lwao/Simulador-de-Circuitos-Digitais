#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include "circuito.h"

using namespace std;

//OPERADORES
  bool_3S operator~(bool_3S x) //NOT
  {
      //Define as operações lógicas NOT para o tipo bool_3S;
        if(x==TRUE_3S) return FALSE_3S;
	if(x==FALSE_3S) return TRUE_3S;
	if(x==UNDEF_3S) return UNDEF_3S;
  }
  bool_3S operator&(bool_3S x, bool_3S y) //AND
  {
        //Se os dois forem TRUE, retorna TRUE
	if((x==TRUE_3S)&&(y==TRUE_3S)) return TRUE_3S;
	else 
	{
		//Se ao menos um FALSE retorna FALSE
		if((x==FALSE_3S) || (y==FALSE_3S) return FALSE_3S;
		//Retorna UNDEF para os restantes casos
		/*
		x AND 1 - x
		1 AND x - x
		x AND x	- x	
		*/
		else return UNDEF_3S
		//Se erro, repensar
		//if (((x==TRUE_3S)||(x==UNDEF_3S)) && (y==UNDEF_3S)) return UNDEF_3S
	}
  }
  bool_3S operator|(bool_3S x, bool_3S y) //OR
  {
	  //Se um dos dois forem TRUE, retorna TRUE
	  if((x==TRUE_3S)||(y==TRUE_3S)) return TRUE_3S;
	  else
	  {
		//Se ambos forem FALSO, retorna FALSO
		if ((x==FALSE_3S)&&(y==FALSE_3S)) return FALSE_3S;
		//Retorna UNDEF para os restantes casos
		/*
		x OR 0 - x
		0 OR x - x
		x OR x - x
		*/
		else UNDEF_3S;
	  }
  }
  bool_3S operator^(bool_3S x, bool_3S y) //XOR
  {
	  //Diferentes entre si, assumindo ou TRUE ou FALSE, retorna TRUE
	  if(((x==TRUE_3S)&&(y==FALSE_3S))||((x==FALSE_3S)&&(y==TRUE_3S))) return TRUE_3S;
	  else 
	  {
		//Iguais entre si, assumindo ou TRUE ou FALSE, retorna FALSE
		if(((x==TRUE_3S)&&(y==TRUE_3S))||((x==FALSE_3S)&&(y==FALSE_3S))) return FALSE_3S;
		//Retorna UNDEF se tive ao menos um UNDEF
		/*
		x XOR 0 - x
		0 XOR x - x
		x XOR 1 - x
		1 XOR x - x
		x XOR x - x
		*/
		else return UNDEF_3S;
	  }
  }



//PORTA


Porta::Porta(unsigned int NI)
{
    //Alocando Porta;
    Nin = NI; //Faz o número de entradas ser igual a variável NI, passada como parâmetro;
    saida = UNDEF_3S; //Inicia a saída da porta com o valor UNDEF_3S;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=UNDEF_3S;
}
Porta::Porta(const Porta &P)
{
    //Construtor por cópia
    Nin = P.Nin;
    saida = P.saida;
    //id_in[Nin];
    for (unsigned i=0; i<Nin; i++) id_in[i]=P.id_in[i];    
}
void Porta::setSaida(bool_3S s)
{
    //Salva a saída fornecidade, se -1<=s<=1
    if ((s>=UNDEF_3S) && (s<=TRUE_3S)) saida=s; 
    else 
    {
        cerr << "Sinal digital inválido!" << endl;
    }
}
int Porta::getId_in(unsigned int i) const
{
    //Retorna a indicação de da origem do sinal da entrada desse porta
    if ((i>0) && (i<NUM_MAX_INPUTS_PORTA)) return id_in[i]; 
    else 
    {
        cerr << "Número de entradas inválida!" << endl;
        return ;
    }
}
void Porta::setId_in(unsigned int i, int N)
{
    //Oferece uma origem para o sinal da porta  
    if ((i>0) && (i<Nin)) id_in[i]=N;
    else 
    {
        cerr << "Número de entrada inválida!" << endl;
    }
}
void Porta::digitar()
{
    do
    {
    cout << "Digite o número de entradas da porta: ";
    cin >> Nin;
    } while ((Nin<0) || (Nin>NUM_MAX_INPUTS_PORTA));
    
    for (unsigned i=0; i<Nin; i++)
    {
        cout << "Digite a origem do sinal lógico da " << i+1 << "ª entrada da porta: ";
        cin >> id_in[i]; //Que porta ou entrada origina o sinal
    }
}
bool Porta::ler(istream& I)
{
	unsigned count(0);
    I.ignore(numeric_limits<streamsize>::max(), ' '); //Ignora até achar um espaço após o nome da porta
    I >> Nin;
    for (unsigned i=0; i<Nin; i++)
    {
        I.ignore(numeric_limits<streamsize>::max(), ' ');
        I >> id_in[i];   
		if (id_in!=0) count++; //conta se todos os id_ins são !=0
    }
    //Se Nin for maior que nulo e todas as ids de entrada forem !=0
	if((Nin>0)&&(count==Nin))) return true;
	else return false
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
    Porta::digitar();
}
bool Porta_NOT::ler(istream& I)
{
    I.ignore(numeric_limits<streamsize>::max(), ' '); //Ignora até achar um espaço após o nome da porta
    I >> Nin;
	//Se Nin for diferente de 1, não pode constituir NOT
	if (Nin!=1) return false; 
	else
	{
		I.ignore(numeric_limits<streamsize>::max(), ' ');
		I >> id_in[0]; 
		return true;		
	}
}
ostream &Porta_NOT::imprimir(ostream& O) const
{
    O << "NT ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOT::simular(const bool_3S in[])
{
    return ~in[0];
}


//PORTA_AND

void Porta_AND::digitar()
{
}
bool Porta_AND::ler(istream& I)
{
	Porta::ler(I);
}
ostream &Porta_AND::imprimir(ostream& O) const
{
    O << "AN ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_AND::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++) prov = (prov&in[i]);
	return prov;
}


//PORTA_NAND

void Porta_NAND::digitar()
{
}
bool Porta_NAND::ler(istream& I)
{
	Porta::ler(I);
}
ostream &Porta_NAND::imprimir(ostream& O) const
{
    O << "NA ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NAND::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++) prov = (pro&in[i]);
	return (~prov);
}


//PORTA_OR

void Porta_OR::digitar()
{
}
bool Porta_OR::ler(istream& I)
{
	Porta::ler(I);
}
ostream &Porta_OR::imprimir(ostream& O) const
{
    O << "OR ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_OR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov|in[i]);
	}
	return prov;
}


//PORTA_NOR

void Porta_NOR::digitar()
{
}
bool Porta_NOR::ler(istream& I)
{
	Porta::ler(I);
}
ostream &Porta_NOR::imprimir(ostream& O) const
{
    O << "NO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NOR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov|in[i]);
	}
	return (~prov);
}


//PORTA_XOR


void Porta_XOR::digitar()
{
}
bool Porta_XOR::ler(istream& I)
{
	Porta::ler(I);
}
ostream &Porta_XOR::imprimir(ostream& O) const
{
    O << "XO ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_XOR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov^in[i]);
	}
	return prov;
}


//PORTA_NXOR

void Porta_NXOR::digitar()
{
}
bool Porta_NXOR::ler(istream& I)
{
	Porta::ler(I); 
}
ostream &Porta_NXOR::imprimir(ostream& O) const
{
    O << "NX ";
    Porta::imprimir(O);
    return O;
}
bool_3S Porta_NXOR::simular(const bool_3S in[])
{
    bool_3S prov;
	prov = in[0];
	for (unsigned i=1; i<Nin; i++)
	{
		prov = (prov^in[i]);
	}
	return (~prov);
}


//CIRCUITO 


void Circuito::limpar()
{
    //Libera array inputs
    if (inputs!=NULL)
    {
        delete[] inputs;
        inputs = NULL;
    }
    //Libera array id_out
    if (id_out!=NULL)
    {
        delete[] id_out;
        id_out = NULL;
    }
    //Libera array de ptrs portas
    if (portas!=NULL)
    {
        for (unsigned i=0; i<Nportas; i++) delete portas[i];
        delete[] portas;
        portas = NULL;
    }
    //Zera todos os quantificadores
    Nin = 0;
    Nout = 0;
    Nportas = 0;
}
void Circuito::alocar(unsigned int NI, unsigned int NO, unsigned int NP)
{
    limpar();
    
    //Aloca os quantificadores com os valores fornecidos
    Nin = NI;
    Nout = NO;
    Nportas = NP;
    
    //Aloca dinâmicamente os arrays
    inputs = new bool_3S[Nin];
    id_out = new int[Nout];
    portas = new ptr_Porta[Nportas];
}
void Circuito::copiar(const Circuito& C)
{
    limpar();
    alocar(C.Nin, C.Nout, C.Nportas);
    
    //Realiza as cópias necessárias
    //obs.: uso do método clone
    for (unsigned i=0; i<Nin; i++) inputs[i]=C.inputs[i];
    for (unsigned i=0; i<Nout; i++) id_out[i]=C.id_out[i];
    for (unsigned i=0; i<Nportas; i++) portas[i] = C.portas[i]->clone();
}
void Circuito::digitar()
{
    //Cria as variáveis temporárias
    int op;
    Porta_NOT tNOT;
    Porta_AND tAND;
    Porta_NAND tNAND;
    Porta_OR tOR;
    Porta_NOR tNOR;
    Porta_XOR tXOR;
    Porta_NXOR tNXOR;
    
    //Número de entradas do circuito
    do 
    {
        cout << "Digite o número de entradas do circuito: ";
        cin >> Nin;
    } while (Nin<=0);
    //Número de saídas do circuito
    do 
    {
        cout << "Digite o número de saídas do circuito: ";
        cin >> Nout;
    } while (Nout<=0);
    //Número de portas do circuito
    do 
    {
        cout << "Digite o número de portas lógicas do circuito: ";
        cin >> Nportas;
    } while (Nportas<=0);
    
    //Aloca os arrays
    alocar(Nin, Nout, Nportas);
    
    
    //Definição das portas
    
    for (unsigned i=0; i<Nportas; i++) //ler a quantidade de portas fornecidas
    {
        //Menu de escolha
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
        
        //Ler por meio de teclado o tipo de porta
        switch (op)
        {
            case 0:
                tNOT.digitar();
                portas[i] = (&tNOT)->clone();
                break;
            case 1:
                tAND.digitar();
                portas[i] = (&tAND)->clone();
                break;
            case 2:
                tNAND.digitar();
                portas[i] = (&tNAND)->clone();
                break;
            case 3:
                tOR.digitar();
                portas[i] = (&tOR)->clone();
                break;
            case 4:
                tNOR.digitar();
                portas[i] = (&tNOR)->clone();
                break;
            case 5:
                tXOR.digitar();
                portas[i] = (&tXOR)->clone();
                break;
            case 6:
                tNXOR.digitar();
                portas[i] = (&tNXOR)->clone();
                break;
            default:
                break;
        }
    }
    
    //Define a origem do sinal das saídas do circuitos, se de uma porta ou entrada
    for (unsigned i=0; i<Nout; i++)
    {
        cout << "Digite a origem do sinal lógico da " << i+1 << "ª saída do circuito: ";
        cin >> id_out[i];
    }

}
void Circuito::ler(const char*nome) //Adicionei esse nome, pois antes estava sem variável
{
    ifstream arquivo(nome);
    if (arquivo.is_open())
    {
        //Variáveis temporárias para a leitura
		unsigned count(0); //contador
        string prov;
        Porta_NOT tNOT;
        Porta_AND tAND;
        Porta_NAND tNAND;
        Porta_OR tOR;
        Porta_NOR tNOR;
        Porta_XOR tXOR;
        Porta_NXOR tNXOR;


      //Lendo cabeçalho geral
        arquivo >> prov;
        if (prov != "CIRCUITO:")
        {
            cerr << "Arquivo com cabeçalho principal inválido\n";
        }
        else //FAlta Prever erros para a falta de algum dos elementos
        {
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');        
            arquivo >> Nin;//Nin>0;
            if(Nin<=0){
                cerr << "Numero invalido de entradas!"
                return;
            }
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nout;//Nout>0;
            if(Nin<=0){
                cerr << "Numero invalido de saidas!"
                return;
            }
            arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
            arquivo >> Nportas;//Nportas>0;
            if(Nportas<=0){
                cerr << "Numero invalido de portas!"
                return;
            }
        }
        //Aloca os arrays
        alocar(Nin, Nout, Nportas);
        
        arquivo >> prov;
        if (prov != "PORTAS:") //Ler o segundo cabeçalho
        {
            cerr << "Arquivo com cabeçalho de portas inválido\n";
        }
        else
        {
            // Antes de ler os dados de um arquivo, zera o conteudo atual do circuito
            limpar();

            for (unsigned i=0; i<Nportas; i++)
            {
                // Vai para o inicio de uma linha (ignora ENTER de linha anterior)
                arquivo.ignore(numeric_limits<streamsize>::max(), '\n');
                arquivo >> prov;

                switch(prov)
                {
					case 'NT':
						if(tNOT.ler(arquivo)) 
						{
							portas[i]=(&tNOT)->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tNOT.Nin; k++)
							{
								if(tNOT.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tNOT.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tNOT.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tNOT.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma porta NOT!";
							return;
						}
						break;
					case 'AN':
						if(tAND.ler(arquivo)) 
						{
							portas[i]=(&tAND)->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tAND.Nin; k++)
							{
								if(tAND.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tAND.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tAND.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tAND.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma  AND!";
							return;
						}
						break;
					case 'NA':
						if(tNAND.ler(arquivo)) 
						{
							portas[i]=(&tNAND)->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tNAND.Nin; k++)
							{
								if(tNAND.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tNAND.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tNAND.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tNAND.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma porta NAND!";
							return;
						}
						break;
					case 'OR':
						if(tOR.ler(arquivo)) 
						{
							portas[i]=(&tOR->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tOR.Nin; k++)
							{
								if(tOR.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tOR.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tOR.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tOR.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma porta OR!";
							return;
						}
						break;
					case 'NO':
						if(tNOR.ler(arquivo)) 
						{
							portas[i]=(&tNOR->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tNOR.Nin; k++)
							{
								if(tNOR.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tNOR.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tNOR.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tNOR.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma porta NOR!";
							return;
						}
						break;
					case 'XO':
						if(tXOR.ler(arquivo)) 
						{
							portas[i]=(&tXOR->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tXOR.Nin; k++)
							{
								if(tXOR.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tXOR.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tXOR.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tXOR.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma porta XOR!";
							return;
						}
						break;
					case 'NX':
						if(tNXOR.ler(arquivo)) 
						{
							portas[i]=(&tNXOR->clone();
							//for que percorre todas as origens de entrada da porta lida
							for (unsigned k=0; k<tNXOR.Nin; k++)
							{
								if(tNXOR.id_in[k]<0)//Se entrada for entrada do circuito
								{
									//Módulo do id tem que ser menos/igual a Nout
									if(-tNXOR.id_in[k]<=Nout) count++;
								}
								else //Se entrada for saída de uma porta
								{
									//Id menor/igual a Nportas
									if(tNXOR.id_in[k]<=Nportas) count++;
								}
							}
							//Se uma das duas condições do for forem atendidas para todos os casos
							if(count==tNXOR.Nin)//continua a leitura
							else //interrompe leitura e msg de erro
							{
								cerr << "Id de entrada da porta maior que o número de portas" << endl;
								return;
							}
							count=0; //zera contador para próxima leitura
						}
						else 
						{
							cerr << "Erro na leitura de uma porta NXOR!";
							return;
						}
						break;
					default:
					// Primeiro caractere da linha nao era nenhuma das opçoes validas
					cerr << "Arquivo " << arquivo << " parcialmente invalido para leitura\n";
					return;
					/*portas[i]->ler(arquivo);*/
				}
            }
        }
        
        arquivo >> prov;
        if (prov != "SAIDAS:") //Ler o terceiro cabeçalho
        {
            cerr << "Arquivo com cabeçalho de saídas inválido\n";
        }
        else
        {
            for (unsigned i=0; i<Nout; i++)
            {
                arquivo.ignore(numeric_limits<streamsize>::max(), ' ');
                arquivo >> id_out[i];
				if ((id_out[i]==0)||(id_out[i]>Nportas)) 
				{
					cerr << "Id de porta igual a zero!" << endl;
					return;
				}	
            }
        }
        
        //Fechando arquivo
        arquivo.close();
    }
    else //Erro na abertura geral do arquivo
    {
        cerr << "Erro na abertura do arquivo \"" << nome << "\" para leitura\n";
    }
}
ostream &Circuito::imprimir(ostream& O) const
{
    //Impressão padrão do circuito
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
    //Retorna ostream
    return O;
}
void Circuito::salvar(const char*nome) const //Adicionei esse nome, pois antes estava sem variável
{
    ofstream arquivo(nome);
    //arquivo.is_open();
    if (arquivo.is_open())
    {
        imprimir(arquivo);
        arquivo.close();
    }
    else
    {
      cerr << "Erro na abertura do arquivo \"" << nome << "\" para escrita\n";
    }
}
void Circuito::digitarEntradas()
{
    //Digitar os valores lógicos das entradas em caso de simulação
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
    //Imprime os valores lógicos das entradas
    cout << "Valores das entradas do circuito: " << endl;
    for (unsigned i=0; i<Nin; i++) cout << "Entrada " << i+1 << " : " << inputs[i] << endl; 
}
void Circuito::imprimirSaidas() const
{
    //Imprime a origem do sinal das saídas do circuito
    cout << "Origem do sinal das saídas do circuito: " << endl;
    for (unsigned i=0; i<Nout; i++) cout << "Saída " << i+1 << " : " << id_out[i] << endl; 
}
void Circuito::simular()
{
    bool tudo_def, alguma_def, in_portas[4];
    
    for (unsigned i=0; i<Nportas; i++) *portas[i]->saida = UNDEF_3S;
    
    do 
    {
        tudo_def = TRUE_3S;
        alguma_def = FALSE_3S;
        for (unsigned i=0; i<Nportas; i++)
        {
            if (*portas[i]->saida == UNDEF_3S)
            {
				//ATENÇÃO, IMPORTANTE
				//Nesse FOR, cada coordenada de in_portas[] 
				//Recebe valor lógico da saída das portas de id_in[0] até id_in[Nin-1]
				//Que servem de entradas para *portas[i]
				for (unsigned j=0; j<*portas[i]->Nin; j++) in_portas[j]=*portas[(*portas[i]->id_in[j])]->saida;
				//in_portas = /*entradas booleanas da porta i;*/ //Vetor de valores lógicos das entradas da porta
				
				portas[i]->saida = portas[i]->simular(in_porta);//Simula a porta e armazena o resultado em sua saída
                if (portas[i].saida == UNDEF_3S)
                {
                    tudo_def = FALSE_3S;
                }
                else
                {
                    alguma_def = TRUE_3S;
                }
            }
        }
    } while (!tudo_def && alguma_def)
   

	//imprime uma linha da tabela verdade
	//obs: o método tabela vai repetir isso (3^Nin) vezes
	
	
	//primeiro imprime as entradas do vetor de inputs
	cout << "ENTRADAS: ";
	for (unsigned i=0; i<Nin; i++)
	{
		if(inputs[i]==TRUE_3S) cout << "T ";
		else
		{
			if(inputs[i]==FALSE_3S) cout << "F ";
			else cout << "? ";
		}
	}
	//depois imprime as saidas do circuito
	//as saídas dos circuitos vão receber a saída de alguma porta
	//a id dessa porta que vai oferecer saída para o circuito está 
	//nos Nout elementos do vetor id_out
	//cada int do id_out vai ser projetado para procurar a saída da porta indicada
	//imprimindo-a
	cout << "SAIDAS: ";
	for (unsigned i=0; i<Nout; i++) cout << *portas[id_out[i]]->saida << " ";
	cout << endl; //Enter para a próxima leitura
}
void Circuito::gerarTabela()
{    
    for (unsigned i=0; i<Nin; i++) *(inputs[i]) = FALSE_3S;
    
    do
    {
        Circuito::simular();
        
        //Qual input incrementar?
        i = Nin-1;
        while ((i>=0) && (inputs[i]==UNDEF_3S)) //se for undef, coloca para false
        {
            *(inputs[i])=FALSE_3S;
            i--;
        }
        
        //Incrementa a input escolhida
        if (i>=0)
        {
            if (*(inputs[i])==FALSE_3S)//se for false, coloca para true
            {
                *(inputs[i])=TRUE_3S;
            }
            else //se for true, coloca para undef, pq false já foi
            {
                *(inputs[i])=UNDEF_3S
            }
        }
    } while (i>=0);
}











