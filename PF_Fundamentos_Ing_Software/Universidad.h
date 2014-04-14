class Universidad
{
private:
    int id;
    string nombre;
public:
    Universidad(); // inicializar con nada
    Universidad(int ident); // "<id>",""
    Universidad(int ident, string nom); // "<id>", "nom"
    int getUIdent();
    void setUIdent(int i);
    string getUNom();
    void setUNom(string n);
    void muestraUni();
};

Universidad::Universidad()
{
    id=1;
    nombre="ITESM";
}

Universidad::Universidad(int ident)
{
    id=ident;
    nombre="ITESM";
}

Universidad::Universidad(int ident, string nom)
{
    id=ident;
    nombre=nom;
}

int Universidad::getUIdent()
{
    return id;
}

void Universidad::setUIdent(int i)
{
    id=i;
}

string Universidad::getUNom()
{
    return nombre;
}

void Universidad::setUNom(string n)
{
    nombre=n;
}

void Universidad::muestraUni()
{
    cout << id << " " << nombre << endl;
}
