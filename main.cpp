/*
Nome: Bruno Mendonça Santos

ATUALIZADO, tudo funcionando
*/

#include <iostream>
#include <string>
#include <sstream> 
#include <ctype.h>
#define NUM 256
#define OP  257
#define NO_OP -1
#define SUM 1
#define MINUS 2
#define MAX 256
using namespace std;

struct attrib {
  char op;
  int value;
  string num;
};

struct variavel{
  string nome;
  attrib elem;
};

struct tabela{
  int inicio;
  int prox;
};

variavel symbol_table[MAX];
tabela table;
int pos;

void error(string);
void print(char);
int calc(int, int, int);
attrib expr();
attrib term();
attrib rest();
void match(char);
char nextToken();
void inicializar();
int add_table(attrib, string);
void mostrar();
int find(string);
int change(attrib,string);


string input; // = "9-5+2";
//<9> <-> <5> <+> <2>
// --- ANALISADOR LÉXICO
int count = 0;
char nextToken(){
  if (count == input.length())
    return EOF;
  return input[count++];
}
// --- ANALISADOR SINTÁTICO
char lookahead;


// --- TABELA DE SIMBOLOS
void inicializar(){
  table.inicio = 0;
  table.prox = 0;
}

int add_table(attrib elem, string nome){
  int aux;
  if(table.prox >= MAX) return -1;
  symbol_table[table.prox].nome = nome;
  symbol_table[table.prox].elem.op = elem.op;
  symbol_table[table.prox].elem.value = elem.value;
  aux = table.prox;
  table.prox++;
  return aux;
}

void mostrar(){
  int i;
  if(table.prox==table.inicio) cout<<"Tabela de simbolos vazia"<<endl;
  for(i=table.inicio; i<table.prox; i++){
    cout<<symbol_table[i].nome<<endl;
    cout<<symbol_table[i].elem.value<<endl;
  }
}

int find(string nome){
  int i;
  if(table.prox==table.inicio) return -1;
  for(i=table.inicio; i<table.prox; i++){
    if(symbol_table[i].nome==nome) return i;
  }
  return -1;
}

int change(attrib res,string nome){
  int i;
  if(table.prox==table.inicio) return -1;
  for(i=table.inicio; i<table.prox; i++){
    if(symbol_table[i].nome==nome){
      symbol_table[i].nome = nome;
      symbol_table[i].elem.value = res.value;
      return i;
    }
  }
  return -1;
}

// --- LEXER

attrib expr(){
  attrib e, t, r;
  t = term();
  r = rest();
  e.value = calc(t.value, r.op, r.value);
  
  
  return e;
}

attrib rest(){
  
  attrib e, t, r, temp;
  e.op = NO_OP;
  if (lookahead == '-'){
     //-term rest
     match('-');
     e.op = MINUS;
     t = term();
     r = rest();

  } else if (lookahead == '+'){
    //+term rest
    match('+');
    e.op = SUM;
    t = term();
    r = rest();
  } else if (lookahead != EOF) {
    //vazio
    //syntax error?
    error("Sem tempo irmão");
  }
  e.value = calc(t.value, r.op, r.value);
  return e;
}

