#include <iostream>
using namespace std;

struct Professor{
    string nome;
    int id;
public:
    Pessoa(string nome = "", int id = 0):
        nome(nome), id(id){
    }
    string toString(){
        return " " + id + ":" + to_string(nome);
    }
};

struct Disciplina{
    string id;
    string nome;
public:
    Disciplina(string id = "01", string nome = "aaa"):
    id(id), nome(nome){
    }
    string toString(){
        return " " + id + ":" + to_string(nome);
    }
};

struct Aluno{
    string id;
    string curso;
    string nome;
public:
    Aluno(string id = "", string curso = "", string nome = ""):
        id(id), curso(curso), nome(nome){
    }
    string toString(){
        return " " + id + ":" + curso ":" + to_string(nome);
    }
};

struct Repositorio{
};

int main(){
    return 0;
}
