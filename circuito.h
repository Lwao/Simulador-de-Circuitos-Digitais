#ifndef _CIRCUITO_H_
#define _CIRCUITO_H_

#include <iostream>

using namespace std;

// Criando um tipo de dados enumerado para representar um booleano com 3 estados:
// TRUE_3S, FALSE_3S e UNDEF_3S

enum bool_3S {
  FALSE_3S = 0,
  TRUE_3S = 1,
  UNDEF_3S = -1
};

#define NUM_MAX_INPUTS_PORTA 4

class Porta;
typedef Porta *ptr_Porta;

class Porta {
protected:
  unsigned Nin;
  int id_in[NUM_MAX_INPUTS_PORTA];
  bool_3S saida;
public:
  Porta(unsigned NI=2);
  Porta(const Porta &);
  inline virtual ~Porta() {}

  virtual ptr_Porta clone() const = 0;
  inline unsigned getNumInputs() const {return Nin;}
  inline bool_3S getSaida() const {return saida;}
  void setSaida(bool_3S s);
  int getId_in(unsigned i) const;
  void setId_in(unsigned i, int N);

  virtual void digitar();
  virtual bool ler(istream &I);
  virtual ostream &imprimir(ostream &O) const;

  virtual bool_3S simular(const bool_3S in[]) = 0;
};

// Operador << com comportamento polimorfico
inline ostream &operator<<(ostream &O, const Porta &X) {return (&X)->imprimir(O);};

class Porta_NOT: public Porta {
public:
  inline Porta_NOT(): Porta(1) {}
  inline ~Porta_NOT() {}
  ptr_Porta clone() const {return new Porta_NOT(*this);}

  void digitar();
  bool ler(istream &I);
  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_AND: public Porta {
public:
  inline Porta_AND(): Porta() {}
  inline ~Porta_AND() {}
  ptr_Porta clone() const {return new Porta_AND(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NAND: public Porta {
public:
  inline Porta_NAND(): Porta() {}
  inline ~Porta_NAND() {}
  ptr_Porta clone() const {return new Porta_NAND(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_OR: public Porta {
public:
  inline Porta_OR(): Porta() {}
  inline ~Porta_OR() {}
  ptr_Porta clone() const {return new Porta_OR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NOR: public Porta {
public:
  inline Porta_NOR(): Porta() {}
  inline ~Porta_NOR() {}
  ptr_Porta clone() const {return new Porta_NOR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_XOR: public Porta {
public:
  inline Porta_XOR(): Porta() {}
  inline ~Porta_XOR() {}
  ptr_Porta clone() const {return new Porta_XOR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Porta_NXOR: public Porta {
public:
  inline Porta_NXOR(): Porta() {}
  inline ~Porta_NXOR() {}
  ptr_Porta clone() const {return new Porta_NXOR(*this);}

  ostream &imprimir(ostream &O) const;

  bool_3S simular(const bool_3S in[]);
};

class Circuito {
private:
  unsigned Nin;      // Numero de entradas
  unsigned Nout;     // Numero de saidas
  unsigned Nportas;  // Numero de portas
  bool_3S *inputs;   // array que deve ser alocado com dimensao "Nin"
  int *id_out;       // array que deve ser alocado com dimensao "Nout"
  ptr_Porta *portas; // array que deve ser alocado com dimensao "Nportas"
  void limpar();
  void alocar(unsigned NI, unsigned NO, unsigned NP);  // ATENCAO: fora de construtor, sempre chamar antes limpar()
  void copiar(const Circuito &C);                      // ATENCAO: fora de construtor, sempre chamar antes limpar()
public:
  // As variaveis do tipo Circuito sao sempre criadas sem nenhum dado
  // A definicao do numero de entradas, saidas e portas eh feita ao ler do teclado ou arquivo
  inline Circuito():Nin(0),Nout(0),Nportas(0),inputs(NULL),id_out(NULL),portas(NULL) {}
  // Construtor por copia apenas chama a funcao copiar
  inline Circuito(const Circuito &C) {copiar(C);}
  // Destrutor apenas chama a funcao limpar
  inline ~Circuito() {limpar();}
  // Operador de atribuicao apenas chama as funcoes copiar e limpar
  inline void operator=(const Circuito &C) {if (this!=&C) {limpar(); copiar(C);}}

  // Entrada dos dados de um circuito via teclado
  void digitar();
  // Entrada dos dados de um circuito via arquivo
  void ler(const char *);
  // Saida dos dados de um circuito (em tela ou arquivo, mesma funcao)
  ostream &imprimir(ostream &O=cout) const;
  // Salvar circuito em arquivo
  // Abre a stream e depois chama o metodo imprimir
  void salvar(const char *) const;
  // Solicita ao usuario que digite os valores das entradas do circuito, que sao
  // as variaveis inputs[i], i de 0 a Nin-1
  void digitarEntradas();
  // Imprime em tela os valores das variaveis inputs[i]
  void imprimirEntradas(void) const;
  // Imprime em tela os valores das saidas das portas ou das entradas do circuito que estao conectadas
  // aas saidas do circuito, de acordo com as variaveis id_out[i], i de 0 a Nout-1
  void imprimirSaidas(void) const;

  // Calcula a saida das portas do circuito para os valores de entrada que estao em inputs[i]
  void simular();
  // Calcula a tabela verdade do circuito:
  void gerarTabela(void);
};

inline ostream &operator<<(ostream &O, const Circuito &C) {return C.imprimir(O);}

#endif // _CIRCUITO_H_
