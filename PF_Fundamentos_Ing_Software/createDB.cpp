#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]){
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;


	/* Open database */
	rc = sqlite3_open("PI.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
  }


	/* Notas:
	 * Programas.Tipo
	 * 	I -> Intercambio
	 * 	S -> Study Abroad
	 * Usuarios.Tipo
	 * 	A -> Admin
	 *  E -> Estudiante
	 */

	//~ /* Create SQL statement */
	sql = "CREATE TABLE Paises("  \
			"id			  INT PRIMARY KEY	     NOT NULL," \
			"Nombre		  TEXT					 NOT NULL);"\
			\
			"CREATE TABLE Universidades("  \
			"id			  INT PRIMARY KEY	     NOT NULL," \
			"idPais		  INT			   	     NOT NULL," \
			"Nombre		  TEXT					 NOT NULL);"\
			\
			"CREATE TABLE Programas("  \
			"id			   INT PRIMARY KEY	  	 NOT NULL," \
			"Nombre		   TEXT					 NOT NULL," \
			"idUniversidad INT					 NOT NULL," \
			"Tipo		   CHAR					 NOT NULL," \
			"Capacidad	   INT					 NOT NULL," \
			"Promedio	   INT					 NOT NULL," \
			"IBT		   INT					 NOT NULL);"\
			\
			"CREATE TABLE Carreras("  \
			"id			  INT PRIMARY KEY		 NOT NULL," \
			"Nombre		  TEXT					 NOT NULL);"\
			\
			"CREATE TABLE REL_Programas_Carreras("  \
			"idPrograma	  INT KEY				 NOT NULL," \
			"idCarrera	  INT KEY				 NOT NULL);"\
			\
			"CREATE TABLE Usuarios("  \
			"id			  INT PRIMARY KEY	  	 NOT NULL," \
			"Nombre		  TEXT					 NOT NULL," \
			"Contraseña	  TEXT					 NOT NULL," \
			"Tipo		  CHAR					 NOT NULL);"\
			\
			"CREATE TABLE Estudiantes("  \
			"id			  INT PRIMARY KEY	  	 NOT NULL," \
			"idCarrera	  INT					 NOT NULL," \
			"IBT		  INT					 NOT NULL," \
			"Promedio	  INT 					 NOT NULL);"\
			\
			"CREATE TABLE Solicitud("  \
			"id			  INT PRIMARY KEY	  	 NOT NULL," \
			"idPrograma	  INT					 NOT NULL," \
			"idEstudiante INT					 NOT NULL);"
			\
			"INSERT INTO Carreras (id,Nombre) VALUES (1,'i²d');" \
			"INSERT INTO Carreras (id,Nombre) VALUES (2,'ITC');" \
			"INSERT INTO Carreras (id,Nombre) VALUES (3,'INT');" \
			"INSERT INTO Carreras (id,Nombre) VALUES (4,'LAE');" \
			"INSERT INTO Carreras (id,Nombre) VALUES (5,'ITIC');" \
			"INSERT INTO Carreras (id,Nombre) VALUES (6,'IQA');" \
			\
			"INSERT INTO Paises (id,Nombre) VALUES (1,'Alemania');" \
			"INSERT INTO Paises (id,Nombre) VALUES (2,'Argentina');" \
			"INSERT INTO Paises (id,Nombre) VALUES (3,'Finlandia');" \
			"INSERT INTO Paises (id,Nombre) VALUES (4,'Francia');" \
			"INSERT INTO Paises (id,Nombre) VALUES (5,'Holanda');"\
			\
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (1,1,'Bauhaus University');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (2,1,'European University of Applied Sciences');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (3,2,'Universidad Nacional de Quilmes');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (4,2,'Universidad Blas Pascal');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (5,2,'Universidad de Palermo');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (6,3,'Aalto University School of Science and Technology');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (7,4,'Arts et Metiers ParisTech');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (8,4,'Ecole des Mines de Nantes');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (9,5,'Amsterdam University College');" \
			"INSERT INTO Universidades (id,idPais,Nombre) VALUES (10,5,'Windesheim University Applied of Sciences');" \
			\
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (1,'Bauhaus Physics',1,'I',2,75,550);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (2,'Bauhaus CS',1,'S',10,80,600);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (3,'EUAS Summer', 2,'I',6,90,0);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (4,'Intercambio Espora',3,'I',2,80,500);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (5,'Pression',4,'S',8,75,570);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (6,'Palermo al gusto',5,'I',1,75,640);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (7,'AUSST',6,'S',10,70,700);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (8,'Mechanics and Industrialization',7,'I',5,95,650);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (9,'Innovative Technologies',8,'S',2,80,570);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (10,'Liberal Arts',9,'S',4,85,550);" \
			"INSERT INTO Programas (id,Nombre,idUniversidad,Tipo,Capacidad,Promedio,IBT) VALUES (11,'Cursussen',10,'I',7,75,550);"\
			\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (1,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (2,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (4,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (5,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (6,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (7,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (9,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (10,1);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (2,2);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (3,2);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (4,2);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (6,2);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (7,2);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (9,2);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (1,3);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (3,3);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (4,3);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (5,3);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (8,3);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (10,3);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (3,4);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (4,4);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (5,4);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (1,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (2,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (3,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (6,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (7,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (8,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (10,5);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (5,6);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (6,6);"\
			"INSERT INTO REL_Programas_Carreras (idPrograma,idCarrera) VALUES (8,6);"\
			\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (0,'Administrador','....','A');"\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (1,'Alberto González','aaaa','E');"\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (2,'Lucía Guajardo','bbbb','E');"\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (3,'Lucas Ramírez','cccc','E');"\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (4,'Leonardo Barajas','dddd','E');"\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (5,'Brenda de León','eeee','E');"\
			"INSERT INTO Usuarios (id,Nombre,Contraseña,Tipo) VALUES (6,'Paola Bustamante','ffff','E');"\
			\
			"INSERT INTO Estudiantes (id,idCarrera,IBT,Promedio) VALUES (1,1,565,80);"\
			"INSERT INTO Estudiantes (id,idCarrera,IBT,Promedio) VALUES (2,2,665,91);"\
			"INSERT INTO Estudiantes (id,idCarrera,IBT,Promedio) VALUES (3,3,765,86);"\
			"INSERT INTO Estudiantes (id,idCarrera,IBT,Promedio) VALUES (4,4,400,76);"\
			"INSERT INTO Estudiantes (id,idCarrera,IBT,Promedio) VALUES (5,5,700,97);"\
			"INSERT INTO Estudiantes (id,idCarrera,IBT,Promedio) VALUES (6,6,580,83);";



	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Tables created successfully\n");
	}
	sqlite3_close(db);
	return 0;
}
