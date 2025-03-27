#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Poste{
private:
    int altura;
    float diametro;
public:
    Poste(int altura, float diametro) : altura(altura), diametro(diametro) {}

    int getAltura() const{
        return altura;
    }

    float getDiametro() const{
        return diametro;
    }
};

int main(){
    vector<Poste> Postes;

    Postes.push_back(Poste(14, 2.4));
    Postes.push_back(Poste(11, 1.4));
    Postes.push_back(Poste(9, 5.4));
    Postes.push_back(Poste(12, 3.4));
    Postes.push_back(Poste(17, 7.4));

    //muestra
    cout <<"sin ordenar"<<endl;
    for(const auto& Poste : Postes){
        cout << "Altura:" << Poste.getAltura()<< endl << "Diametro:" << Poste.getDiametro()<<endl;
    }

    //ordenamiento
    std::sort(Postes.begin(), Postes.end(), [](const Poste& a, const Poste& b) {
        return a.getAltura() < b.getAltura();
    });

    //muestra
    cout <<"ordenado" << endl;
    for(const auto& Poste : Postes){
        cout << "Altura:" << Poste.getAltura()<< endl << "Diametro:" << Poste.getDiametro()<<endl;
    }
}
