#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define C 7 //Número de compradores
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////
int turno[C] = {}; //Variable Global de turnos.
bool escogiendo[C] = {}; //Variable global de escogiendo. Si esta escogiendo turno.
/////////////////////////////////////////////////////////////////////////////////////////////
int Max(){ 
	int aux = 0;
	for(int i=0;i<C;i++){
		if(turno[i]>aux) aux=turno[i];
	}
	return aux;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void *panaderia(void *id){ 
	for(int p=0;p<20;p++){
		int i=*(int *)id; //Recibe el id del proceso //Casteo de void a int
			escogiendo[i] = true; //El comprador empieza a escoger
			turno[i] = Max()+1; //Asignamos turno dependiendo de el comprador actual
			escogiendo[i] = false; //El comprador termina de escoger
			for(int j=0;j<C;j++){
				while(escogiendo[j]);
				while((turno[j]!=0)&&((turno[i]==turno[j])&&(j<i)||turno[j]<turno[i]));
			}
		/*Simulamos trabajo esperando unos segundos cuando entra a la sección critica*/
		usleep(rand() % 100000);
		/*SECCIÓN CRITICA*/
		cout<<"Sección Critica: Comprador: "<<i<<"; Turno: "<<turno[i]<<endl;
		turno[i]=0; //Proceso en el turno [i] termino la Sección Critica
		usleep(rand() % 100000);	
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
int main(){	
	pthread_t compradores[C]; //Creamos threads de compradores
	srand(time(NULL)); //Semilla del rand
	int *id; //Declaramos el argumento para asignar memoria al ID
	for (int i=0;i<C;i++){
		id = new int; //Inicializamos variable 
		if(id == NULL) exit(EXIT_FAILURE); 
		*id = i; //Asignamos Id de proceso
		//Creamos el thread 
		//Asignamos el puntero al thread, un atributo default, 
		//la función que va a ejecutar el thread y el argumento que pasaremos a la funcion
		pthread_create(&compradores[i],NULL,panaderia,id); 
	}
	pthread_exit(NULL);	//Liberamos memoria de threads
	return 0;
}