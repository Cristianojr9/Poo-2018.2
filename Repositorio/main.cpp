#include <iostream>
using namespace std;

struct Pessoa{
    string nome;
    int idade;
    Pessoa(string nome = "", int idade = 0):
        nome(nome), idade(idade){
    }
    string toString(){
        return "[" + nome + ":" + to_string(idade) + "]";
    }
};

struct Disciplina{
};

struct Repositorio{
};

int main(){
    return 0;
}
