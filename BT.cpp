#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
using namespace std;

#define MAX_MONEDAS 11
#define INFINITO 9999

int valores[MAX_MONEDAS];
int pesos[MAX_MONEDAS]; 
int N;
int V;

void leeEntrada(){
	
	cin >> N;
	cin >> V;
	
	for (int i= 0; i<N; i++)
		cin >> valores[i];
	
	for (int i= 0; i<N; i++)
		cin >> pesos[i];
		
}

void generar(int nivel, int * s){
	s[nivel] = s[nivel] + 1;
}



int pesar(int nivel, int *s){
	int sol =0;
	
	// vamos a recorrer el array hasta nivel para obtener el peso total.
	for(int i = 0; i <= nivel; i++){
		sol+= s[i]*pesos[i];
	}

	return sol;
}


int valorar(int nivel, int *s){
	int sol =0;

	for(int i = 0; i < nivel; i++){
		sol+= s[i]*valores[i];
	}
	
	return sol;
}

bool masHermanos(int nivel, int * s){

	return  (float)s[nivel] < (((float)V-(float)valorar(nivel, s))/(float)valores[nivel]) ;
}

int retroceder(int nivel, int * s){
	s[nivel] = -1;
	return nivel - 1;
}

bool criterio(int nivel, int * s){

	// solo podemos avanzar si quedan niveles y si el valor total actual no supera V
	return ((nivel < N-1) and (valorar(nivel, s) <= V)); // si ponemos "<=", comprueba toda esa rama, lo que no es necesario.
}

int solucion(int nivel, int * s){
	int total=0;
	
	for (int i=0; i < N ; i++) {
		total = total + s[i]*valores[i]; // numero de monedas por su valor
	}
	
	return nivel == (N-1) &&  total == V;
}

void imprimirSol(int* sol){
	for(int i =0;i<N-1; i++) cout<< sol[i] << " " ;
	
	cout<< sol[N-1] <<endl;
	
}


//árbol permutacional.
void backtracking(int * s){
	//INICIALIZACIÓN: 
	int nivel = 0;
	
	int voaMax = -1; 
	int voaMin = INFINITO;
	
	int * soaMax = new int[N](); // para el máximo peso de monedas
	int * soaMin = new int[N](); //para el mínimo peso de monedas
	
	for (int i=0; i < N ; i++) {
		s[i] = -1;
		soaMax[i] = -1; 
		soaMin[i] = -1; 
	}

	do {
		// GENERAR: siempre generará el siguiente hermano
		generar(nivel, s); //actualiza s 

		//SOLUCION
		if (solucion(nivel, s)){
			int peso = pesar(nivel,s);

			 if(peso >= voaMax){
					voaMax = peso;
					for(int i = 0; i<N; i++) soaMax[i] = s[i];
			 }
			 
			 if(peso <= voaMin){
					voaMin = peso;
					for(int i = 0; i<N; i++) soaMin[i] = s[i];
			 }
		 }
		
		
		 //CRITERIO
		 if (criterio(nivel, s)){
			 nivel++;
		 }else {
			 //MAS HERMANOS
			while(!masHermanos(nivel, s) and nivel >= 0)
				//RETROCEDER
				nivel = retroceder(nivel, s);
			
		 }
			
	//FIN DEL BUCLE
	} while (nivel != -1);



	//MOSTRAR SOLUCION
	int resultado = voaMax - voaMin;
	if(resultado < 0) cout << "IMPOSIBLE" << endl;
	else{
		cout <<resultado<< endl;
		imprimirSol(soaMax);
		imprimirSol(soaMin);
	}
}




int main (void){


	int ncasos;
	cin >> ncasos;

    for (int i= 0; i<ncasos; i++) {
		leeEntrada();
		int * s = new int[N]();

		backtracking(s);
	}
	
}
