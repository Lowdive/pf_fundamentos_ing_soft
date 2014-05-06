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

	Usuario *usuario=NULL;

	/* Open database */
	rc = sqlite3_open("PI.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	char o=' ';
	do{
		clearScreen();
		if(usuario==NULL){
			switch(o){
				case '1':
					usuario=Usuario::auth(db);
					if(usuario!=NULL&&usuario->esEstudiante())
						usuario=new Estudiante(db,usuario);
				break;
			}
		}else if(usuario->esEstudiante()){
			switch(o){
				case '1':
					buscar(db,usuario);
				break;
				case '2':
					usuario->display();
				break;
				case '3':
					usuario=NULL;
				break;
			}
		}

		if(usuario==NULL)
			cout<<"1\tAuthenticar\n";
		else if(usuario->esEstudiante()){
			cout<<"1\tBuscar\n";
			cout<<"2\tVer mi información\n";
			cout<<"3\tLogout\n";
		}
		cout<<"0\tSalir\n";
		cin>>o;
	}while(o!='0');


	sqlite3_close(db);
	return 0;
}

