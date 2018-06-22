/*
 * MyDB.c
 *
 *  Created on: Jun 18, 2018
 *      Author: Anahí
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fCLIENTES;
FILE *fCUENTAS;
FILE *fTRANSACCIONES;
FILE *MYDB;

int count_idCliente,count_idCuenta,count_idTransacciones;
int idBusqueda;
char Ruta_cliente[400], Ruta_cuenta[400], Ruta_transacciones[400];
char Ruta[300];
char clienteR[15]="\\Clientes.dat";
char cuentaR[15]="\\Cuenta.dat";
char transaccionesR[20]="\\Transacciones.dat";

typedef enum {false, true} bool;

typedef struct{
	int dia;
	int mes;
	int anio;
}FECHA;

typedef struct{
	int idCliente;
	char nombre[41];
	char apellidoM[20];
	char apellidoP[20];
	FECHA fechaNacimiento;
	bool stat;
}CLIENTE;

typedef struct{
	int idCuenta;
	int idCliente;
	int saldo;
	FECHA fechaApertura;
	bool stat;
}CUENTA;

typedef struct{
	int idTransaccion;
	char tipoTransaccion[15];
	int idCuentaOrigen;
	int idCuentaDestino;
	FECHA fechaTransaccion;
	int montoTransaccion;
}TRANSACCION;


int menu();
void createFILES();
void createRute();

void nuevoCliente();
void imprimirCliente();
int buscarCliente(int idBusqueda,int x);
int cantidadClientes();
void EliminarCuentaCliente(int idBusqueda);
void eliminarCliente(int idBusqueda);

int buscarCuenta(int idBusqueda,int x);
void nuevoCuenta();
int cantidadCuentas();
void imprimirCuenta();
void eliminarCuenta(int idBusqueda);
void regristarT(int idOrigen, int idDestino, int monto,int tipo);
void deposito();
void dep(int ubicacion, int monto);
void retiro();
int ret(int ubicacion, int monto);
void transferencia();



int main(void){
	setbuf(stdout, NULL);

	MYDB=fopen("mydb.sys","r");
	if(MYDB==0)
		createFILES();
	else
	{
		MYDB=fopen("mydb.sys","r");
		fgets(Ruta,200,MYDB);
		fclose(MYDB);
		createRute();
	}

	int m=0;
	while(m==0){
		system("cls");
		m=menu();
	}
	return 0;
}

void createRute(){

	strcpy(Ruta_cliente,Ruta);
	strcat(Ruta_cliente,clienteR);
	strcpy(Ruta_cuenta,Ruta);
	strcat(Ruta_cuenta,cuentaR);
	strcpy(Ruta_transacciones,Ruta);
	strcat(Ruta_transacciones,transaccionesR);
}


void createFILES(){
	int idzero=0;
	printf("Escribe la ruta donde quieres que se guarden tus archivos\n");
	gets(Ruta);
	createRute();

	MYDB=fopen("mydb.sys","wb");
	fprintf(MYDB,"%s",Ruta);
	fclose(MYDB);

	fCLIENTES=fopen(Ruta_cliente,"wb");
	fwrite(&idzero, sizeof(int),1,fCLIENTES);
	if(fCLIENTES==NULL)
		printf("ERROR AL CREAR EL ARCHIVO CLIENTES");
	fclose(fCLIENTES);

	fCUENTAS=fopen(Ruta_cuenta,"wb");
	fwrite(&idzero, sizeof(int),1,fCUENTAS);
	if(fCUENTAS==NULL)
		printf("ERROR AL CREAR EL ARCHIVO CUENTAS");
	fclose(fCUENTAS);

	fTRANSACCIONES=fopen(Ruta_transacciones,"wb");
	fwrite(&idzero, sizeof(int),1,fTRANSACCIONES);
	if(fTRANSACCIONES==NULL)
		printf("ERROR AL CREAR EL ARCHIVO TRANSACCIONES");
	fclose(fTRANSACCIONES);
}


void nuevoCliente(){

	CLIENTE newCliente;

	printf("Ingrese el nombre\n");
	fflush(stdin);
	gets(newCliente.nombre);
	printf("Ingrese el apellido paterno\n");
	fflush(stdin);
	gets(newCliente.apellidoP);
	printf("Ingrese el apellido materno\n");
	fflush(stdin);
	gets(newCliente.apellidoM);
	printf("Fecha de naciemiento dd/mm/aaaa\n");
	printf("Ingresa el dia\n");
	scanf("%d",&newCliente.fechaNacimiento.dia);
	printf("Ingresa el mes\n");
	scanf("%d",&newCliente.fechaNacimiento.mes);
	printf("Ingrese el año\n");
	scanf("%d",&newCliente.fechaNacimiento.anio);
	newCliente.stat=true;

	fCLIENTES=fopen(Ruta_cliente,"rb");
	fread(&count_idCliente,sizeof(int),1,fCLIENTES);
	count_idCliente++;
	fclose(fCLIENTES);

	fCLIENTES=fopen(Ruta_cliente,"a+b");
	newCliente.idCliente=count_idCliente;
	fwrite(&newCliente,sizeof(CLIENTE),1,fCLIENTES);
	fclose(fCLIENTES);

	fCLIENTES=fopen(Ruta_cliente,"r+b");
	fwrite(&count_idCliente,sizeof(int),1,fCLIENTES);
	fclose(fCLIENTES);
}

int cantidadClientes(){
	int cantidadClientes=0, x;
	CLIENTE tempCliente;
	fCLIENTES=fopen(Ruta_cliente,"rb");
	fread(&x,sizeof(int),1,fCLIENTES);
	while(!feof(fCLIENTES)){
		fread(&tempCliente,sizeof(CLIENTE),1,fCLIENTES);
		cantidadClientes++;
	}
	return cantidadClientes;
}

void imprimirCliente(){
	int cC=cantidadClientes();
	int i;
	CLIENTE tempCliente;
	fCLIENTES=fopen(Ruta_cliente,"rb");
	fread(&count_idCliente,sizeof(int),1,fCLIENTES);
	printf("%20s %20s %20s %20s %10s\n","ID Cliente","Nombre","Apellido Paterno","Apellido Materno","Fecha de Nacimiento");

	for(i=1;i<cC;i++){
		fread(&tempCliente,sizeof(CLIENTE),1,fCLIENTES);
		if(tempCliente.stat==true){
			printf("%20d %20s %20s %20s %10d/%2d/%4d \n",tempCliente.idCliente,tempCliente.nombre,tempCliente.apellidoP,tempCliente.apellidoM,tempCliente.fechaNacimiento.dia,tempCliente.fechaNacimiento.mes,tempCliente.fechaNacimiento.anio);
		}
	}
	printf("Press enter to continue\n");
	char enter = 0;
	fflush(stdin);
	while (enter != '\r' && enter != '\n') { enter = getchar(); }
	fclose(fCLIENTES);
}

int buscarCliente(int idBusqueda,int opcion){
	int ubicacion=0,x,cant;
	cant=cantidadClientes();
	CLIENTE tempCliente;
	fCLIENTES=fopen(Ruta_cliente,"rb");
	fread(&x,sizeof(int),1,fCLIENTES);

	if(cant>=idBusqueda){
		do{
			fread(&tempCliente,sizeof(CLIENTE),1,fCLIENTES);
			ubicacion++;
		}while(tempCliente.idCliente!=idBusqueda);
		if(tempCliente.stat==true){
			if(opcion==0){
				printf("%20s %20s %20s %20s %10s\n","ID Cliente","Nombre","Apellido Paterno","Apellido Materno","Fecha de Nacimiento");
				printf("%20d %20s %20s %20s %10d/%2d/%4d \n",tempCliente.idCliente,tempCliente.nombre,tempCliente.apellidoP,tempCliente.apellidoM,tempCliente.fechaNacimiento.dia,tempCliente.fechaNacimiento.mes,tempCliente.fechaNacimiento.anio);
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
			}
			fclose(fCLIENTES);
			return ubicacion;
		}
		else{
			if(opcion==0){
				printf("ID Cliente NO se encuentra en esta base de batos\n");
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
				fclose(fCLIENTES);
				return -1;
			}
		}
	}
	else{
		printf("ID Cliente NO se encuentra en esta base de batos\n");
		printf("Press enter to continue\n");
		char enter = 0;
		fflush(stdin);
		while (enter != '\r' && enter != '\n') { enter = getchar(); }
		fclose(fCLIENTES);
		return -1;
	}
	return -1;
}


void eliminarCliente(int idBusqueda){
		int ubicacion=buscarCliente(idBusqueda,1);
		int i;
		CLIENTE tempCliente;
		fCLIENTES=fopen(Ruta_cliente,"rb");

		fread(&i,sizeof(int),1,fCLIENTES);

		for(i=0;i<ubicacion;i++)
		fread(&tempCliente,sizeof(CLIENTE),1,fCLIENTES);



		EliminarCuentaCliente(idBusqueda);
		tempCliente.stat=false;

		//printf("id a borrar: %d", tempCliente.idCliente);
		fclose(fCLIENTES);

		fCLIENTES=fopen(Ruta_cliente,"r+b");
		fseek(fCLIENTES, sizeof(int), SEEK_SET );
		fseek(fCLIENTES, sizeof(CLIENTE)*(ubicacion-1), SEEK_CUR );
		fwrite(&tempCliente,sizeof(CLIENTE),1,fCLIENTES);
		fclose(fCLIENTES);

		printf("Press enter to continue\n");
		char enter = 0;
		fflush(stdin);
		while (enter != '\r' && enter != '\n') { enter = getchar(); }
}


void EliminarCuentaCliente(int idBusqueda){
	int x,cC,i,j;
	cC=cantidadCuentas();
	CUENTA tempCuenta;

	printf("ELIMIMAR CUENTA\n");
	for(i=1;i<cC;i++){
		fCUENTAS=fopen(Ruta_cuenta,"rb");
		fread(&x,sizeof(int),1,fCUENTAS);
			for(j=0;j<i;j++)
				fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
	fclose(fCUENTAS);

		if(tempCuenta.idCliente==idBusqueda){
			if(tempCuenta.stat==true)
			//("id cuenta que pertenecia al cliente: %d\n",tempCuenta.idCuenta);
			eliminarCuenta(tempCuenta.idCuenta);
		}
	}

	printf("Press enter to continue\n");
	char enter = 0;
	fflush(stdin);
	while (enter != '\r' && enter != '\n') { enter = getchar();}


}

void nuevoCuenta(){

	CUENTA newCuenta;
	int busqueda;
	printf("Ingresa el ID del cliente\n");
	scanf("%d",&newCuenta.idCliente);
	busqueda=buscarCliente(newCuenta.idCliente,1);
	if(busqueda==-1){
		printf("ERROR EL CREAR LA CUENTA\n");
		printf("Press enter to continue\n");
		char enter = 0;
		fflush(stdin);
		while (enter != '\r' && enter != '\n') { enter = getchar(); }
		fclose(fCLIENTES);
	}
	else{
	printf("Ingresa el Saldo inicial de la cuenta (SIN signo $)\n");
	scanf("%d",&newCuenta.saldo);
	printf("Fecha de APERTURA de la cuenta dd/mm/aaaa\n");
	printf("Ingresa el dia\n");
	scanf("%d",&newCuenta.fechaApertura.dia);
	printf("Ingresa el mes\n");
	scanf("%d",&newCuenta.fechaApertura.mes);
	printf("Ingrese el anioo\n");
	scanf("%d",&newCuenta.fechaApertura.anio);
	newCuenta.stat=true;

	fCUENTAS=fopen(Ruta_cuenta,"rb");
	fread(&count_idCuenta,sizeof(int),1,fCUENTAS);
	count_idCuenta++;
	fclose(fCUENTAS);

	fCUENTAS=fopen(Ruta_cuenta,"a+b");
	newCuenta.idCuenta=count_idCuenta;
	fwrite(&newCuenta,sizeof(CUENTA),1,fCUENTAS);
	fclose(fCUENTAS);

	fCUENTAS=fopen(Ruta_cuenta,"r+b");
	fwrite(&count_idCuenta,sizeof(int),1,fCUENTAS);
	fclose(fCUENTAS);}
}

int cantidadCuentas(){
	int cantidadCuentas=0, x;
	CUENTA tempCuenta;
	fCUENTAS=fopen(Ruta_cuenta,"rb");
	fread(&x,sizeof(int),1,fCUENTAS);
	while(!feof(fCUENTAS)){
		fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
		cantidadCuentas++;
	}
	return cantidadCuentas;
}

void imprimirCuenta(){
	int cC=cantidadCuentas();
		int i;
		CUENTA tempCuenta;
		fCUENTAS=fopen(Ruta_cuenta,"rb");
		fread(&count_idCuenta,sizeof(int),1,fCUENTAS);
		printf("%20s %20s %20s %20s\n","ID CUENTA", "ID Cliente","Saldo","Fecha de Apertura");

		for(i=1;i<cC;i++){
			fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
			if(tempCuenta.stat==true){
				printf("%20d %20d %20d %10d/%2d/%4d\n",tempCuenta.idCuenta,tempCuenta.idCliente,tempCuenta.saldo,tempCuenta.fechaApertura.dia,tempCuenta.fechaApertura.mes,tempCuenta.fechaApertura.anio);
			}
		}
		printf("Press enter to continue\n");
		char enter = 0;
		fflush(stdin);
		while (enter != '\r' && enter != '\n') { enter = getchar(); }
		fclose(fCUENTAS);
}

int buscarCuenta(int idBusqueda,int opcion){
	int ubicacion=0,x,cant;
	cant=cantidadCuentas();
	CUENTA tempCuenta;
	fCUENTAS=fopen(Ruta_cuenta,"rb");
	fread(&x,sizeof(int),1,fCUENTAS);

	if(cant>=idBusqueda){
		do{
			fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
			ubicacion++;
		}while(tempCuenta.idCuenta!=idBusqueda);
		if(tempCuenta.stat==true){
			if(opcion==0){
				printf("%20s %20s %20s %20s\n","ID CUENTA", "ID Cliente","Saldo","Fecha de Apertura");
				printf("%20d %20d %20d %10d/%2d/%4d\n",tempCuenta.idCuenta,tempCuenta.idCliente,tempCuenta.saldo,tempCuenta.fechaApertura.dia,tempCuenta.fechaApertura.mes,tempCuenta.fechaApertura.anio);
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
			}
			fclose(fCUENTAS);
			return ubicacion;
		}
		else{
			if(opcion==0){
				printf("ID Cuenta NO se encuentra en esta base de batos\n");
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
				fclose(fCUENTAS);
				return -1;
			}
		}
	}
	else{
		printf("ID Cuenta NO se encuentra en esta base de batos\n");
		printf("Press enter to continue\n");
		char enter = 0;
		fflush(stdin);
		while (enter != '\r' && enter != '\n') { enter = getchar(); }
		fclose(fCUENTAS);
		return -1;
	}
	return -1;

}

void eliminarCuenta(int idBusqueda){
		int ubicacion=buscarCuenta(idBusqueda,1);
		int i;
		CUENTA tempCuenta;

		fCUENTAS=fopen(Ruta_cuenta,"rb");
		fread(&i,sizeof(int),1,fCUENTAS);
		for(i=0;i<ubicacion;i++)
			fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
		tempCuenta.stat=false;
		fclose(fCUENTAS);

		fCUENTAS=fopen(Ruta_cuenta,"r+b");
		fseek(fCUENTAS, sizeof(int), SEEK_SET );
		fseek(fCUENTAS, sizeof(CUENTA)*(ubicacion-1), SEEK_CUR );
		fwrite(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
		fclose(fCUENTAS);
}
void regristarT(int idOrigen, int idDestino, int monto, int tipo){

	TRANSACCION newTransaccion;
	newTransaccion.idCuentaOrigen=idOrigen;
	newTransaccion.idCuentaDestino=idDestino;
	newTransaccion.montoTransaccion=monto;
	printf("Fecha de Transaccion dd/mm/aaaa\n");
	printf("Ingresa el dia\n");
	scanf("%d",&newTransaccion.fechaTransaccion.dia);
	printf("Ingresa el mes\n");
	scanf("%d",&newTransaccion.fechaTransaccion.mes);
	printf("Ingrese el año\n");
	scanf("%d",&newTransaccion.fechaTransaccion.anio);

	char d[15]="deposito";
	char r[15]="retiro";
	char t[20]="transferencia";
	switch(tipo){
	case 1:

		strcpy(newTransaccion.tipoTransaccion,d);
		break;
	case 2:
		strcpy(newTransaccion.tipoTransaccion,r);
		break;
	case 3:
		strcpy(newTransaccion.tipoTransaccion,t);
		break;
	}

		fTRANSACCIONES=fopen(Ruta_transacciones,"rb");
		fread(&count_idTransacciones,sizeof(int),1,fTRANSACCIONES);
		count_idTransacciones++;
		fclose(fTRANSACCIONES);

		fTRANSACCIONES=fopen(Ruta_transacciones,"a+b");
		newTransaccion.idTransaccion=count_idTransacciones++;
		fwrite(&newTransaccion,sizeof(TRANSACCION),1,fTRANSACCIONES);
		fclose(fTRANSACCIONES);

		fTRANSACCIONES=fopen(Ruta_transacciones,"r+b");
		fwrite(&count_idTransacciones,sizeof(int),1,fTRANSACCIONES);
		fclose(fTRANSACCIONES);
}
void deposito(){
	int idD, monto,ubicacion;
	printf("Ingrese el numero de cuenta a depositar\n");
	scanf("%d",&idD);
	ubicacion=buscarCuenta(idD,1);
	if(ubicacion!=-1){
	printf("Ingrese el monto\n");
		scanf("%d",&monto);
	regristarT(0,idD, monto, 1);}
	dep(ubicacion,monto);
}

void dep(int ubicacion, int monto){

		int i;
		CUENTA tempCuenta;
		fCUENTAS=fopen(Ruta_cuenta,"rb");
		fread(&i,sizeof(int),1,fCUENTAS);
		for(i=0;i<ubicacion;i++)
		fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
		tempCuenta.saldo=tempCuenta.saldo+monto;
		fclose(fCUENTAS);

		fCUENTAS=fopen(Ruta_cuenta,"r+b");
		fseek(fCUENTAS, sizeof(int), SEEK_SET );
		fseek(fCUENTAS, sizeof(CUENTA)*(ubicacion-1), SEEK_CUR );
		fwrite(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
		fclose(fCUENTAS);
}
void retiro(){
	int idO, monto,ubicacion, success;
		printf("Ingrese el numero de cuenta a retirar\n");
		scanf("%d",&idO);
		ubicacion=buscarCuenta(idO,1);
		if(ubicacion!=-1){
		printf("Ingrese el monto\n");
			scanf("%d",&monto);
		success=ret(ubicacion, monto);
		if(success==0)
		regristarT(idO,0, monto, 2);}
}


int ret(int ubicacion, int monto){
	int i;
	CUENTA tempCuenta;
	fCUENTAS=fopen(Ruta_cuenta,"rb");
	fread(&i,sizeof(int),1,fCUENTAS);
	for(i=0;i<ubicacion;i++)
		fread(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);

	if(tempCuenta.saldo>=monto){
		tempCuenta.saldo=(tempCuenta.saldo-monto);
		fclose(fCUENTAS);

		fCUENTAS=fopen(Ruta_cuenta,"r+b");
		fseek(fCUENTAS, sizeof(int), SEEK_SET );
		fseek(fCUENTAS, sizeof(CUENTA)*(ubicacion-1), SEEK_CUR );
		fwrite(&tempCuenta,sizeof(CUENTA),1,fCUENTAS);
		fclose(fCUENTAS);
		return 0;
		}
	else{
		fclose(fCUENTAS);
		printf("ERROR SALDO INSUFICIENTE\n");
		printf("Press enter to continue\n");
		char enter = 0;
		fflush(stdin);
		while (enter != '\r' && enter != '\n') { enter = getchar(); }
		return -1;
	}
}

void transferencia(){
	int idO,idD, monto,ubicacionO,ubicacionD,success;
		printf("Ingrese el numero de cuenta Origen\n");
		scanf("%d",&idO);
		ubicacionO=buscarCuenta(idO,1);
		if(ubicacionO!=-1 ){
			printf("Ingrese el numero de cuenta Destino\n");
			scanf("%d",&idD);
			ubicacionD=buscarCuenta(idD,1);
			if(ubicacionD!=-1 ){
			printf("Ingrese el monto\n");
			scanf("%d",&monto);
			success=ret(ubicacionO, monto);
			if(success==0){
				dep(ubicacionD,monto);
			regristarT(idO,0, monto, 2);}
			}
		}
}

int menu(){
	int m, m2;
	printf("1)Clientes\n2)Cuentas\n3)Transacciones\n4)salir\n ");
	scanf("%d",&m);
	switch(m){
	case 1://CLIENTES
		printf("1)NUEVO cliente\n2)BUSCAR cliente\n3)ELIMINAR cliente\n4)IMPRIMIR clientes\n5)Atras\n");
		scanf("%d",&m2);
		switch (m2){
		case 1://Nuevo
			nuevoCliente();
			break;
		case 2://Buscar
			printf("Introduzca el ID del usuario que desa buscar\n");
			scanf("%d",&idBusqueda);
			buscarCliente(idBusqueda,0);
			break;
		case 3://Eliminar
			printf("Introduzca el ID del usuario que desa eliminar\n");
			scanf("%d",&idBusqueda);
			eliminarCliente(idBusqueda);
			break;
		case 4://Imprimir
			imprimirCliente();
			break;
		case 5://Atrás
			return 0;
			break;
		default:
			printf("Opción NO disponible\n");
			printf("Press enter to continue\n");
			char enter = 0;
			fflush(stdin);
			while (enter != '\r' && enter != '\n') { enter = getchar(); }
			return 0;
			break;
		}
		break;
		case 2://CUENTAS
			printf("1)NUEVA cuenta\n2)BUSCAR cuenta\n3)ELIMINAR cuenta\n4)IMPRIMIR cuentas\n5)Atras\n");
			scanf("%d",&m2);
			switch (m2){
			case 1://Nuevo
				nuevoCuenta();
				break;
			case 2://Buscar
				printf("Introduzca el ID de cuenta que desa buscar\n");
				scanf("%d",&idBusqueda);
				buscarCuenta(idBusqueda,0);
				break;
			case 3://Eliminar
				printf("Introduzca el ID de cuenta que desa eliminar\n");
				scanf("%d",&idBusqueda);
				eliminarCuenta(idBusqueda);
				break;
			case 4://Imprimir
				imprimirCuenta();
				break;
			case 5://Atrás
				return 0;
				break;
			default:
				printf("Opcion NO disponible\n");
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
				return 0;
				break;
			}
			break;
		case 3://TRANSACCIONES
			printf("1)Deposito\n2)Retiro\n3)Transderencia\n4)Atras\n");
			scanf("%d",&m2);
			switch (m2){
			case 1://Deposito
				deposito();
				break;
			case 2://Retiro
				retiro();
				break;
			case 3://Transferencia
				transferencia();
				break;
			case 4://atrás
				return 0;
				break;
			default:
				printf("Opcion NO disponible\n");
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
				return 0;
				break;
			}
			break;
			case 4://SALIR
				return 1;
				break;
			default:
				printf("Opcion NO disponible\n");
				printf("Press enter to continue\n");
				char enter = 0;
				fflush(stdin);
				while (enter != '\r' && enter != '\n') { enter = getchar(); }
				return 0;
				break;
	}
	return 0;
}

