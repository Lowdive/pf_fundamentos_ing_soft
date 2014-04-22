class Usuario
{
private:
    string nombre;
    int id;
    string pass;
public:
    string getUser();
    void setUser();
    int getIDu();
    void setIDu();
    string getPass();
    void setPass();
    bool autenticar(string pass);
};

bool Usuario::autenticar(string pass)
{
    //if pass==????
}
