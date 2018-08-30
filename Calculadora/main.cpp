#include <stdio.h>
#include <iostream>
using namespace std;

struct Calc{
    int bateria;
    int limiteBateria;

    void charge(int carga){
        bateria += carga;
        if(bateria > limiteBateria)
            bateria = limiteBateria;
    }
    float soma(float a, float b, bool * deu_certo){
        if(gastarBateria()){
            *deu_certo = true;
            return a + b;
        }
        *deu_certo = false;
        return 0;
    }
    float div(float a, float b){
        if(gastarBateria()){
            if(b == 0){
                puts("fail: nao posso dividir por 0");
                return 0;
            }
            return a/b;
        }
        return 0;
    }
    float mult(float a, float b, bool * deu_certo){
        if(gastarBateria()){
            *deu_certo = true;
            return a * b;
        }
        *deu_certo = false;
        return 0;
    }
    bool gastarBateria(){
        if(bateria > 0){
            this->bateria -= 1;
            return true;
        }
        puts("fail: bateria insuficiente");
        return false;
    }
};

int main(){
    string op;
    Calc calc = {2, 5};
    while(true){
        cin >> op;
        if(op == "help"){
            puts("soma _a _b; div _a _b; mult _a _b; show; charge _carga;");
        }else if(op == "soma"){
            float a, b;
            bool deu_certo;
            cin >> a >> b;
            float resp = calc.soma(a, b, &deu_certo);
            if(deu_certo)
                cout << "  = " << resp << endl;;
        }
        else if(op == "div"){
            float a, b;
            cin >> a >> b;
            cout << "  = " << calc.div(a, b) << endl;
        }else if(op == "charge"){
            int a;
            cin >> a;
            calc.charge(a);
        }else if(op == "mult"){
            float a,b;
            bool deu_certo;
            cin >> a >> b;
            cout << " = " << calc.mult(a,b, &deu_certo) << endl; 
        }else if(op == "show"){
            cout << "  bateria = " << calc.bateria << endl;
        }else if(op == "fim")
            break;
    }
    return 0;
}
