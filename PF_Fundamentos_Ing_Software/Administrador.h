class Administrador
{
private:
    int id;
    string nombre;
public:
    Administrador();
    Administrador(int ID, string nom);
    int getIDadmin();
    void setIDadmin(int newID);
    string getNomAdmin();
    void setNomAdmin(string newAdmin);
};
