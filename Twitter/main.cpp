#include <iostream>
#include <vector>
#include <sstream>
#include <map>
using namespace std;
class User{
public: 
    string name;
    string seguidores; 
    string seguidos;
    User(string name = ""):
        name(name)
    {
    }
};

class Tweet{
public: 
    int id;
    string msg;
    string username;

    Tweet(int id, string msg = "", string username = ""):
        id(id), msg(msg), username(username)
    {
    }

    string toString(){
        return id + " " + username + ": " + msg + "\n";
    }
};

template<typename T, typename V>
struct Repository{
    map<T, V> user;
    string _typename;
public: 
    Repository(string _typename = ""):
        _typename(_typename)
    {
    }
    
};

class Sistema{
public: 
    Repository<string, User> repUser;
    Repository<string, Tweet> repTweet;



};

struct Controller{
    
}

int main(){
    Controller c;
    c.exec;
    return 0;
}
