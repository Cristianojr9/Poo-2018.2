#include <iostream> // caso o favorito não fosse favorito, e o usuario tenta desfavoritar(bool isFav(){}) | usar o map * para mostrar os favoritos
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Fone {
public:
    string id;
    string number;

    Fone(string id = "", string number = ""){
        this->id = id;
        this->number = number;
    }

    static bool validate(string number) {
        string data = "1234567890()- ";
        for(auto c : number)
            if(data.find(c) == string::npos)
                return false;
        return true;
    }
};

class Contato : public Entry{
    string name;
    vector<Fone> fones;
    bool value {0};
public:
    Contato(string name = ""){
        this->name = name;
    }

    string getId(){
        return name;
    }

    void setFavorited(bool value){
        this->favorito = value;
    }

    bool getFav(){
        return this->favorito;
    }

    void addFone(Fone fone){
        if(!Fone::validate(fone.number))
            throw string("fone " + fone.number + " invalido");
        fones.push_back(fone);
    }

    void rmFone(size_t indice){
        if(indice < 0 || indice >= fones.size())
            throw string("indice " + to_string(indice) + " nao existe");
        fones.erase(fones.begin() + indice);
    }

    vector<Fone> getFones(){
        vector<Fone> resp;
        for(auto fone: fones)
            resp.push_back(fone);
        return resp;
    }

    string toString(){
        string saida = "";
        if(this->favorito == 1){
            saida += "@ ";
        }else if(this->favorito == 0){
            saida += "- ";
        }
        saida += this->name + " C ";
        int i = 0;
        for(auto fone : getFones())
            saida += "[" + to_string(i++) + ":" + fone.id + ":" + fone.number + "]";
        return saida;
    }
};

class Entry {
    bool favorited = false;
public:
    Entry() = 0;
    virtual ~Entry() = 0;
    virtual string getId() = 0;
    virtual void setFavorited(bool value) = 0;
    virtual bool isFavorited() = 0;
    virtual string toString() = 0;
};

class Agenda {
    map<string, Entry*> m_entries;
    map<string, Entry*> m_favorites;

public:
    void addEntry(Entry * entry){
        string id = cont.getName();
        vector<Fone> fones = cont.getFones();
        if(exists(id)){
            for(auto fone : fones){
                contatos[id].addFone(fone);
            }
            throw string("Numeros adicionados");
        }
            
        contatos[id] = cont;
    }

    void rmEntry(string id) {
        contatos.erase(id);
    }

    Contato * getEntry(string name){
        if(contatos.count(name))
            return &contatos[name];
        throw string("  contato " + name + " nao existe");
    }

    vector<Contato> getContatos(){
        vector<Contato> resp;
        for(auto& par : contatos)
            resp.push_back(par.second);
        return resp;
    }

    bool exists(string name){
        if(contatos.count(name) == 1){
            return true;
        }
    }

    void favorite(string name){
        if(exists(name)){
            contatos[name].setFavorited(1);
            favoritos[name] = getContato(name);
        }else{
            throw "O nome nao e um contato";
        }
    }

    void unfavorite(string name){
        if(exists(name)){
            contatos[name].setFavorited(0);
            favoritos.erase(name);
        }else{
            throw "O nome nao e um contato";
        }
    }

    vector<Entry*> getFavorited(){
        vector<Contato> resp;
        for(auto& par : favoritos)
            resp.push_back(*par.second);
        // for(auto cont : getContatos()){
        //     if(cont.getFav()){
        //         resp.push_back(cont);
        //     }
        
        return resp;
    }

    vector<Entry*> search(string pattern){
        vector<Contato> resp;
        for(auto& par : contatos)
            if(par.second.toString().find(pattern) != string::npos)
                resp.push_back(par.second);
        return resp;
    }

    string toString(){
        string saida = "";
        for(auto contato : getContatos())
            saida += contato.toString() + "\n";
        return saida;
    }
};



class Controller {

    Agenda agenda;
public:

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addContato"){
            string name, id_number;
            ss >> name;
            Contato cont(name);
            while(ss >> id_number){
                string id, fone;
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
                cont.addFone(Fone(id, fone));
            }
            agenda.addContato(cont);
        }
        else if(op == "rmFone"){
            string name;
            int indice;
            ss >> name >> indice;
            agenda.getContato(name)->rmFone(indice);
        }
        else if(op == "rmContato"){
            string name;
            ss >> name;
            agenda.rmContato(name);
        }
        else if(op == "agenda"){
            cout << agenda.toString();
        }
        else if(op == "search"){
            string pattern;
            ss >> pattern;
            auto resp = agenda.search(pattern);
            for(auto contato : resp)
                cout << contato.toString() << endl;
        }else if(op == "fav"){
            string name;
            ss >> name;
            agenda.favoritar(name);
            throw "done";
        }else if(op == "desfav"){
            string name;
            ss >> name;
            agenda.desfavoritar(name);
            throw string("done");
        }else if(op == "showFav"){
            string saida = "";
            auto favs = agenda.getFavoritos();
            for(auto contato : favs)
                saida += contato.toString() + "\n";
            throw saida;
        }else
            cout << "comando invalido" << endl;
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
            } catch(const char * warning){
                cout << warning << endl;
            }
        }
    }
};

int main()
{
    Controller controller;
    controller.exec();
    return 0;
}
