class Programa
{
private:
    string nombre;
    string carreras[500];
    int capacidad;
    string tipo;
public:
    Programa(); // inicializar con nada
    Programa(string nom); // "<id>",""
    Programa(string nom, string arr[], int cap, string tip); // "<id>", "nom"
    string getProg();
    void setProg(string program);
    string getCarr();
    void setNewCarrera(string carr); //adds to the end of the arr
    void delCarrera(string carr); //searches for the career then deletes then fixes empty spaces
    int getCap();
    void setCap(int c);
    string getTipo();
    void setTipo(string t);
};

Programa::Programa()
{
    nombre="Intercambio";
    carreras={"INT", "ITC", "ITIC"};
    capacidad=60;
    tipo="normal";
}

Programa::Programa(string nom)
{
    nombre=nom;
    carreras={"INT", "ITC", "ITIC"};
    capacidad=60;
    tipo="normal";
}

Programa(string nom, string arr[], int cap, string tip)
{
    nombre=nom;
    carreras=arr;
    capacidad=60;
    tipo="normal";
}

void Programa::editarPrograma()
{
    //debería tener parámetros?
}
