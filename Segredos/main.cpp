#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
class Segredo{
    int nivel;
    string texto;
public:
    Segredo(int nivel = 0, string texto = ""){
        this->nivel = nivel;
        this->texto = texto;
    }
    void setNivel(int valor){
        if(valor < 0 || valor > 10)
            throw "fail: nivel invalido";
        this->nivel = valor;
    }
    
    string toString(){
        return "[" + texto + "] " + to_string(nivel); 
    }
};
 struct User{
    string id;
    string pass;
    Segredo seg;
    User(string id = "", string pass = ""){
        this->id = id;
        this->pass = pass;
    }
    string getId(){
        return id;
    }
    string getPass(){
        return pass;
    }
    string toString(){
        return id + seg.toString();
    }
    bool verificar(string pass){
        return this->pass == pass;
    }
};
 struct Sistema{
    vector<User> usuarios;
    string adminName;
    Sistema(){
        adminName = "admin";
        usuarios.push_back(User("admin", "admin"));
    }
    // saber se existe usuarios
    User& getUser(string user){
        for(auto &user : usuarios)
            if(user.getId() == user.id)
                return user;
        throw "fail: usuario não existe";
    // add usuarios
    }
    void addUser(User user){
        for(auto &usu : usuarios)
            if(user.getId() == usu.getId())
                throw "fail: usuario ja existe";
        usuarios.push_back(user);
    }
    
};
 struct Controller{
    Sistema sist;
    User * current;
public:   
    Controller(){
        current = nullptr;
    }
    void shell(string line){
        stringstream in(line);
        string op;
        in >> op;
        if(op == "addUser"){
            string nome, pass;
            in >> nome >> pass;
            sist.addUser(User(nome, pass));
            cout << "sucess\n";
        }else if(op == "login"){
            string nome, pass;
            in >> nome, pass;
            if(current != nullptr)
                throw "fail: ja existe alguem logado";
            User& user = sist.getUser(nome); 
            if(!user.verificar(pass))
                throw "fail: senha invalida";
            current = &user;
        }else if(op == "logout"){
            if(current == nullptr)
                throw "fail: ninguem logado";
            current = nullptr;
        }else if(op == "show"){
            cout << current->toString() << endl;
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
