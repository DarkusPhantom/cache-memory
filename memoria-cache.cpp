#include <iostream>
#include <fstream>		// Para implementar la modificacion de archivos E/S
#include <string.h>     // Para obtener sub-cadenas que seran el Indice y Etiqueta de direcciones.
#include <cmath>        // Para la funciones logaritmicas para calcular bitsIndice y bitsEtiqueta.
#include <iomanip>      // Para la formacion de la tabla generada como salida del codigo.

#include <algorithm>    // Para la funcion find() que busca un elemento dentro de una lista.
#include <utility>      // Para la creacion de una estructura tipo <Pair> para metodo LFU.

#include <iterator>     // std::next
#include <bitset>       // Para numeros binarios mediante un set de N bits.
#include <queue>		// Para implementar el TDA Cola
#include <list>         // Libreria STL utilizada para este projecto

#include "Cola.h"
#include "Nodo.h"

using namespace std;
#define NUMBITS 16      // Numero maximo para Bitset (En decimal seria 65,336)

void read_data() {	
	int longuitud_cache;
	cout << "Ingrese el tamaño de la cache:" << endl;
	cin >> longuitud_cache;

	int emplazamiento;
	cout << "Ingrese el emplazamiento:" << endl;
	cin >> emplazamiento;

	int longuitud_linea;
	cout << "Ingrese el tamaño de la linea:" << endl;
	cin >> longuitud_linea;

	int politica_remplazo;
	cout << "Ingrese la politica de remplazo:" << endl;
	cin >> politica_remplazo;

	cout << endl << longuitud_cache << endl << emplazamiento << endl << longuitud_linea << endl << politica_remplazo << endl;
}

void readConfigIn(int *longuitud_bloque, bool *emplazamiento , int *longuitud_linea, bool *politica_remplazo) {
	ifstream configIn("conf.in");
	if (!configIn.good()) {
		cout << "Verificar si el archivo se encuentra en la misma carpeta que el ejecutable" << endl;
	} else {
		while(!configIn.eof()){
			configIn >> *longuitud_bloque;
			configIn >> *emplazamiento;
			configIn >> *longuitud_linea;
			configIn >> *politica_remplazo;
		}
		configIn.close();
	}
}

//void readTrazIn(queue<int, list<int>> direction_list) {}

int main() {
	int longuitud_bloque ,longuitud_linea;
	bool emplazamiento, politica_remplazo;
	readConfigIn(&longuitud_bloque, &emplazamiento ,&longuitud_linea, &politica_remplazo);
	cout << "Leido el archivo config.in" << endl;

	list<int> direction_list;
	//Pasar esto a readTrazIn(direction_list)
	ifstream trazIn("traz.in");
	if (!trazIn.good()) {
		cout << "Verificar si el archivo se encuentra en la misma carpeta que el ejecutable" << endl;
	} else {
		int block_line;
		while(!trazIn.eof()){
			trazIn >> block_line;
			direction_list.push_back(block_line);
		}
	}
	cout << "Leido el archivo traz.in" << endl;
	// //readTrazIn(direction_list);
	
	int number_of_lines = longuitud_bloque / longuitud_linea;
	cout << "\n\nNumero de lineas calculado." << endl;
	cout << "Resultado:" << endl;
    for(list<int> :: iterator line_block = direction_list.begin(); line_block != direction_list.end(); line_block++){
        cout << *line_block << " ";
    }
 
    if (emplazamiento == 0){
    	cout << "\n\nPreparando proceso de Correspondencia Directa" << endl;
    	if (politica_remplazo == 0) {
    		//direct_cache_process()
    	} else {
    		//replaceFIFO()
    	}
    } else {
    	cout << "\n\nPreparando proceso de Asociativa por Conjuntos";
    	if (politica_remplazo == 0) {
    		//direct_cache_process()
    	} else {
    		//replaceFIFO()
    	}
    }

	return 0;
}