class Pais
{
private:
    int id;
    string nombre;
public:
	Pais(int ident, string nom);
    int getId();
    string getNombre();
    void muestraPais();
    static Pais* select(sqlite3 *db);
};
Pais::Pais(int ident, string nom){
    id=ident;
    nombre=nom;
}
int Pais::getId(){
    return id;
}
string Pais::getNombre(){
    return nombre;
}
void Pais::muestraPais()
{
    cout << id << " " << nombre << endl;
}
Pais *Pais::select(sqlite3 *db){
	sqlite3_stmt *query;

	string sql="SELECT id,Nombre FROM Paises";
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	int res=sqlite3_step(query);
	int id;
	string nombre;

	cout<<"Selecciona el pais con su número\n"
		<<"0	Todos\n";
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
		return new Pais(0,"Todos");

	sql=sqlite3_mprintf("SELECT Nombre FROM Paises WHERE id='%d';",idSeleccionado);
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);
	sqlite3_step(query);
	string nombreSeleccionado=(char*)sqlite3_column_text(query,0);
	return new Pais(idSeleccionado,nombreSeleccionado);
}
