class Estudiante: public Usuario{
	private:
		int promedio;
		int ibt;
		int idCarrera;
	public:
		Estudiante(sqlite3 *db,Usuario *usuario);
		int getPromedio(){return promedio;};
		int getIbt(){return ibt;};
		virtual void display(sqlite3 *db);
};

Estudiante::Estudiante(sqlite3 *db,Usuario *usuario){
	sqlite3_stmt *query;

	string sql=sqlite3_mprintf("SELECT idCarrera,IBT,Promedio FROM Estudiantes WHERE id='%d';",usuario->getId());
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	sqlite3_step(query);

	id=usuario->getId();
	nombre=usuario->getNombre();
	tipo='E';
	idCarrera=sqlite3_column_int(query,0);
	ibt=sqlite3_column_int(query,1);
	promedio=sqlite3_column_int(query,2);

	delete usuario;
	sqlite3_finalize(query);
}
void Estudiante::display(sqlite3 *db){
	sqlite3_stmt *query;
	string sql=sqlite3_mprintf("SELECT Nombre FROM Carreras WHERE id='%d';",idCarrera);
	sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);

	sqlite3_step(query);

	string carrera=(char*)sqlite3_column_text(query,0);

	std::cout<<"ID\t\t"<<id<<'\n';
	std::cout<<"Nombre\t\t"<<nombre<<'\n';
	std::cout<<"Carrera\t\t"<<carrera<<'\n';
	std::cout<<"Promedio\t"<<promedio<<'\n';
	std::cout<<"IBT\t\t"<<ibt<<'\n';
	std::cout<<'\n';
}
