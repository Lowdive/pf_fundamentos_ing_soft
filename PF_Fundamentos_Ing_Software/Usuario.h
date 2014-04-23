class Usuario
{
private:
    string nombre;
    int id;
    string pass;
public:
    Usuario();
    Usuario(string n, int iD, string psw);
    string getUsername();
    void setUsername(string n);
    int getIDu();
    void setIDu(int iD);
    string getPass();
    void setPass(string psw);
    bool autenticar(string pass);
};

Usuario::Usuario()
{
    nombre="Juan";
    id=0;
    pass="user";
}

Usuario::Usuario(string n, int iD, string psw)
{
    nombre=n;
    id=iD;
    pass=psw;
}

string Usuario::getUsername()
{
    return nombre;
}

void Usuario::setUsername(string n)
{
    nombre=n;
}

int Usuario::getIDu()
{
    return id;
}

void Usuario::setIDu(int iD)
{
    id=iD;
}

string Usuario::getPass()
{
    return pass;
}

void Usuario::setPass(string psw)
{
    pass=psw;
}

bool Usuario::autenticar(string pass)
{
    //if pass==????
}
