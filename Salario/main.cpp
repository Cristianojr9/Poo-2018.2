#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Funcionario{
protected:
    string name, profissao;
    int qtd_diaria = 0, max_diaria, bonus = 0, salario;
public:
    Funcionario(string name):
        name(name)
	{
	}

    virtual string getName() = 0;
    virtual string getProfiss() = 0;
    virtual int getDiaria() = 0;
    virtual int getMaxDiaria() = 0;
    virtual void calcSalario() = 0;
    virtual string toString() = 0;
    virtual void setBonus(int val){
		bonus = val;
	}
    virtual void addDiaria(){
		this->qtd_diaria += 1;	
	}
};

class Professor : public Funcionario{
    string profissao = {"Professor"};
    int max_diaria = {2};
    char classe;
public:
    Professor(string name, char classe):
        Funcionario(name), classe(classe)
	{
	}

    virtual string getName(){
		return name;
	} 
    virtual string getProfiss(){
		return profissao;
	}
    virtual int getDiaria(){
		return qtd_diaria;
	}
    virtual int getMaxDiaria(){
		return max_diaria;
	}        

    void calcSalario(){
        switch(classe){
            case 'A': salario = 3000; break;
            case 'B': salario = 5000; break;
            case 'C': salario = 7000; break;
            case 'D': salario = 9000; break;
            case 'E': salario = 11000; break;
        }
        salario += 100 * qtd_diaria + bonus;
    }
    string toString(){
        stringstream ss;
        ss << profissao + " " + name + " classe " + classe + "\n"
        << "  salario " + to_string(salario);
        return ss.str();
    }
};

class SerTecAdm : public Funcionario{
    string profissao = {"Fulano"};
    int max_diaria = {1}, nivel;
public:
    SerTecAdm(string name, int nivel):
        Funcionario(name), nivel(nivel){}

    virtual string getName(){
		return name;
	} 
    virtual string getProfiss(){
		return profissao;
	}
    virtual int getDiaria(){
		return qtd_diaria;
	}
    virtual int getMaxDiaria(){
		return max_diaria;
	}

    void calcSalario(){
        salario = 3000 + 300 * nivel + 100 * qtd_diaria + bonus;
    }
    string toString(){
        stringstream ss;
        ss << profissao + " " + name + " nivel " + to_string(nivel) + "\n" << "  salario " + to_string(salario);
        return ss.str();
    }
};

class Terceirizado : public Funcionario{
    string profissao = {"Tercerizado"};
    int max_diaria = {-1}, horastrab;
    string adicsalub;
public:
    Terceirizado(string name, int ht, string as):
        Funcionario(name), horastrab(ht), adicsalub(as){}

    virtual string getName(){
		return name;
	} 
    virtual string getProfiss(){
		return profissao;
	}
    virtual int getDiaria(){
		return qtd_diaria;
	}
    virtual int getMaxDiaria(){
		return max_diaria;
	}

    void calcSalario(){
        salario = 4 * horastrab + bonus;
        if(adicsalub == "sim")
            salario += 500;
    }
    string toString(){
        stringstream ss;
        string adicional = "salubre";
        if(adicsalub == "sim")
            adicional = "insalubre";    
        ss << profissao + " " + name + " " + to_string(horastrab) + "h " << adicional  + "\n" + "  salario " + to_string(salario);        
        return ss.str();
    }
};

template<typename T>
class Sistema{
    map<string, T*> data;
public:
    bool exists(string k){
        auto it = data.find(k);
        if(it != data.end())
            return true;
        return false;
    }
    bool addUser(string k, T* v){
        if(!exists(k)){
            data[k] = v;
            return true;
        }
        throw "fail: usuario ja cadastrado";
    }
    void rmUser(string k){
        auto user = getUser(k);
        data.erase(k);
        cout << "  " + user->getProfiss() + " " + user->getName() + " foi removido!";
        delete user;
    }
    T* getUser(string k){
        auto it = data.find(k);
        if(it != data.end())
            return it->second;
        throw "fail: funcionario " + k + " nao existe";
    }
    void refreshSalario(T* t){
        t->calcSalario();           
    }
    void addDiaria(string k){
        auto user = getUser(k);
        if(dynamic_cast<Terceirizado*>(user))
            throw "fail: Ter nao pode receber diarias";
        else if(user->getMaxDiaria() >= user->getDiaria())
            user->addDiaria();
        else
            throw "fail: limite de diarias atingido";
    }
    void setBonus(int bonus){
        bonus = bonus / data.size();
        for(auto& pair : data){
            pair.second->setBonus(bonus);
        }
    }
    string toString(){
        stringstream ss;
        for(auto pair : data)
            ss << pair.second->toString()
               << endl << "  ";
        return ss.str();
    }
};

class Controller{
    Sistema<Funcionario> Sist;
public:
    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;

        in >> op;

        try{
            if(op == "addProf"){
                string name;
                char level;
                in >> name >> level;
                Professor* P = new Professor(name, level);
                if(!Sist.addUser(name, P))
                    delete P;
                out << "done";
            }
            else if(op == "addSta"){
                string name;
                int level;
                in >> name >> level;
                SerTecAdm* S = new SerTecAdm(name, level);
                if(!Sist.addUser(name, S))
                    delete S;
                out << "done";
            }
            else if(op == "addTer"){
                string name, salub;
                int hours_work;
                in >> name >> hours_work >> salub;
                Terceirizado * T = new Terceirizado(name, hours_work, salub);
                if(!Sist.addUser(name, T))
                    delete T;
                out << "done";
            }
            else if(op == "rm"){
                string name;
                in >> name;
                Sist.rmUser(name);
            }
            else if(op == "show"){
                if(in >> op){
                    Funcionario* f = Sist.getUser(op);
                    Sist.refreshSalario(f);
                    out << Sist.getUser(op)->toString();
                } else
                    out << Sist.toString();
            }
            else if(op == "addDiaria"){
                string name;
                in >> name;
                Sist.addDiaria(name);
                out << "done";
            }
            else if(op == "setBonus"){
                int bonus;
                in >> bonus;
                Sist.setBonus(bonus);
                out << "done";
            }
        }
        catch(char const* e){
			out << e;
		}
        return out.str();
    }

    void exec() {
        string line = "";
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            try {
                shell(line);
            } catch(const string& e) {
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
