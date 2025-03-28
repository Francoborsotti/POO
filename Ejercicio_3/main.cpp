#include <iostream>
#include <vector>
#include <windows.h>
#include <psapi.h>

using namespace std;

SIZE_T getCurrentMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.PrivateUsage;
}

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
    vector<Auto>autos;

    while(true){
        int kilometro;
        string marca;
        SIZE_T memoryUsage = getCurrentMemoryUsage();

        if ((memoryUsage/ (1024 * 1024)) > 200){
            break;
        }

        cout << "introduzaca un kilometraje" <<endl;
        cin >> kilometro;
        cout << "introduzca una marca" <<endl;
        cin >> marca;
        autos.push_back(Auto(kilometro, marca));

    }
    cout <<"cantidad de autos:"<< autos.size();
}
