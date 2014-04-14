#include <iostream>
using namespace std;
#include "Pais.h"

int main()
{
    Pais def;
    Pais conID;
    Pais conIDNom;
    def.muestraPais();
    conID.setIdent(5);
    conID.muestraPais();
    conIDNom.setIdent(3);
    conIDNom.setNom("Brasil");
    conIDNom.muestraPais();
    cout << "Hello world!" << endl;
    return 0;
}
