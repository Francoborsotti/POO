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
        SIZE_T memoryUsage = getCurrentMemoryUsage();

        if ((memoryUsage/ (1024 * 1024)) > 200){
            break;
        }
        autos.push_back(Auto(1000, "fiat"));

    }
    cout <<"cantidad de autos:"<< autos.size();
}
