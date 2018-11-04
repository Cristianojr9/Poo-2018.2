#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Cliente{
public: 
    string id;
    string nome;
    float saldo;
    bool alive;
      
    Cliente(string id = "", string nome = "", float saldo = 0){
        this->id = id;
        this->nome = nome;
        this->saldo = saldo;
        alive = true;
    }
};

class Transacao{
public:
    int idtr;
    string idcli;
    float value;
      
    Transacao(int idtr, string idcli, float value){
        this->idtr = idtr;
        this->idcli = idcli;
        this->value = value;
    }
};

class Sistema{
public:
    float value;
    vector<Cliente> clientes;
    vector<Transacao> transacoes;
    int contadoridtr = 0;
 
    Sistema(float value){
        this->value = value;
    }
      
    bool validatr(string cli_id, float value){
        if(this->value + value <= 0)
            throw "fail: sem fundos\n";
            for(auto cli : clientes){
                if(cli.id == cli_id && cli.saldo + value > 0)
                    throw "fail: valor maior que o debito\n";
            }
        return true;
    }
    bool validacli(string cli_id){
        for(Cliente cli : clientes){
            if(cli_id == cli.id)
                return true;
            }
        return false;
    }
    bool addcli(string cli_id, string nome){
        if(validacli(cli_id))
            throw "fail: cliente ja existe\n";
            clientes.push_back(Cliente(cli_id,nome));
    }
    void addtr(string cli_id, float value){
            if(validacli(cli_id)){
                for(Cliente &cli : clientes){
                    if(cli.id == cli_id){
                        cli.saldo += value;
                        this->value += value;
                        transacoes.push_back(Transacao(contadoridtr, cli.id, value));
                        contadoridtr++;
                        break;
                    }
                }
            } 
            else
                throw "fail: cliente nao existe\n";
    }
    void showcli(){
        for(Cliente cli : clientes){
            cout << "[cli_id:" + cli.id + "]" + cli.nome + ":" + to_string((int)cli.saldo) << endl; 
        }
    }
    void showtr(){
        for(Transacao tr : transacoes){
            cout << "[id:" + to_string(tr.idtr) + "] " + tr.idcli + ":" + to_string((int)tr.value) << endl;
        }
    }
};

class Agiota{
public:
    string nome;
    Sistema* sist;
      
    Agiota(string nome, Sistema* sist){
        this->nome = nome;
        this->sist = sist;
    }
      
    void toString(){
        cout << "nome: " + nome + " / saldo: " + to_string(sist->value);
    }
};

struct Controller{
    Sistema sist;
    Agiota agi;
public:
    Controller():
        
    {
    }
    
    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
            
        if(op == "add"){
            in >> op;
            if(op == "cli"){
                string id, nome;
                in >> id;
                getline(in, nome);
                sist.addcli(id, nome);
            }else if(op == "tr"){
                string cli_id;
                float value;
                in >> cli_id;
                in >> value;
                if(sist.validatr(cli_id, value))
                    sist.addtr(cli_id, value);
            }
        }
    }                 
    void exec(){
        string ss;
            while(true){
                getline(cin, ss);
                if(ss == "end")
                    break;
                try{
                shell(ss);
                }catch(const char * e){
                    cout << e << endl;
            }
        }
    }
};


int main(){
    Controller jj;
    jj.exec;
    return 0;
}
