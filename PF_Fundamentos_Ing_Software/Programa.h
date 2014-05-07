#include <iostream>

class Programa
{
private:
    string nombre;
    string carreras[500];
	int id;
    int capacidad;
    char tipo;
    int ibt;
    int promedio;
public:
    Programa(); // inicializar con nada
    Programa(string nom); // "<id>",""
    Programa(string nom, string arr[], int cap, string tip); // "<id>", "nom"
    Programa(int id, string nombre, char tipo, int capacidad, int ibt, int promedio);
    string getProg();
    void setProg(string program);
    string getCarr();
    void setNewCarrera(string carr); //adds to the end of the arr
    void delCarrera(string carr); //searches for the career then deletes then fixes empty spaces
    int getCap();
    void setCap(int c);
    string getTipo();
    void setTipo(char t);
    void editarPrograma();
    void muestraProg();
    string getNombre(){return nombre;};
    static void select(sqlite3 *db, int idUniversidad, int idPais, Usuario *usuario);
};

Programa::Programa()
{
    nombre="Intercambio";
    carreras[0]="ITIC";
    capacidad=60;
    tipo='I';
}

Programa::Programa(string nom)
{
    nombre=nom;
    carreras[0]="ITIC";
    capacidad=60;
    tipo='I';
}

Programa::Programa(string nom, string arr[], int cap, string tip)
{
    nombre=nom;
    //loop para copiar arr[] a carreras
    capacidad=60;
    tipo='I';
}
Programa::Programa(int id, string nombre, char tipo, int capacidad, int ibt, int promedio){
	this->id=id;
	this->nombre=nombre;
	this->tipo=tipo;
	this->capacidad=capacidad;
	this->ibt=ibt;
	this->promedio=promedio;
}
string Programa::getProg()
{
    return nombre;
}
void Programa::setProg(string program)
{
    nombre=program;
}
string Programa::getCarr()
{
    //devuelve un string con todas las carreras?
}
void Programa::setNewCarrera(string carr) //adds to the end of the arr
{
    //recorre el arreglo, agrega al final del arreglo
}
void Programa::delCarrera(string carr) //searches for the career then deletes then fixes empty spaces
{
    //recorre el arreglo, borra la carrera que se busca y reacomoda el arreglo
}
int Programa::getCap()
{
    return capacidad;
}
void Programa::setCap(int c)
{
    capacidad=c;
}
string Programa::getTipo()
{
    if(tipo=='I')
		return "Intercambio";
	return "Study Abroad";
}
void Programa::setTipo(char t)
{
    tipo=t;
}

void Programa::editarPrograma()
{
    //debería tener parámetros?
    int x=0;
}

void Programa::muestraProg()
{
    cout << nombre << " " << carreras[0] << " " << capacidad << " " << tipo << endl;
}

void Programa::select(sqlite3 *db, int idUniversidad,int idPais, Usuario *usuario){
	sqlite3_stmt *query;
	string sql;

	if(usuario->esAdiministrador()){
		if(idUniversidad==0&&idPais==0)
			sql="SELECT id,Nombre FROM Programas";
		else if(idUniversidad==0)
			sql=sqlite3_mprintf("SELECT id,Nombre FROM Programas WHERE idUniversidad IN (SELECT id from Universidades WHERE idPais='%d')",idPais);
		else
			sql=sqlite3_mprintf("SELECT id,Nombre FROM Programas WHERE idUniversidad='%d'",idUniversidad);
	}else{
		Estudiante *estudiante=static_cast<Estudiante*>(usuario);
		if(idUniversidad==0&&idPais==0)
			sql=sqlite3_mprintf("SELECT id,Nombre FROM Programas WHERE Promedio<='%d' AND IBT<='%d'",estudiante->getPromedio(),estudiante->getIbt());
		else if(idUniversidad==0)
			sql=sqlite3_mprintf("SELECT id,Nombre FROM Programas WHERE Promedio<='%d' AND IBT<='%d' AND idUniversidad IN (SELECT id from Universidades WHERE idPais='%d')",estudiante->getPromedio(),estudiante->getIbt(),idPais);
		else
			sql=sqlite3_mprintf("SELECT id,Nombre FROM Programas WHERE Promedio<='%d' AND IBT<='%d' AND idUniversidad='%d'",estudiante->getPromedio(),estudiante->getIbt(),idUniversidad);
	}
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	int res=sqlite3_step(query);
	int id;
	int idPermitidos [100];
	string nombre;

	cout<<"Selecciona el programa con su numero\n";
	int numPermitidos=0;
	while(res!=SQLITE_DONE){
		id=sqlite3_column_int(query,0);
		idPermitidos[numPermitidos++]=id;
		nombre=(char*)sqlite3_column_text(query,1);
		cout<<id<<'\t'<<nombre<<'\n';
		res=sqlite3_step(query);
	}
	sqlite3_finalize(query);

	int idSeleccionado;
	bool valido=false;
	do{
		cin>>idSeleccionado;
		int i=0;
		while(i<numPermitidos&&idSeleccionado!=idPermitidos[i])
			i++;
		if(idSeleccionado!=idPermitidos[i])
			std::cout<<"Ese no es un programa valido, intenta de nuevo (0 para cancelar): ";
		else
			valido=true;
	}while(!valido&&idSeleccionado!=0);

	if(idSeleccionado!=0){
		sql=sqlite3_mprintf("SELECT Nombre FROM Programas WHERE id='%d';",idSeleccionado);
		sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);
		sqlite3_step(query);
		string nombreSeleccionado=(char*)sqlite3_column_text(query,0);
		sqlite3_finalize(query);

		char *sqlInsert=sqlite3_mprintf("INSERT INTO Solicitudes (idPrograma,idEstudiante) VALUES ('%d','%d');",idSeleccionado,usuario->getId());
		sqlite3_exec(db, sqlInsert, NULL, 0, NULL);
		std::cout<<"Solicitud enviada para "<<nombreSeleccionado<<" (presiona Enter para continuar)\n";

		string basura;
		std::cin.ignore();
		std::getline(std::cin,basura);
	}
}
