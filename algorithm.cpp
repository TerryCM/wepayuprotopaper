/*
Algoritmo de emparejamiento:
 Programado y revisado por Terry Cruz, LLoyd Castillo y Christian Garcīa
 Se usuo C++ para menejar las estructuras de datos de una manera más rapida, cabe resaltar que para el ingreso de datos se uso la manera
 estandar de lectura que se usa en C y se trato en la medida de lo posible no usar funcionalidades adicionales de C++ aparte de las estructuras
 de datos.
/**/
#include <stack>
#include <vector>
#include <iostream>
#include <cmath>
#define nax 100000;
using namespace std;
int eps = 350;
int cantmax = 3;
vector <double> students;
vector <double> steliminar;
deque <double> creditwait;
deque <double> credit;
int initialize(){

 //Inizializamos el algoritmo de emparejamiento
	// Primero revisamos que existan estudiantes y tarjeta habientes para empezar a funcionar el algoritmo
	if(!students.empty() && (!credit.empty() || !creditwait.empty()) ){
		// primero revisamos que no tengamos a nadie en la listas de espera de lo contario lo añadimos a nuestra cola.
		if(!creditwait.empty()){
			// Primero añadimos los elementos de la cola de lista de espera a la cola principal.
			while(!creditwait.empty()){
				credit.push_front(creditwait.back());
				creditwait.pop_back();
			}

		}
		// Luego empezamos con el bucle
		for(auto it = credit.cbegin(); it != credit.cend(); ++it) {
			//Primero revisamos el ultimo tarjeta habiente es decir el que tiene mayor prioridad.
			double thabiente = credit.front();
			credit.pop_front();
			// Luego de obtener el precio del tarjeta de habiente empezamos a buscar todas las posibilidades
			// Primero empezamos buscando el valor exacto el cual es nuestra primera prioridad.
			int found = 0;
			// Prioridad 1
			for(int i =0 ; i<students.size(); i++){
				if (students[i] == thabiente){
					found = 1;
					cout << "Encontrado para el tarjeta habiente " << *it  << "  (prioridad 1) " << students[i] << "\n";
                    students[i] = students.back();
                    students.pop_back();
                    break;
				}
			}
			// Prioridad 2
			if(!found){
				// si no lo encontramos pasamos al paso 2
				// Hacemos un brutteforce con objetivo que la suma de todos lo estudiantes sean el objetivo
				int seleccion=-1;
				int cantM = 4;
				for(int i=0; i < (1<<students.size());i++){
				    double sum = 0;
				    int cantidad=0;
					for(int j=0;j<students.size();j++){
						if((1<<j) & i){
							sum+=students[j];
							cantidad++;
						}
					}
					if(sum == thabiente && cantidad<=cantmax && cantidad<cantM){
						found = 1;
						seleccion=i;
						cantM = cantidad;
					}
				}
				if(found){
					cout << "Encontrado para el tarjeta habiente con credito (prioridad 2) " << *it << "  los estudiantes con montos: "<<"\n";
					//si encontramos imprimimos y eliminamos
					for(int i = 0 ; i < students.size();i++){
						if((1<<i) & seleccion){
							cout << students[i] << " ";
                            steliminar.push_back(students[i]);
						}
					}
				cout << "\n";

				}
			}else{
				continue;
			}
			//Prioridad 3
			if(!found){
				// Hacemos un brutteforce con objetivo que la suma de todos lo estudiantes sean el objetivo

				int seleccion =-1;
				int epsMin = 350;
				for(int i=0; i < 1<<students.size();i++){
				    double sum = 0;
				    int cantidad =0;
					for(int j=0;j<students.size();j++){
						if(1<<j & i){
							sum+=students[j];
							cantidad++;
						}
					}
					if(fabs(sum - thabiente)<=eps && fabs(sum - thabiente)<=epsMin && cantidad<cantmax){
						found = 1;
						seleccion=i;
						epsMin = fabs(sum - thabiente);
					}
				}
				if(found){
					cout << "Encontrado para el tarjeta habiente con credito (prioridad 3) "<< *it << "  los estudiantes con montos: "<<"\n";
					//si encontramos imprimimos y eliminamos
					for(int x = 0 ; x < students.size();x++){
						if((1<<x) & seleccion) {
                            cout << students[x] << ' ';
                            steliminar.push_back(students[x]);
                        }
					}

                    for(int i=0; i<steliminar.size();i++){
                        erase(students,steliminar[i]);
                    }

			}
					cout << "\n";

			}else{
				continue;
			}

			if(!found){
			    cout << "No se encontro nada para el tarjeta habiente con crédito " << *it << "moviendo a la cola de espera" << "\n";
			//Aqui es el caso en el que no cumple con ninguno de los casos, mandamos a la cola de espera.
		        creditwait.push_back(thabiente);
			}

		}
	}

}

int main(){

	while(true){
		int n;
		double std, tarj;
		printf( "Ingrese 0 para ingresar un estudiante o 1 para ingresar un tarjeta habiente \n");
		scanf("%d",&n);
		if(n == 0){
			printf( "Ingrese al estudiante \n");
			scanf("%lf",&std);
			students.push_back(std);
			initialize();
		}else if(n==1){
			printf( "Ingrese al tarjeta habiente \n");
			scanf("%lf",&tarj);
			credit.push_back(tarj);
			initialize();
		}

	}

}