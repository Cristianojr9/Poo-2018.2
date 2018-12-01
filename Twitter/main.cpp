#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

class Tweet{
public: 
    int id;
    string text;
    string username;
    vector<string> v_usrlike;

    Tweet(int id, string text = "", string username = ""):
        id(id), text(text), username(username)
    {
    }
    ~Tweet(){
    }
    string getUsername(){
        return username;
    }
    void like(string username){
        auto it = find(v_usrlike.begin(), v_usrlike.end(), username);
        if(it == v_usrlike.end())
            v_usrlike.push_back(username);
        else
            v_usrlike.erase(it);
    }  
    string toString(){
        stringstream ss;
        ss << to_string(id) + " " + username + ": " + text + " {";
        for(auto it = v_usrlike.begin(); it != v_usrlike.end(); it++){
            if(it != v_usrlike.end()-1) ss << *it + " ";
            else ss << *it;
        }
        return ss.str() + "}";
    }
};

class User{
    vector<Tweet*> v_timeline;
    vector<Tweet*> v_myTweets;
    vector<User*> v_seguidos;
    vector<User*> v_seguidores;
    int tt = 0; //tweets
public: 
    string username;
    
    User(string username = ""):
        username(username)
    {
    }
    ~User(){
    }
    void seguir(User * seguido){
        this->v_seguidos.push_back(seguido);
        seguido->v_seguidores.push_back(this);
    }
    string seguidos(){
        stringstream ss;
        for(auto it = v_seguidos.begin(); it != v_seguidos.end(); it++){
            if(it != v_seguidos.end()-1) ss << (*it)->username + " ";
            else ss << (*it)->username;
        }
        return ss.str();
    }
    string seguidores(){
        stringstream ss;
        for(auto it = v_seguidores.begin(); it != v_seguidores.end(); it++){
            if(it != v_seguidores.end()-1) ss << (*it)->username + " ";
            else ss << (*it)->username;
        }
        return ss.str();
    }
    void setTimeline(Tweet * twt){
        this->v_myTweets.push_back(twt);
        for(auto seguidor : v_seguidores){
            seguidor->v_timeline.push_back(twt);
            seguidor->tt++;
        }
    }
    string unread(){
        stringstream ss;
        if(tt == 0)
            return "  nada de novo";
        for(int i = 1; i <= tt; i++){
            ss << v_timeline[v_timeline.size()-i]->toString() + "\n";
        }
        this->tt = 0;
        return ss.str();
    }
    string myTweets(){
        stringstream ss;
        if(v_myTweets.size() == 0)
            return "  publique algum tweet";
        for(auto it = v_myTweets.end()-1; it >= v_myTweets.begin(); it--)
            ss << (*it)->toString() + "\n";
        return ss.str();
    }
    string timeline(){
        stringstream ss;
        if(v_timeline.size() == 0)
            return "  nao tem nada";
        for(auto it = v_timeline.end()-1; it >= v_timeline.begin(); it--)
            ss << (*it)->toString() + "\n";
        this->tt = 0;
        return ss.str();
    }
    string toString(){
        stringstream ss;
        ss << "  " + this->username + "\n";
        ss << "    seguidos\t[";
        ss << this->seguidos() + "]\n";
        ss << "    seguidores\t[";
        ss << this->seguidores();
        return ss.str() + "]\n";
    }
};

template<typename T>
class Repository{
    map<string, T> data;
public:
    void add(string k, T v){
        data[k] = v;
    }
    void rem(string k){
        auto it  = data.find(k);
        if(it == data.end())
            throw "entrada " + k + " nao existe";
        data.erase(it);
        delete it;
    }
    bool exists(string k){
        auto it  = data.find(k);
        if(it == data.end())
            return false;
        return true;
    }
    T* getT(string k){
        auto it = data.find(k);
        if(it == data.end())
            throw "entrada " + k + " nao existe";
        return &it->second;
    }
    vector<T*> getValues(){
        vector<T*> v_data;
        for(auto pair : data)
            v_data.push_back(pair.second);
        return v_data;
    }
    string toString(){
        stringstream ss;
        for(auto pair : data)
            ss << pair.second.toString();
        return ss.str();
    }
};

class TweetGenerator{
    int nextId = {0};
    Repository<Tweet> * p_r_tweet;
public:    
    TweetGenerator(Repository<Tweet>* r_tweet){
        this->p_r_tweet = r_tweet;
    }
    Tweet* createtwt(string username, string text){
        p_r_tweet->add(to_string(nextId), Tweet(nextId, username, text));
        nextId++;
        return p_r_tweet->getT(to_string(nextId-1));
    }
};

class Controller{
    Repository<User>* r_user;
    Repository<Tweet>* r_tweet;
    TweetGenerator* g_tweet;
public:
    Controller(){
        this->r_user = new Repository<User>;
        this->r_tweet = new Repository<Tweet>;
        this->g_tweet = new TweetGenerator(r_tweet);
    }
    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        try{
            if(op == "addUser"){
                string username;
                in >> username;
                r_user->add(username, User(username));
            }
            else if(op == "users"){
                out << r_user->toString();
            }
            else if(op == "seguir"){
                string seguidor, seguido;
                in >> seguidor >> seguido;
                r_user->getT(seguidor)->seguir(r_user->getT(seguido));
            }
            else if(op == "twittar"){
                string username, text;
                in >> username;
                getline(in, text);
                auto twt = g_tweet->createtwt(username, text);
                r_user->getT(username)->setTimeline(twt);
            }
            else if(op == "seguidores"){
                string user;
                in >> user;
                out << r_user->getT(user)->seguidores();
            }
            else if(op == "seguidos"){
                string user;
                in >> user;
                out << r_user->getT(user)->seguidos();
            }
            else if(op == "timeline"){
                string user;
                in >> user;
                out << r_user->getT(user)->timeline();
            }
            else if(op == "unread"){
                string user;
                in >> user;
                out << r_user->getT(user)->unread();
            }
            else if(op == "myTweets"){
                string user;
                in >> user;
                out << r_user->getT(user)->myTweets();
            }
            else if(op == "like"){
                string username, idtwt;
                in >> username >> idtwt;
                r_tweet->getT(idtwt)->like(username);
            }
            else
                cout << "comando invalido" << endl;
        }
        catch(string e){ out << "  fail: " + e; }
	    catch(char const* e){ out << "  fail: " << e; }
	    catch(...){ out << "  fail: ocorreu uma excecao"; }
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
    c.exec;
    return 0;
}
