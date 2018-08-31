#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Passageiro{
    string nome; 
    int idade;

    Passageiro(string nome = "alguem", int idade = 65){
        this->nome = nome;
        this->idade = idade;
    }
    string toString(){
        stringstream ss;
        ss << this->nome << ":" << this->idade;
        return ss.str();
    }
};

struct Topic{
    vector<Passageiro*> cadeiras;

    Topic(int qtd = 0):
        cadeiras(qtd, nullptr)
    {
    }

   ~Topic(){
        for(Passageiro * cad : cadeiras)
            delete(cad);
    }

    bool reservar(Passageiro * passageiro, int qtd, int pri){
        if(qtd == 0){
            cout << "Fail: crie uma topic" << endl;
            return false;
        }

        for(Passageiro * pass : cadeiras){
            if(pass != nullptr && pass->nome == passageiro->nome){
                cout << "Fail: " << pass->nome << " ja esta na topic" << endl;
                return false;
            }
        }

        if(passageiro->idade < 65){
            for(int i = pri; i < qtd; i++){
                if(cadeiras[i] == nullptr){
                    cadeiras[i] = passageiro;                 
                    return true;
                }
            }
            for(int i = pri; i >= 0; i--){
                if(cadeiras[i] == nullptr){
                    cadeiras[i] = passageiro;
                    return true;
                }                
            }
        }
        else if(passageiro->idade >= 65){
            for(int i = 0; i < qtd; i++){
                if(cadeiras[i] == nullptr){
                    cadeiras[i] = passageiro;
                    return true;
                }
            }
        }
        cout << " Fail: trem lotado" << endl;
        return false;
    }

    bool remover(string nome){
        int qtd = cadeiras.size();

        for(int i = 0; i < qtd; i++){
            if(cadeiras[i]->nome == nome){
                cadeiras[i] = nullptr;
                return true;
            }
        }
        return false;
    }

    string toString(int qtd, int pri){
        stringstream ss;
        ss << " [ ";
        for(int i = 0; i < qtd; i++)
            if(cadeiras[i] == nullptr && i < pri){
                ss << "@ ";
            }
            else if(cadeiras[i] == nullptr && i >= pri){
                ss << "# ";
            }
            else if(i < pri){
                ss << "@ " << cadeiras[i]->toString() << " ";
            }
            else {
                ss << "# " << cadeiras[i]->toString() << " ";
            }

        ss << "]";
        return ss.str();
    }
};

int main(){ 
    Topic topic;
    string op;
    int qtd = 0, pri = 0;

    while(true){
        cin >> op;
        if(op == "end"){
            break;
        }else if(op == "show"){
            cout << topic.toString(qtd, pri) << endl;
        }else if(op == "new"){
            cin >> qtd >> pri;
            topic = Topic(qtd);
            cout << " done"<< endl;
        }else if(op == "in"){
            string nome;
            int idade;
            cin >> nome >> idade;
            if(topic.reservar(new Passageiro(nome, idade), qtd, pri)){
                cout << " done" << endl;
            }
        }else if(op == "out"){
            string nome;
            cin >> nome;
            if(topic.remover(nome)){
                cout << " done" << endl;
            }
            else {
                cout << "Fail: " << nome << " nao esta na topic" << endl;
            }
        }
    }
}
