#include <iostream>
#include <vector>

using namespace std;

class Auto{
private:
    int kilometros;
    string marca;
public:
    Auto(int kilometros, string marca) : kilometros(kilometros), marca(marca) {}

    int saberKilometros(){
        return kilometros;
    }

    string saberMarca(){
        return marca;
    }
};

int main(){
    bool aux = true;
    while(aux){
        int kilometro;
        string marca;
        cout << "introduzaca un kilometraje" <<endl;
        cin >> kilometro;
        cout << "introduzca una marca" <<endl;
        cin >> marca;

    }
    Auto auto1(1000, "fiat");
    Auto auto2(1200, "reno");
    Auto auto3(1300, "chebrolet");
    Auto auto4(1400, "toyota");
    Auto auto5(1500, "ford");

    vector<Auto> Autos;


}
