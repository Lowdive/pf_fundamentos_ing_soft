class Estudiante: public Usuario{
	private:
		int promedio;
		int ibt;
		int idCarrera;
	public:
		Estudiante(sqlite3 *db,Usuario *usuario);
		int getPromedio(){return promedio;};
		int getIbt(){return ibt;};
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

