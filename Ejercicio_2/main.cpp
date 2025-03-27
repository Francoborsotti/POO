#include <iostream>
#include <vector>

using namespace std;

string sinEspacio(string a){
    string resultado;
    for (char c : a) {
        if (c != ' ') {
            resultado += c;
        }
    }
    return resultado;
}
int main(){
    vector<string>cadena;
    cadena.push_back("pan comido");
    cadena.push_back("dar en el calvo");
    cadena.push_back("echar lena al fuego");
    cadena.push_back("ir al grano");
    cadena.push_back("meter la pata");

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (sinEspacio(cadena[j]) > sinEspacio(cadena[j+1])) {
                std::swap(cadena[j], cadena[j + 1]);
            }
        }
    }
    for(const auto& string : cadena){
        cout << string <<endl;
    }
}
