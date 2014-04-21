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
    //loop para copiar arr[] a carreras
    capacidad=60;
    tipo="normal";
}

string getProg()
{
    return nombre;
}
void setProg(string program)
{
    nombre=program;
}
string getCarr()
{
    //devuelve un string con todas las carreras?
}
void setNewCarrera(string carr) //adds to the end of the arr
{
    //recorre el arreglo, agrega al final del arreglo
}
void delCarrera(string carr) //searches for the career then deletes then fixes empty spaces
{
    //recorre el arreglo, borra la carrera que se busca y reacomoda el arreglo
}
int getCap()
{
    return capacidad;
}
void setCap(int c)
{
    capacidad=c;
}
string getTipo()
{
    return tipo;
}
void setTipo(string t)
{
    tipo=t;
}

void Programa::editarPrograma()
{
    //debería tener parámetros?
}
