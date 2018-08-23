#include <iostream>
using namespace std;

struct Carro{
    float tanque;
    float tanqueMax;
    int pessoas;
    int passMax;
    float distancia;

};

bool entrar(Carro &carro){
    if( carro.pessoas == carro.passMax ){
        return false;
    }else{
        carro.pessoas = carro.pessoas + 1;
        return true;
    }
}

bool sair(Carro &carro){
    if( carro.pessoas == 0 ){
        return false;
    }else{
        carro.pessoas = carro.pessoas - 1;
        return true;
    }

}
void abastecer(Carro &carro, float gasolina){
    if( gasolina >= carro.tanqueMax ){
        carro.tanque = 10;
        cout << "done" << endl;
    }else if( gasolina > 0 && gasolina < carro.tanqueMax ){
            carro.tanque = gasolina + carro.tanque;
            if( carro.tanque > carro.tanqueMax ){
            carro.tanque = 10;
        }
        cout << "done" << endl;
    }
}

void dirigir(Carro &carro, float andar){
    if(carro.pessoas == 0){
        cout << "fail: nao ha ninguem no carro" << endl;
    }else if(andar > ( carro.tanque*10 )){
        cout << "fail: gasolina insuficiente" << endl;
    }else{
        carro.tanque = carro.tanque - ( andar / 10 );
        carro.distancia = carro.distancia + andar;
        cout << "done" << endl;
    }
}

int main (){
    Carro carro = {0, 10, 0, 2, 0};
    string op;
    float gas = 0,km = 0;
    while(true){
        cin >> op;
   	    if(op == "show"){
                cout << "pass: " << carro.pessoas << ", gas: "<< carro.tanque << ", km: " << carro.distancia << endl;
            }if( op == "in" ){
                if(entrar(carro) == false){
                    cout << "fail: limite de pessoas atingido" << endl;
                }else{
                    cout << "done" << endl;
                }
            }else if( op == "out" ){
                if( sair(carro) == false ){
                    cout << "fail: nao ha ninguem no carro" << endl;
                }else{
                    cout << "done" << endl;
            }else if( op == "fuel" ){
                cin >> gas;
                abastecer(carro,gas);
            }else if( op == "drive" ){
                cin >> km;
                dirigir(carro,km);
            }
    }
}
