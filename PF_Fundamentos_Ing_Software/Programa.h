#include <iostream>
#include <sstream>

class Programa
{
private:
    string nombre;
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
    string getCarreras(sqlite3 *db);
    void setNewCarrera(string carr); //adds to the end of the arr
    void delCarrera(string carr); //searches for the career then deletes then fixes empty spaces
    int getCap();
    void setCap(int c);
    string getTipo();
    void setTipo(char t);
    void editarPrograma();
    string getNombre(){return nombre;};
    static void select(sqlite3 *db, int idUniversidad, int idPais, Usuario *usuario);
    void display(sqlite3 *db);
    static void nuevo(sqlite3 *db);
};

Programa::Programa()
{
    nombre="Intercambio";
    capacidad=60;
    tipo='I';
}

Programa::Programa(string nom)
{
    nombre=nom;
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
string Programa::getCarreras(sqlite3 *db){
	sqlite3_stmt *query;
	string carreras="",carrera;
	string sql=sqlite3_mprintf("SELECT Nombre FROM Carreras WHERE id IN (SELECT idCarrera FROM REL_Programas_Carreras WHERE idPrograma='%d')",id);

	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	int res=sqlite3_step(query);

	while(res!=SQLITE_DONE){
		carrera=(char*)sqlite3_column_text(query,0);
		carreras+=carrera+", ";
		res=sqlite3_step(query);
	}
	sqlite3_finalize(query);

	return carreras.substr(0,carreras.length()-2);
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

	cout<<"Selecciona el programa con su numero (0 para cancelar)\n";
	int numPermitidos=0;
	while(res!=SQLITE_DONE){
		id=sqlite3_column_int(query,0);
		idPermitidos[numPermitidos++]=id;
		nombre=(char*)sqlite3_column_text(query,1);
		cout<<id<<'\t'<<nombre<<'\n';
		res=sqlite3_step(query);
	}
	sqlite3_finalize(query);

	if(numPermitidos==0){
		std::cout<<"No hay ningun programa disponible para ti con las caracteristicas seleccionadas (presiona Enter para continuar)\n";
		std::cin.ignore();
		std::cin.ignore();
	}else{
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
			if(usuario->esEstudiante()){
				sql=sqlite3_mprintf("SELECT Nombre FROM Programas WHERE id='%d';",idSeleccionado);
				sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);
				sqlite3_step(query);
				string nombreSeleccionado=(char*)sqlite3_column_text(query,0);
				sqlite3_finalize(query);

				char *sqlInsert=sqlite3_mprintf("INSERT INTO Solicitudes (idPrograma,idEstudiante) VALUES ('%d','%d');",idSeleccionado,usuario->getId());
				sqlite3_exec(db, sqlInsert, NULL, 0, NULL);
				std::cout<<"Solicitud enviada para "<<nombreSeleccionado<<" (presiona Enter para continuar)\n";

				std::cin.ignore();
				std::cin.ignore();
			}else{
				sql=sqlite3_mprintf("SELECT Nombre,Tipo,Capacidad,IBT,Promedio FROM Programas WHERE id='%d';",idSeleccionado);
				sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);
				sqlite3_step(query);
				string nombreSeleccionado=(char*)sqlite3_column_text(query,0);
				char tipoSeleccionado=(char)sqlite3_column_text(query,1)[0];
				int capacidadSeleccionado=(char)sqlite3_column_int(query,2);
				int ibtSeleccionado=(char)sqlite3_column_int(query,3);
				int promedioSeleccionado=(char)sqlite3_column_int(query,4);
				Programa programa(idSeleccionado,nombreSeleccionado,tipoSeleccionado,capacidadSeleccionado,ibtSeleccionado,promedioSeleccionado);
				programa.display(db);

				std::cout<<"(presiona Enter para continuar)\n";
				std::cin.ignore();
				std::cin.ignore();
			}
		}
	}
}
void Programa::display(sqlite3 *db){
	std::cout<<"Nombre\t\t"<<nombre<<'\n';
	std::cout<<"Tipo\t\t"<<getTipo()<<'\n';
	std::cout<<"Capacidad\t"<<capacidad<<'\n';
	std::cout<<"Carreras\t"<<getCarreras(db)<<'\n';
	std::cout<<"Promedio\t"<<promedio<<'\n';
	std::cout<<"IBT\t\t"<<ibt<<'\n';
	std::cout<<'\n';
}
void Programa::nuevo(sqlite3 *db){
	sqlite3_stmt *query;
	string nombre,tipo;
	int capacidad,promedio,ibt;

	std::cout<<"Agregando nuevo programa\n";
	Pais *pais=Pais::select(db);
	Universidad *universidad=Universidad::select(db,pais->getId());

	std::cout<<"Nombre: ";
	std::cin.ignore();
	std::getline(std::cin,nombre);
	std::cout<<"Tipo (I para intercambio, S para study abroad): ";
	std::cin>>tipo;
	std::cout<<"Capacidad: ";
	std::cin>>capacidad;
	std::cout<<"Promedio minimo: ";
	std::cin>>promedio;
	std::cout<<"IBT minimo: ";
	std::cin>>ibt;

	char *sqlInsert=sqlite3_mprintf("INSERT INTO Programas (Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES('%q','%d','%q','%d','%d','%d');",nombre.c_str(),universidad->getId(),tipo.c_str(),capacidad,promedio,ibt);

	sqlite3_exec(db, sqlInsert, NULL, 0, NULL);

	int idPrograma=sqlite3_last_insert_rowid(db);

	//Asignar Carreras

	//~ sql=sqlite3_mprintf("SELECT id,Nombre FROM Carreras WHERE Promedio<='%d' AND IBT<='%d' AND idUniversidad='%d'",estudiante->getPromedio(),estudiante->getIbt(),idUniversidad);
	sqlite3_prepare_v2(db,"SELECT id,Nombre FROM Carreras",-1,&query,NULL);

	int res=sqlite3_step(query);
	int id;

	cout<<"Seleccionas la carreras con sus numeros, separados por comas\n";
	while(res!=SQLITE_DONE){
		id=sqlite3_column_int(query,0);
		nombre=(char*)sqlite3_column_text(query,1);
		cout<<id<<'\t'<<nombre<<'\n';
		res=sqlite3_step(query);
	}
	sqlite3_finalize(query);

	string carreras;
	std::cin.ignore();
	std::getline(std::cin,carreras);

	std::istringstream ss(carreras);
	string token;

	while(std::getline(ss, token, ',')){
		sqlInsert=sqlite3_mprintf("INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES('%d','%d');",idPrograma,std::stoi(token));
		sqlite3_exec(db, sqlInsert, NULL, 0, NULL);
	}

	std::cout<<"Programa agregado (presiona Enter para continuar)";
	std::cin.ignore();
}
