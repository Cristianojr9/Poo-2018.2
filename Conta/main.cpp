#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

enum Creditar{ deposito, estorno };
enum Debitar{ saque, tarifa };

class Operacao{
private:
    string descricao;
    float valor = 0, saldo = 0;
public:
    
    string getDescricao(){ 
        return this->descricao; 
    }float getValor(){ 
        return this->valor; 
    }float getSaldo(){ 
        return this->saldo; 
    }
    
    void setDescricao(string descricao){ 
        this->descricao = descricao; 
    }void setValor(float valor){ 
        this->valor = valor; 
    }void setSaldo(float saldo){ 
        this->saldo = saldo;
    }
    
    Operacao(string descricao = "aaa", float valor = 0, float saldo = 0){
        this->descricao = descricao;
        this->valor = valor;
        this->saldo = saldo;
    }
};

class Conta{
private:
    int numero = 0;
    float saldo = 0;
    vector<Operacao> operacoes;
public:
    
    int getNumero(){ 
        return this->numero; 
    }float getSaldo(){ 
        return this->saldo; 
    }
    
    void setNumero(int numero){ 
        this->numero = numero; 
    }void setSaldo(float saldo){ 
        this->saldo = saldo; 
    }
    
    Conta(int numero = 0){
        this->numero = numero;
    }
    
    void pushOperation(string descricao, float val, float saldo){
        operacoes.push_back(Operacao(descricao, val, saldo));
    }
    
    string toString(){
        stringstream ss;
        ss << "conta:" << this->getNumero() << " saldo: " << this->getSaldo();
        return ss.str();
    }
    
    string extrato(size_t num = 0){
        stringstream ss;
        int index = (num > 0 && num < operacoes.size()) ? operacoes.size()-num : 0;
        for (size_t i = index; i < operacoes.size(); i++){
            ss << i 
            << ": " << setw(10) << operacoes[i].getDescricao()
            << ": " << setw(5) << operacoes[i].getValor() 
            << ": " << setw(5) << operacoes[i].getSaldo() 
            << endl;
        }
        return ss.str();
    }

    bool creditar(int op, float val){
        switch (op){
            case 0: 
                if (val > 0){
                    setSaldo(getSaldo() + val);
                    pushOperation("deposito", val, getSaldo());
                    return true;
                }
            case 1:
                if (val > 0){
                    setSaldo(getSaldo() + val);
                    pushOperation("estorno", val, getSaldo());
                    return true;
                }
            default:
                return false;
        }
    }

    bool debitar(int op, float valor){
        switch (op){
            case 0: 
                if (getSaldo() >= valor){
                    setSaldo(getSaldo() - valor);
                    pushOperation("saque", valor*(-1), getSaldo());
                    return true;
                }
            case 1: 
                if (getSaldo() >= valor){
                    setSaldo(getSaldo() - valor);
                    pushOperation("tarifa", valor*(-1), getSaldo());
                    return true;
                }
            default:
                return false;
        }
    }
};


class Controller{
public:
    Conta conta;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if (op == "init"){
            int n;
            in >> n;
            conta = Conta(n);
            out << "success";
        }else if (op == "show"){
            out << conta.toString();
        }else if (op == "extrato"){
            int n = 0;
            if (in >> n){
                in >> n;
                out << conta.extrato(n);
            }else
                out << conta.extrato();
        }else if (op == "deposito"){
            float v;
            in >> v;
            if (conta.creditar(Creditar::deposito, v))
                out << "success";
            else
                out << "failure: valor invalido";
        }else if (op == "saque" || op == "tarifa"){
            float v;
            in >> v;
            if (op == "saque"){
                if (conta.debitar(Debitar::saque, v))
                    out << "success";
            }else 
                out << "failure: valor invalido";
        }
        return out.str();
    }

    void exec(){
        string line;
        while (true){
            getline(cin, line);
            if (line == "end")
                return;
            cout << shell(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}
