#include <string>

using namespace std;
class Usuario
{
protected:
    string nombre;
    int id;
    char tipo;
public:
    Usuario();
    Usuario(int iD, string n, char tipo);
    string getNombre();
    void setNombre(string n);
    int getId();
    void setId(int iD);
    bool esAdiministrador(){return tipo=='A';};
    bool esEstudiante(){return tipo=='E';};
    static Usuario* auth(sqlite3 *db);
    virtual void display(){};
};

Usuario::Usuario()
{
    nombre="Juan";
    id=0;
}

Usuario::Usuario(int iD, string n, char t)
{
    nombre=n;
    id=iD;
    tipo=t;
}

string Usuario::getNombre()
{
    return nombre;
}

void Usuario::setNombre(string n)
{
    nombre=n;
}

int Usuario::getId()
{
    return id;
}

void Usuario::setId(int iD)
{
    id=iD;
}
Usuario *Usuario::auth(sqlite3 *db){
	int uid;
	string pass,realPass;
	sqlite3_stmt *query;

	cout<<"Usuario: ";
	cin>>uid;
	cout<<"Contraseña: ";
	cin>>pass;


	string sql=sqlite3_mprintf("SELECT id,Nombre,Contraseña,Tipo FROM Usuarios WHERE id='%d';",uid);
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	sqlite3_step(query);

	realPass=(char*)sqlite3_column_text(query,2);

	if(realPass==pass){
		int id=sqlite3_column_int(query,0);
		string nombre=(char*)sqlite3_column_text(query,1);
		char tipo=sqlite3_column_text(query,3)[0];
		sqlite3_finalize(query);
		cout<<"Bienvenido "<<nombre<<"\n\n";
		return new Usuario(id,nombre,tipo);
	}
	std::cout<<"Usuario o contraseña incorrecta\n";
	sqlite3_finalize(query);
	return NULL;
}
