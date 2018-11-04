#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
using namespace std;
class Nota{
    string titulo, texto;
public:
    Nota(string titulo = "", string texto = ""){
        this->titulo = titulo;
        this->texto = texto;
    }
    string toString(){
        return "[" + titulo + ";" + texto + "]";
    }
};

class Usuario{
public:
    string username, senha;
    map<string, Nota> notas;

    Usuario(string username = "", string senha = ""){
        this->username = username;
        this->senha = senha;
    }

    bool changePass(string velhaSenha, string novaSenha){
        if(senha == velhaSenha){
            senha = novaSenha;
            cout << "  senha alterada com sucesso\n";
            return true;
        } throw "senha atual errada\n";
    }
    void addNote(string titulo, string texto){
        if(!existsNote(titulo))
            notas[titulo] = Nota(titulo, texto);
        else
            throw "ja existe nota com este titulo\n";
    }
    bool existsNote(string titulo){
        auto it = notas.find(titulo);
        if(it != notas.end())
            return true;
        return false;
    }
    void showNotes(){
        cout << "  " + username << endl;
        for(auto& it : notas)
            cout << "  " + it.second.toString() << endl;
    }
    void toString(){
        cout << "  " + username + ":" + senha;
    }
};

class Sistema{
    Usuario* current = nullptr;
    map<string, Usuario> usuarios;
public:
    bool addUser(string user, string senha){
        if(!exists(user)){
            usuarios[user] = Usuario(user, senha);
            return true;
        }
        throw "usuario ja cadastrado\n";
    }
    bool exists(string user){
        auto it = usuarios.find(user);
        if(it != usuarios.end())
            return true;
        return false;
    }
    Usuario* login(string id, string senha){
        current = getUser(id);
        if(current->username != id)
            throw "user nao cadastrado\n";
        else if(current->senha != senha)
            throw "senha incorreta\n";
        return current;
    }
    Usuario* getUser(string id){
        auto it = usuarios.find(id);
        if(usuarios.find(id) != usuarios.end());
            return &it->second;
        throw "usuario nao cadastrado\n";
    }
    void toString(){
        cout << "  Usuarios: [";
        for(auto pair: usuarios)
            cout << pair.second.username + " ";
        cout << "]";
    }
};

class Controller{
    Sistema sistema;
    Usuario* currentUser = nullptr;
public:
    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
            if(op == "login"){
                string id, senha;
                in >> id;
                in >> senha;
                currentUser = sistema.login(id, senha);
                out << "sucess\n";
            }else if(op == "logout"){
                currentUser = nullptr;
                out << "deslogado com sucesso\n";
            }else if(op == "adduser"){
                string id, senha;
                in >> id;
                in >> senha;
                sistema.addUser(id, senha);
                out << "usuario cadastrado\n";
            }else if(op == "changepass"){
                string senhaantiga, novasenha;
                in >> senhaantiga >> novasenha;
                currentUser->changePass(senhaantiga, novasenha);
            }else if(op == "addnote"){
                string titulo, texto;
                in >> titulo;
                getline(in, texto);
                currentUser->addNote(titulo, texto);
                out << "sucess\n";
            }
            else if(op == "shownotes"){
                currentUser->showNotes();
            }
            else if(op == "showusers"){
                sistema.toString();
            }
        return out.str();
    }

    void exec(){
        string line;
            while(true){
                getline(cin, line);
                if (line == "end")
                return;
            cout << shell(line);
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}
