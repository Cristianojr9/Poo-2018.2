#include <iostream>
#include <sstream>
using namespace std;

class Pet{
private:
    int hungry,energy,clean;
    int hungryMax,energyMax,cleanMax;
    int diamonds = 0, age = 0;
    bool vivo;
public:

    int getHungry(){ 
        return this->hungry;
    }int getEnergy(){ 
        return this->energy;
    }int getClean(){
        return this->clean;
    }int getHungryMax(){
        return this->hungryMax;
    }int getEnergyMax(){ 
        return this->energyMax;
    }int getCleanMax(){ 
        return this->cleanMax; 
    }int getDiamonds(){ 
        return this->diamonds; 
    }int getAge(){ 
        return this->age;
    }
    
    void setHungry(int hungry){
        if (hungry < 0){
            this->hungry = 0;
        }else{
            this->hungry = hungry;
    }
}    
    void setEnergy(int energy){ 
        this->energy = energy; 
    }void setClean(int clean){ 
        this->clean = clean; 
    }void setHungryM(int hungryMax){ 
        this->hungryMax = hungryMax; 
    }void setEnergyM(int energyMax){ 
        this->energyMax = energyMax; 
    }void setCleanMax(int cleanMax){ 
        this->cleanMax = cleanMax;
    }void setDiamonds(int diamonds){ 
        this->diamonds = diamonds; 
    }void setAge(int age){ 
        this->age = age;
    }void setVivo(bool vivo){
        this->vivo = vivo;
    }

    Pet(int energyMax = 0, int hungryMax = 0, int cleanMax = 0){
        this->hungry = hungryMax;
        this->hungryMax = hungryMax;
        this->energy = energyMax;
        this->energyMax = energyMax;
        this->clean = cleanMax;
        this->cleanMax = cleanMax;
}   
    string toString(){
        stringstream ss;
        ss << "E:" << getEnergy() << "/" << getEnergyMax() << ", "
             << "H:" << getHungry() << "/" << getHungryMax() << ", "
             << "C:" << getClean() << "/" << getCleanMax() << ", "
             << "D:" << getDiamonds() << ", " << "A:" << getAge() << endl;
        return ss.str();
    }

    bool morreu(){
        if(getEnergy() <= 0){
            setEnergy(0);
            cout << "fail: pet morreu de fraqueza\n";
            vivo = false;
            return true;
        }else if(getHungry() <= 0){
            setHungry(0);
            vivo = false;
            cout << "fail: pet morreu de fome\n";
            return true;
        }else if(getClean() <= 0){
            setClean(0);
            vivo = false;
            cout << "fail: pet morreu de sujeira\n";
            return true;
        }
        return false;
    }

    void jogar(){
        if(vivo = false){
            cout << "fail: pet esta morto\n";
            return;
        }else{
            setEnergy(getEnergy() - 2);
            setHungry(getHungry() - 1);
            setClean(getClean() - 3);
            morreu();
            setAge(getAge() + 1);
            setDiamonds(getDiamonds() + 1);
    }
}
    void comer(){
        if(vivo = false){
            cout << "fail: pet esta morto\n";
            return;
        }else{
            setEnergy(getEnergy() - 1);
            setHungry(getHungry() + 4);
            setClean(getClean() - 2);
            setAge(getAge() + 1);
        }
    }

    void dormir(){
        if(vivo = false){
            cout << "fail: pet esta morto\n";
            return;
        }else{
            setHungry(getHungry() - 1);
            setAge(getAge() + (getEnergyMax() - getEnergy()));
            setEnergy(getEnergyMax());
    }
}
    void limpar(){
        if(vivo = false){
            cout << "fail: pet esta morto\n";
            return;
        }else{
            setHungry(getHungry() - 1);
            setEnergy(getEnergy() - 3);
            setAge(getAge() + 2);
            setClean(getCleanMax());
        }
    }
};

class Controller{
public:
    Pet pet;

    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if(op == "init"){
            int energyMax, hungryMax, cleanMax;
            in >> energyMax >> hungryMax >> cleanMax;
            pet = Pet(energyMax, hungryMax, cleanMax);
            out << "success" << endl;
        }else if(op == "show"){
            out << pet.toString();
        }else if(op == "play"){
            pet.jogar();
        }else if(op == "eat"){
            pet.comer();
        }else if(op == "sleep"){
            pet.dormir();
        }else if(op == "clean"){
            pet.limpar();
        }return out.str();
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
