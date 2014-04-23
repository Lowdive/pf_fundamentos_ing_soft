#include <iostream>
#include <string>
using namespace std;
#include "Pais.h"
#include "Universidad.h"

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

    Universidad udef;
    Universidad uconID;
    Universidad uconIDNom;
    udef.muestraUni();
    uconID.setUIdent(5);
    uconID.muestraUni();
    uconIDNom.setUIdent(3);
    uconIDNom.setUNom("Brasil");
    uconIDNom.muestraUni();
    cout << "Hello world!" << endl;
    return 0;
}
