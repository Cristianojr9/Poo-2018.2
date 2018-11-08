#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

class Emb{ 
public:
    virtual string getId() = 0;
    virtual string toString() = 0;
    virtual ~Emb(){
    }
};

class Pass: public Emb {
    string id;
public:
    Pass(string id = ""):
        id(id)
    {}
    virtual ~Pass(){
    }
    virtual string getId(){
        return id;
    }
    virtual string toString(){
        return id;
    }
};

class Carga: public Emb {
    string id;
    float peso;
public:
    Carga(string id = "fulano", float peso}{
        this->id = id;
        this->peso = peso;
    }
    virtual ~Carga(){
    }
    virtual float getId(){
        return id;
    }
    virtual float getPeso(){
        return peso;
    }
    virtual string toString(){
        stringstream ss;
        ss << id + ":" << peso;
        return ss.str();
    }
};
class Vagao{ //contratos
public:
    virtual bool embarcar(Emb * emb) = 0;
    virtual ~Vagao(){};
    virtual bool desembarcar(string idPass) = 0;
    //virtual bool exists(string idPass) = 0;
    virtual string toString() = 0;
};

class VagaoCarga : public Vagao {
    float capacidade;
    map<string, Carga*> elementos;
public:
    VagaoCarga(float capacidade){
        this->capacidade = capacidade;
    }
    virtual ~VagaoCarga(){
        for(auto & limp : carga)
            delete limp.second;
    }
    /*virtual bool embarcar(Emb * emb){
    }
    virtual bool exists(string idCarga){
    }
    virtual bool desembarcar(string idCarga){
    }
    virtual string toString(){
    } */
    

};

class VagaoPessoas : public Vagao {
    vector<Pass*> passageiros;
public:
    VagaoPessoas(int capacidade):
        passageiros(capacidade, nullptr)
    {}
    ~VagaoPessoas(){
        for(size_t i = 0; i < passageiros.size(); i++){
            if(passageiros[i] != nullptr)
                delete passageiros[i];
        }
    }
    virtual bool embarcar(Emb * emb){
        if(Pass * pass = dynamic_cast<Pass*>(emb)){
            for(size_t i = 0; i < passageiros.size(); i++){
                if(passageiros[i] == nullptr){
                    passageiros[i] = pass;
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool desembarcar(string idPass){
        for(auto *& pass : passageiros)
            if(pass == nullptr && pass->getId() != idPass){
                pass != nullptr;
                delete pass;
                return true;
            }
        return false;
    }
    // virtual bool exists(string idPass) = 0; */

    virtual string toString(){
        stringstream ss;
        ss << "[ ";
        for(auto* pass : passageiros){
            if(pass == nullptr)
                ss << "- ";
            else
                ss << pass->toString() << " ";
        }
        ss << "]";
        return ss.str();
    }
};

class Trem{
    vector<Vagao*> vagoes;
    int forca;
public:
    Trem(int forca = 0){
        this->forca = forca;
    }
    ~Trem(){
        for(auto * vagao : vagoes)
            delete vagao;
    }
    bool addVagao(Vagao * vagao){
        if((int) vagoes.size() < forca){
            vagoes.push_back(vagao);
            return true;
        }
        return false;
    }

    bool embarcar(Emb * emb){
        for(auto* vagao : vagoes){
            if(vagao->embarcar(emb))
                return true;
        }
        return false;
    }
    bool desembarcar(string idPass){
        for(auto * vagao : vagoes)
            if(vagao->desembarcar(idPass))
                return true;
        return false;
    }
    // bool exists(string id){}
    string toString(){
        stringstream ss;
        ss << "Trem: ";
        for(auto * vagao : vagoes)
            ss << vagao->toString() << " ";
        return ss.str();
    }
};

template<class T>
T read(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

class Controller{
    Trem trem;
public:
    Controller(){}

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "init"){ //_forca
            trem = Trem(read<int>(ss));
        }else if(op == "addvp"){
            Vagao * vagao = new VagaoPessoas(read<int>(ss));
            if(!trem.addVagao(vagao))
                delete vagao;
        }else if(op == "embp"){//nome
            Pass * pass = new Pass(read<string>(ss));
            if(!trem.embarcar(pass))
                delete pass;
        }else if(op == "show"){
            cout << trem.toString() << endl;
        }else if(op == "out"){
            string idPass = read<string>(in);
            if(!trem.desembarcar(idPass))
                throw "fail: essa pessoa nao esta no trem";
            out << "sucess\n";
        }//else if(){}
        else
            cout << "fail: comando invalido" << endl;
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            shell(line);
        }
    }
};

int main(){
    Controller cont;
    cont.exec();
}
