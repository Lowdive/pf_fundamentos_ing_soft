class Universidad
{
private:
    int id;
    string nombre;
    int idPais;
public:
    Universidad(); // inicializar con nada
    Universidad(int ident); // "<id>",""
    Universidad(int ident, string nom, int idPais); // "<id>", "nom"
    int getId();
    void setId(int i);
    string getNombre();
    void setNombre(string n);
    void muestraUni();
    static Universidad* select(sqlite3 *db, int idPais);
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

Universidad::Universidad(int ident, string nom, int pais)
{
    id=ident;
    nombre=nom;
    idPais=pais;
}

int Universidad::getId()
{
    return id;
}

void Universidad::setId(int i)
{
    id=i;
}

string Universidad::getNombre()
{
    return nombre;
}

void Universidad::setNombre(string n)
{
    nombre=n;
}

void Universidad::muestraUni()
{
    cout << id << " " << nombre << endl;
}
Universidad *Universidad::select(sqlite3 *db,int idPais){
	sqlite3_stmt *query;
	string sql;

	if(idPais==0)
		sql="SELECT id,Nombre FROM Universidades";
	else
		sql=sqlite3_mprintf("SELECT id,Nombre FROM Universidades WHERE idPais='%d';",idPais);
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	int res=sqlite3_step(query);
	int id;
	string nombre;

	cout<<"Selecciona la universidad con su número\n"
		<<"0	Todas\n";
	while(res!=SQLITE_DONE){
		id=sqlite3_column_int(query,0);
		nombre=(char*)sqlite3_column_text(query,1);

		cout<<id<<'\t'<<nombre<<'\n';

		res=sqlite3_step(query);
	}
	sqlite3_finalize(query);
	//~ int max=id;
	int idSeleccionado;
	cin>>idSeleccionado;

	if(idSeleccionado==0)
		return new Universidad(0,"Todas",-1);

	sql=sqlite3_mprintf("SELECT Nombre,idPais FROM Universidades WHERE id='%d';",idSeleccionado);
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);
	sqlite3_step(query);
	string nombreSeleccionado=(char*)sqlite3_column_text(query,0);
	int idPaisSeleccionado=sqlite3_column_int(query,1);
	return new Universidad(idSeleccionado,nombreSeleccionado,idPaisSeleccionado);
}
