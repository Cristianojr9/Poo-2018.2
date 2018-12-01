#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Entry {
    bool favorited;
public:
    virtual string getId() = 0;
    virtual void setFavorited(bool value) = 0;
    virtual bool isFavorited() = 0;
    virtual string toString() = 0;
};

class Note : public Entry {
    string id;
    bool favorited = false;
    vector<string> itens;
 public:

    Note(string id = ""){
        this->id = id;
    }
    string getId(){
        return id;
    }
    void addItem(string item){
        itens.push_back(item);
    }
    void rmItem(int indice){
        itens.erase(itens.begin()+indice);
    }
    string toString(){
        int i = 0;
        string saida = id+" N [ ";
        for(auto item : itens){
            saida += to_string(i++) +": "+item + " ";
        }
        saida +="]";
        if(favorited){
                    saida+=" - Favorito: true";
            }else{
                    saida+=" - Favorito: false";
            }
        return saida;
    }
    void setFavorited(bool fv){
        favorited = fv;
    }
    bool isFavorited(){
        return favorited;
    }

};

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
    bool favorited = false;
    vector<Fone> fones;
public:

    void setFavorited(bool fv){
        favorited = fv;
    }
    bool isFavorited(){
        return favorited;
    }

    Contato(string name = ""){
        this->name = name;
    }

    string getId(){
        return name;
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
        string saida = this->name + " C ";
        int i = 0;
        for(auto fone : getFones())
            saida += "[" + to_string(i++) + ":" + fone.id + ":" + fone.number + "]";

            if(favorited){
                    saida+=" - Favorito: true";
            }else{
                    saida+=" - Favorito: false";
            }
        return saida;
    }
};


class Agenda {
public:
   map<string, Entry*> m_entries;
   map<string, Entry*> m_favorities;


    void addEntry(Entry * entry){
        m_entries.insert(make_pair(entry->getId(), entry));
    }
    void rmEntry(string id){
        m_entries.erase(id);
    }

    void favorite(string idEntry){
        auto it =  m_entries.find(idEntry);
        if(it != m_entries.end()){
            m_entries.at(idEntry)->setFavorited(true);
            m_favorities.insert(make_pair(idEntry, m_entries.at(idEntry)));
        }else{
            throw "fail: erro";
        }
    }
    void unfavorite(string idEntry){
        auto it =  m_entries.find(idEntry);
        if(it != m_entries.end()){
            m_entries.at(idEntry)->setFavorited(false);
            m_favorities.erase(idEntry);
        }else{
            throw "fail: erro";
        }
    }
    vector<Entry*> getFavorited(){
        vector<Entry*> favoritos;
        for(auto it : m_favorities){
            favoritos.push_back(it.second);
        }
        return favoritos;
    }
    Entry * getEntry(string id){
        auto it =  m_entries.find(id);
        if(it != m_entries.end()){
            return m_entries.at(id);
        }else{
            throw "fail: errouuu";
        }
    }
    vector<Entry*> getEntries(){
        vector<Entry*> entradas;
        for(auto it : m_entries){
            entradas.push_back(it.second);
        }
        return entradas;
    }

    string toString(){
        stringstream ss;
        for(auto it : m_entries){
            ss << it.second->toString()<<endl;
        }
        return ss.str();
    }
};

class AgendaMaster : public Agenda{
public:
    Contato * getContato(string id){
        if(Contato *contato = dynamic_cast<Contato*>(getEntry(id))){
            return contato;
        }
        return nullptr;
    }
    Note * getNote(string id){
        if(Note *note = dynamic_cast<Note*>(getEntry(id))){
            return note;
        }
        return nullptr;
    }


};
class Controller {

    AgendaMaster agenda;
public:

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addContato"){
            string name, id_number;
            ss >> name;
            string id, fone;

            agenda.addEntry(new Contato(name));
            while(ss >> id_number){
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
            }
            Contato *contato = agenda.getContato(name);
            contato->addFone(Fone(id, fone));
        }else if(op == "addNote"){
            string name;
            ss >> name;
            agenda.addEntry(new Note(name));
        }else if(op == "rmNote"){
            string name;
            ss >> name;
            agenda.rmEntry(name);
        }else if(op == "addFone"){
            string name, id_number;
            ss >> name;
            string id, fone;
            while(ss >> id_number){
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
            }
            Contato *contato = agenda.getContato(name);
            contato->addFone(Fone(id, fone));
        }else if(op == "rmFone"){
            string name;
            int indice;
            ss >> name >> indice;
        
            Contato *contato = agenda.getContato(name);
            contato->rmFone(indice);

        }else if(op == "addItem"){
            string name, anotacao="", comando;
            ss >> name;
             while(ss >> comando){
                anotacao+=comando+" ";
            }
            Note *note = agenda.getNote(name);
            note->addItem(anotacao);
        }else if(op == "rmItem"){
            string name;
            int indice;
            ss >> name;
            ss >> indice;

            Note *note = agenda.getNote(name);
            note->rmItem(indice);
        }else if(op == "rmContato"){
            string name;
            ss >> name;
            agenda.rmEntry(name);
        }else if(op == "agenda"){
            cout << agenda.toString();
        }else if(op == "search"){
            string pattern;
            ss >> pattern;
            auto it = agenda.getEntry(pattern);
            cout << it->toString() << endl;
        }else if(op == "fav"){
            string name;
            ss >> name;
            agenda.favorite(name);
        }else if(op == "desfav"){
            string name;
            ss >> name;
            agenda.unfavorite(name);
        }else if(op == "showFav"){
            for(auto *it : agenda.getFavorited()){
                cout << it->toString() << endl;
            }
        }else
            cout << "comando invalido" << endl;
    }


    void exec() {
        string line = "";
        while(true){
            getline(cin, line);
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
    Controller controller;
    controller.exec();
    return 0;
}
