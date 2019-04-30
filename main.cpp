/*
Nome: Bruno Mendonça Santos

expressoes aceitas:

variavel=expressao 
ex:
x=10+20+30
y=10+20+x

nao aceita nos seguintes casos:

x=10+y+20
x+num
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
#define VAR -10
using namespace std;

struct attrib{
  char op;
  int value;
  string num;
};

struct node{
  string nome;
  attrib elem;
  node* next;
};


void error(string);
void print(char);
int calc(int, int, int);
attrib expr();
attrib term();
attrib rest();
attrib x();
void match(char);
char nextToken();
string getNome();
void check();
node *check(string);
attrib valor(int);
char getback();

class linked_list
{
private:
    node *head,*tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(attrib n, string nome)
    {
        node *tmp = new node;
        tmp->nome = nome;
        tmp->elem.op = n.op;
        tmp->elem.value = n.value;
        tmp->elem.num = n.num;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    node* gethead()
    {
        return head;
    }
    void display()
    {
        node *tmp;
        
        tmp = head;
        while (tmp != NULL)
        {
            cout << tmp->nome << endl;
            tmp = tmp->next;
        }
        
    }
    node *find2(string nome)
    {
        node *tmp, *aux;
        tmp = head;
        while (tmp != NULL)
        {
            if(tmp->nome == nome){
              return tmp;
            }
            tmp = tmp->next;
        }
        return tmp;
    }

    static void find(node *head, string a)
    {
      
      if(head->nome == a)
        {
            cout << "achou" << endl; 
        }
        else if(head == NULL)
        {
            cout << "NULL" << endl;
        }
        else{
          find(head->next, a);
        }
        
    }
};

string input;
int count = 0;

char nextToken(){
  if (count == input.length())
    return EOF;
  return input[count++];
}

char getback(){
  return input[count--];
}
char lookahead;
linked_list symbol_table;

string getNome(){
  string nome;
  char look = lookahead;
  while((look!='=')){
      nome += look;
      look = nextToken();
      lookahead = nextToken();
      if(look==EOF){
        //cout <<"aqui 1";
        break;
      }else if(isdigit(look)){
        //cout <<"aqui 2";
        break;
      }else if(look=='+'){
        //lookahead = input[count-2];
        //if(lookahead == '1') cout<<"isso";
        //cout <<"aqui 3";
        break;
      }else if(look=='-'){
        //cout <<"aqui 4";
        break;
      }
      //lookahead = nextToken();
  }
  return nome;
}

attrib expr(){
  attrib res, v1, v2, temp;
  
  if(isdigit(lookahead)){
    v1 = term();  
    v2 = rest();
    //cout<<v2.value;
    res.value = calc(v1.value, v2.op, v2.value);
  }else{
    node *checar;    
    string nome = getNome();
    checar = check(nome);
    
    if(checar!=NULL){
      
      //v1 = term();
      //v2 = rest();
      //res.value = calc(v1.value, v2.op, v2.value);
      v1.op = NO_OP;
      v1.value = checar->elem.value;      
      v2 = rest();
      res.value = calc(v1.value, v2.op, v2.value);
      //res = v1;
      
    }else{   
    //cout<<"aqui";
    v1.op = NO_OP;    
    //lookahead = nextToken();
    temp = expr();
    v1.value = temp.value;
    res = v1;
    symbol_table.add_node(res, nome);
  

    }
  }
  
  return res;
}

node *check(string nome){
  
  node *aux = symbol_table.find2(nome);
  if(aux!=NULL){
      
      return aux;
  }
  return aux;
}

attrib x(){
  attrib res, val;
  res.op = NO_OP;
  string nome;
  while((lookahead!='=')){
      
      nome += lookahead;
      lookahead = nextToken();
  }
  return res;
}

attrib rest(){
  
  attrib e, t, r;
  e.op = NO_OP;
  
  if (lookahead == '-'){
     //-term rest
     match('-');
     e.op = MINUS;
     t = term();
     r = rest();

  } else if (lookahead == '+'){
    //+term rest
    //cout<<"aqui";
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

int calc(int v1, int op, int v2){
  
  switch (op){
    case NO_OP : return v1;
    case SUM : return v1+v2;
    case MINUS : return v1-v2;
  }
  return 0;//error
}

attrib term(){
  attrib res,v1;
  res.op = NO_OP;
  if(isdigit(lookahead)){
  if((lookahead!='+' && lookahead!='-')){
    
  while(((lookahead!='+') && (lookahead!='-')) && (lookahead!=EOF) ){
  
  
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
  }
  }else{
    v1 = valor(lookahead);
    res = v1;
  }
  

  //symbol_table.add_node(res);
  

  return res;
}

attrib valor(int lookahead){
  attrib res, v1;
    node *checar;    
    string nome = getNome();
    checar = check(nome);
    if(checar!=NULL){
      v1.op = NO_OP;
      lookahead = nextToken();
      v1.value = checar->elem.value;
      res = v1;
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

void error(string msg){
  cout << endl << "Syntax Error: "<< msg << endl;
  cout << input << endl;
  for (int i = 0 ; i < count-1; i++)
     cout << " ";
     cout << "^";
   cout << endl;

}

int main(){
  cout << "$ ";
  getline(cin, input);
  while (!input.empty()){
    lookahead = nextToken();
    attrib e = expr();
    //symbol_table.find(symbol_table.gethead(), e);
    cout << e.value << endl << "$ ";
    getline(cin, input);
    count = 0;
  }
}