attrib term(){
  int add;
  string nome;
  attrib res, temp;
  res.op = NO_OP;

  if(isdigit(lookahead)){
    
    while((lookahead!='+') && (lookahead!='-') && lookahead!=EOF && lookahead!='='){
      
      switch (lookahead) {
        case '0': match('0'); res.num += "0"; break;
        case '1': match('1'); res.num += "1"; break;
        case '2': match('2'); res.num += "2"; break;
        case '3': match('3'); res.num += "3"; break;
        case '4': match('4'); res.num += "4"; break;
        case '5': match('5'); res.num += "5"; break;
        case '6': match('6'); res.num += "6"; break;
        case '7': match('7'); res.num += "7"; break;
        case '8': match('8'); res.num += "8"; break;
        case '9': match('9'); res.num += "9"; break;
        default: error("Number expected.");
      }
      
    }
    stringstream geek(res.num); 
    geek >> res.value;
  }else{
    while((lookahead!='+') && (lookahead!='-') && lookahead!=EOF && lookahead!='='){
      switch (lookahead){
        case 'a': match('a'); nome += "a"; break;
        case 'b': match('b'); nome += "b"; break;
        case 'c': match('c'); nome += "c"; break;
        case 'd': match('d'); nome += "d"; break;
        case 'e': match('e'); nome += "e"; break;
        case 'f': match('f'); nome += "f"; break;
        case 'g': match('g'); nome += "g"; break;
        case 'h': match('h'); nome += "h"; break;
        case 'i': match('i'); nome += "i"; break;
        case 'j': match('j'); nome += "j"; break;
        case 'k': match('k'); nome += "k"; break;
        case 'l': match('l'); nome += "l"; break;
        case 'm': match('m'); nome += "m"; break;
        case 'n': match('n'); nome += "n"; break;
        case 'o': match('o'); nome += "o"; break;
        case 'p': match('p'); nome += "p"; break;
        case 'q': match('q'); nome += "q"; break;
        case 'r': match('r'); nome += "r"; break;
        case 's': match('s'); nome += "s"; break;
        case 't': match('t'); nome += "t"; break;
        case 'u': match('u'); nome += "u"; break;
        case 'v': match('v'); nome += "v"; break;
        case 'w': match('w'); nome += "w"; break;
        case 'x': match('x'); nome += "x"; break;
        case 'y': match('y'); nome += "y"; break;
        case 'z': match('z'); nome += "z"; break;
        case 'A': match('A'); nome += "A"; break;
        case 'B': match('B'); nome += "B"; break;
        case 'C': match('C'); nome += "C"; break;
        case 'D': match('D'); nome += "D"; break;
        case 'E': match('E'); nome += "E"; break;
        case 'F': match('F'); nome += "F"; break;
        case 'G': match('G'); nome += "G"; break;
        case 'H': match('H'); nome += "H"; break;
        case 'I': match('I'); nome += "I"; break;
        case 'J': match('J'); nome += "J"; break;
        case 'K': match('K'); nome += "K"; break;
        case 'L': match('L'); nome += "L"; break;
        case 'M': match('M'); nome += "M"; break;
        case 'N': match('N'); nome += "N"; break;
        case 'O': match('O'); nome += "O"; break;
        case 'P': match('P'); nome += "P"; break;
        case 'Q': match('Q'); nome += "Q"; break;
        case 'R': match('R'); nome += "R"; break;
        case 'S': match('S'); nome += "S"; break;
        case 'T': match('T'); nome += "T"; break;
        case 'U': match('U'); nome += "U"; break;
        case 'V': match('V'); nome += "V"; break;
        case 'W': match('W'); nome += "W"; break;
        case 'X': match('X'); nome += "X"; break;
        case 'Y': match('Y'); nome += "Y"; break;
        case 'Z': match('Z'); nome += "Z"; break;
        default: error("Letter expected.");
      }
    }
    pos = find(nome);
    if(pos==-1){
      if(lookahead == '='){
        match('=');
        temp = expr();
        res.value = temp.value;
        add = add_table(res, nome);
      }else{

        res.value = 0;
        add = add_table(res, nome);
      }
      
    }else{
      if(lookahead == '='){
        match('=');
        temp = expr();
        res.value = temp.value;
        add = change(res,nome);
      }else res.value = symbol_table[pos].elem.value;
    }
    //res.value = 0;
  }

  return res;
}

void match(char c){
  if (lookahead == c) {
    lookahead = nextToken();
  } else {
    string s = "Found " + to_string(lookahead) + " but expected " + to_string(c);
    error(s);
  }
}

int calc(int v1, int op, int v2){
  switch (op){
    case NO_OP : return v1;
    case SUM : return v1+v2;
    case MINUS : return v1-v2;
  }
  return 0;//error
}

void error(string msg){
  cout << endl << "Syntax Error: "<< msg << endl;
  cout << input << endl;
  for (int i = 0 ; i < count-1; i++)
     cout << " ";
     cout << "^";
   cout << endl;

}

void print(char c){
  cout << c;
}
// --- ENTRYPOINT
int main(){
  inicializar();

  cout << "$ ";
  getline(cin, input);
  while (!input.empty()){
    lookahead = nextToken();
    attrib e = expr();
    cout << e.value << endl << "$ ";
    getline(cin, input);
    count = 0;
  }
}
