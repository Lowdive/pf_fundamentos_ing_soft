class Pais
{
private:
    int id;
    string nombre;
    Pais(); // inicializar con nada
    Pais(string ident); // "<id>",""
    Pais(string ident, string nom); // "<id>", "nom"
    string getIdent();
    void setIdent(string i);
    string getDat();
    void setDat(string n);
};
