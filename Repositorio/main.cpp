#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;
struct Professor{
    string nome;
    int id;
public:
    Professor(string nome = "", int id = 0):
        nome(nome), id(id){
    }
    static void toString(Professor prof){
        stringstream ss;
        ss << "  " << prof.id << ":" << prof.nome;
        cout << ss.str();
    }    
};

struct Disciplina{
    string id;
    string nome;
public:
    Disciplina(string id = "01", string nome = "aaa"):
    id(id), nome(nome){
    }
    static void toString(Disciplina dis){
        stringstream ss;
        ss << "  " << dis.id << ":" << dis.nome;
        cout << ss.str();
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
    static void toString(Aluno alu){
        stringstream ss;
        ss << "  " << alu.id << ":" << alu.curso << ":" << alu.nome;
        cout << ss.str();
    }
};

template<typename T>
class Repositorio{
    map<string, T> data;
public: 
    bool exists(string key){
        return data.find(key) != data.end();
    }
    bool add(string key, T elem){
        if(!exists(key)){
            data[key] = elem;
            return true;
        }
        return false;
    }
    bool rem(string key){
        if(exists(key)){
            data.erase(key);
            return true;
        }
        return false;
    }
    T& getT(string key, string str = ""){
        auto item = data.find(key);
        if(item != data.end())
            return item->second;
        throw "" + str + " " + key + " nao existe";
    }

    vector<T> getValues(){
        vector<T> vecT;
        for(auto& par : data)
            vecT.push_back(par.second);
        return vecT;
    }

    vector<string> getKeys(){
        vector<string> vecK;
        for(auto& par : data)
            vecK.push_back(par.first);
        return vecK;
    }

    static void toString(T t){
        stringstream ss;
        ss << t.id << ":";
        if(t.curso){
            ss << t.curso << ":";
        }
        ss << t.nome;
        cout << ss.str();
    }
};

class Controller{
    Repositorio<Aluno> repAlu;
    Repositorio<Professor> repProf;
    Repositorio<Disciplina> repDis;
public:
    void shell(string line){
        stringstream in(line);
        string op;
        in >> op; 
        if(op == "addAlu"){
                string id;
                string curso;
                string nome;
                in >> id;
                in >> curso;
                getline(in, nome);
                if(!repAlu.add(id, Aluno(id, curso, nome)))
                    throw "aluno " + id + " ja existe";
            }else if(op == "addPro"){
                int id;
                string nome;
                in >> id;
                getline(in, nome);
                if(!repProf.add(id, Professor(nome, id)))
                    throw "professor " + id + " ja existe";
            }else if(op == "addDis"){
                string id;
                string nome;
                in >> id;
                getline(in, nome);
                if(!repDis.add(id, Disciplina(id, nome)))
                    throw "disciplina " + id + " ja existe";
            }else if(op == "getAlu"){
                string id;
                in >> id;
                Aluno::toString(repAlu.getT(id, "aluno"));
            }else if(op == "getPro"){
                string id;
                in >> id;
                Professor::toString(repProf.getT(id, "professor"));
            }else if(op == "getDis"){
                string id;
                in >> id;
                Disciplina::toString(repDis.getT(id, "disciplina"));
            }else if(op == "showAlu"){
                for(auto id : repAlu.getKeys()){
                    Aluno::toString(repAlu.getT(id));
                    cout << endl;
                }
            }else if(op == "showPro"){
                for(auto id : repProf.getKeys()){
                    Professor::toString(repProf.getT(id));
                    cout << endl;
                }
            }else if(op == "showDis"){
                for(auto id : repDis.getKeys()){
                    Disciplina::toString(repDis.getT(id));
                    cout << endl;
                }
            }else if(op == "rmAlu"){
                string id;
                in >> id;
                if(!repAlu.rem(id))
                    throw "Aluno " + id + " nao existe";
            }else if(op == "rmPro"){
                string id;
                in >> id;
                if(!repProf.rem(id))
                    throw "Professor " + id + " nao existe";
            }else if(op == "rmDis"){
                string id;
                in >> id;
                if(!repDis.rem(id))
                    throw "Disciplina " + id + " nao existe";
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
    Controller c;
    c.exec();
    return 0;
}
