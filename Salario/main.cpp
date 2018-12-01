#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Funcionario{
    string nome;
    int qtd_diaria = 0, max_diaria;
	double bonus = 0;
public:
    Funcionario(string nome):
        nome(nome)
	{
	}
	virtual string getName() = 0;
    virtual int getDiaria() = 0;
    virtual int getMaxDiaria() = 0;
    virtual string toString() = 0;
    virtual void setBonus(double val){
		bonus = val;
	}
    virtual void addDiaria(){
		this->qtd_diaria += 1;
	}
};

class Professor : public Funcionario{
    int maxdiaria = {2};
    char classe;
public:
    Professor(string nm, char cs):
        Funcionario(nm), classe(cs)
	{
	}
	virtual string getName(){
		return nome;
	} 
    virtual string getProfissao(){
		return profissao;
	}
    virtual int getDiaria(){
		return diaria;
	}
    virtual int getMaxDiaria(){
		return maxdiaria;
	}        

    void calcSalario(){
        switch(classe){
            case 'A': salario = 3000; 
				break;
            case 'B': salario = 5000; 
				break;
            case 'C': salario = 7000; 
				break;
            case 'D': salario = 9000; 
				break;
            case 'E': salario = 11000; 
				break;
        }
        salario += 100 * diaria + bonus;
    }
    string toString(){
        stringstream ss;
        ss << profissao + " " + nome + " classe " + classe + "\n" << "  salario " + to_string(salario);
        return ss.str();
    }
};

class SerTecAdm : public Funcionario{
	string nome;
    int maxdiaria = {1}, nivel;
public:
    SerTecAdm(string nome, int nivel):
        nome(nome), nivel(nivel)
	{
	}

    virtual string getName(){
		return nome;
	} 
    virtual int getDiaria(){
		return diaria;
	}
    virtual int getMaxDiaria(){
		return maxdiaria;
	}

    void calcSalario(){
        salario = 3000 + 300 * nivel + 100 * diaria + bonus;
    }
    string toString(){
        stringstream ss;
        ss << profissao + " " + nome + " nivel " + to_string(nivel) + "\n"
        << "  salario " + to_string(salario);
        return ss.str();
    }
};

class Terceirizado : public Funcionario{
    string profissao;
    int maxdiaria = {-1}, horastrab;
    string adicsalub;
public:
    Terceirizado(string nm, int ht, string as):
        Funcionario(nm), horastrab(ht), adicsalub(as)
	{
	}
	virtual string getName(){
		return nome;
	} 
    virtual string getProfiss(){
		return profissao;
	}
    virtual int getDiaria(){
		return diaria;
	}
    virtual int getMaxDiaria(){
		return maxdiaria;
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
        ss << profissao + " " + nome + " " + to_string(horastrab) + "h "
        << adicional  + "\n" + "  salario " + to_string(salario);        
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
    Sistema<Funcionario> mySis;
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
                if(!mySis.addUser(name, P))
                    delete P;
                out << "done";
            }
            else if(op == "addSta"){
                string name;
                int level;
                in >> name >> level;
                SerTecAdm* S = new SerTecAdm(name, level);
                if(!mySis.addUser(name, S))
                    delete S;
                out << "done";
            }
            else if(op == "addTer"){
                string name, salub;
                int hours_work;
                in >> name >> hours_work >> salub;
                Terceirizado * T = new Terceirizado(name, hours_work, salub);
                if(!mySis.addUser(name, T))
                    delete T;
                out << "done";
            }
            else if(op == "rm"){
                string name;
                in >> name;
                mySis.rmUser(name);
            }
            else if(op == "show"){
                if(in >> op){
                    Funcionario* f = mySis.getUser(op);
                    mySis.refreshSalario(f);
                    out << mySis.getUser(op)->toString();
                } else
                    out << mySis.toString();
            }
            else if(op == "addDiaria"){
                string name;
                in >> name;
                mySis.addDiaria(name);
                out << "done";
            }
            else if(op == "setBonus"){
                int bonus;
                in >> bonus;
                mySis.setBonus(bonus);
                out << "done";
            }
        }
        catch(char const* e){out << e;}
        catch(string e){out << e;}
        catch(...){out << "fail: ocorreu uma exceção";}
        
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
