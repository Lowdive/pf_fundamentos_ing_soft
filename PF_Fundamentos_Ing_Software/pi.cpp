#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include "Usuario.h"
#include "Estudiante.h"
#include "Pais.h"
#include "Universidad.h"
#include "Programa.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void queryPrint(char *sql){
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;

	/* Open database */
	rc = sqlite3_open("PI.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
}


void clearScreen()
{
    cout << string( 100, '\n' );
}

void buscar(sqlite3 *db,Usuario *usuario){
	Pais *pais=Pais::select(db);
	clearScreen();
	cout<<"Pais seleccionado: "<<pais->getNombre()<<"\n\n";

	Universidad *universidad=Universidad::select(db,pais->getId());
	clearScreen();
	cout<<"Universidad seleccionada: "<<universidad->getNombre()<<"\n\n";

	Programa *programa=Programa::select(db,universidad->getId(),pais->getId(),usuario);
	clearScreen();
	cout<<"Programa seleccionado: "<<programa->getNombre()<<"\n\n";


}

int main(){
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	/* Open database */
	rc = sqlite3_open("PI.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	Usuario *usuario=Usuario::auth(db);
	if(usuario==NULL){
		cout<<"Usuario invalido";
		exit(0);
	}
	if(usuario->esEstudiante())
		usuario=new Estudiante(db,usuario);

	clearScreen();
	cout<<"Bienvenido "<<usuario->getNombre()<<"\n\n";

	buscar(db,usuario);

	sqlite3_close(db);
	return 0;
}

