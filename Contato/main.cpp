#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

struct Fone{
	string label;
	string numero;

	Fone(string label = "alguem", string numero = "929292"){
		this->label = label;
		this->numero = numero;
	}
	string toString(){
		stringstream ss; 
		ss << this->label << ":" << this->numero;
		return ss.str();
	}

};

struct Contato{

	vector<Fone> fones;
	string nome;

	Contato(string nome = "boulos"){
		this->nome;
	}

	void add(Fone fone){
		fones.push_back(fone);
	}

	void remover(string foneID){
		for (int i = 0; i < (int) fones.size(); i++)
			if(fones[i].label == foneID){
				fones.erase(fones.begin() + i);
			}
	}

	string toString(){
		stringstream ss;
		ss << this->nome << "=>";
		for (int i = 0; i < (int) fones.size(); i++)
			ss << "[" << i << ":" << fones[i].label << ":" << fones[i].numero << "]";
		return ss.str();
	}
};


int main(){
	Contato c;
	while(true){
		string op;
		cin >> op;
		if(op == "add"){
			string label,fone;
			cin >> label >> fone;
			c.add(Fone(label,fone));
			cout << "sucess" << endl;
		}else if(op == "init"){
			string nome;
			cin >> nome;
			c.nome = nome;
			cout << "sucess" << endl;
		}else if(op == "show"){
			cout << c.toString() << endl;
		}else if(op == "rm"){
			string id;
			cin >> id;
			c.remover(id);		
			cout << "sucess" << endl;
		}else if(op == "end"){
		    break;
		}
	}
	
	return 0;
}
