class Pais
{
private:
    int id;
    string nombre;
public:
    Pais(); // inicializar con nada
    Pais(int ident); // "<id>",""
    Pais(int ident, string nom); // "<id>", "nom"
    int getIdent();
    void setIdent(int i);
    string getNom();
    void setNom(string n);
    void muestraPais();
};

Pais::Pais()
{
    id=1;
    nombre="Mexico";
}

Pais::Pais(int ident)
{
    id=ident;
    nombre="Mexico";
}

Pais::Pais(int ident, string nom)
{
    id=ident;
    nombre=nom;
}

int Pais::getIdent()
{
    return id;
}

void Pais::setIdent(int i)
{
    id=i;
}

string Pais::getNom()
{
    return nombre;
}

void Pais::setNom(string n)
{
    nombre=n;
}

void Pais::muestraPais()
{
    cout << id << " " << nombre << endl;
}
