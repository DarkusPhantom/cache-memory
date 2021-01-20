#include <iostream>
#include <fstream>		// Para implementar la modificacion de archivos E/S
#include <string.h>     // Para obtener sub-cadenas que seran el Indice y Etiqueta de direcciones.
#include <cmath>        // Para la funciones logaritmicas para calcular bitsIndice y bitsEtiqueta.
#include <iomanip>      // Para la formacion de la tabla generada como salida del codigo.
#include <algorithm>    // Para la funcion find() que busca un elemento dentro de una lista.
#include <iterator>     // std::next
#include <bitset>       // Para numeros binarios mediante un set de N bits.
#include <queue>		// Para implementar el TDA Cola
#include <list>         // Libreria STL utilizada para este projecto

using namespace std;
#define BITS_NUMBER 16      // Numero maximo para Bitset (En decimal seria 65,336)

void readConfigIn(int *block_size, bool *emplazamiento , int *block_line_size, bool *replace_politic) {
	ifstream configIn("conf.in");
	if (!configIn.good()) {
		cout << "Verificar si el archivo se encuentra en la misma carpeta que el ejecutable" << endl;
	} else {
		while(!configIn.eof()){
			configIn >> *block_size;
			configIn >> *emplazamiento;
			configIn >> *block_line_size;
			configIn >> *replace_politic;
		}
		configIn.close();
	}
}

void process_LRU(list<int> direction_list, int capacity_cache) {
    list<int>::iterator index_direction, indiceAux;
    list<int> cache_list, list_helper;
    int index_bits = log10(capacity_cache) / log10(2);
    int bits_tags = BITS_NUMBER - index_bits;
    int accerts = 0, fails = 0;
    bool hit;
    ofstream resu("resu.out");

    cout << "Abriendo archivo...." << endl;
    cout << "Generando resultados..." << endl;
    resu << "\n" << setw(20) << "Direccion de memoria" << setw(20) << "Hit o Fallo" << setw(30) << "Contenido de los bloques" << endl << setw(65) << "de cache actual" << endl;
    for (index_direction = direction_list.begin(); index_direction != direction_list.end(); index_direction++) {
        bitset<BITS_NUMBER> binary = * index_direction;
        hit = false;

        for (indiceAux = list_helper.begin(); indiceAux != list_helper.end() && !hit; indiceAux++) {
            if(* index_direction == * indiceAux) hit = true;
        }

        string tag = binary.to_string().substr(0, bits_tags);
        string index = binary.to_string().substr(bits_tags);
        string direction = tag + " " + index;

        if (!hit) {
            if (list_helper.size() < capacity_cache) {
                cache_list.push_back(* index_direction);

            } else {
                indiceAux = find(cache_list.begin(), cache_list.end(), list_helper.front());
                (* indiceAux) = (* index_direction);
                list_helper.pop_front();
            }
            list_helper.push_back(* index_direction);
            fails++;
            resu << "\n" << setw(20) << direction << setw(20) << "Fallo" << setw(20) << * index_direction;
        } else {
            list_helper.remove(* index_direction);
            list_helper.push_back(* index_direction);
            accerts++;
            resu << "\n" << setw(20) << direction << setw(20) << "Hit" << setw(20) << * index_direction;
        }
    }
    // resu << endl;
    resu.close();
    cout << "Proceso completado. Cerrando archivo..." << endl;
    cout << "Revise el archivo resu.out" << endl;
}

// void process_FIFO(list<int> direction_list, int capacity_cache) {
//     list<int>::iterator index_direction, indiceAux;
//     list<int> cache_list, list_helper;
//     int index_bits = log10(capacity_cache) / log10(2);
//     int bits_tags = BITS_NUMBER - index_bits;
//     int accerts = 0, fails = 0;
//     bool hit;
//     ofstream resu("resu.out");

//     cout << "Abriendo archivo...." << endl;
//     cout << "Generando resultados..." << endl;
//     resu << "\n" << setw(20) << "Direccion de memoria" << setw(20) << "Hit o Fallo" << setw(30) << "Contenido de los bloques" << endl << setw(65) << "de cache actual" << endl;
//     for (index_direction = direction_list.begin(); index_direction != direction_list.end(); index_direction++) {
//         bitset<BITS_NUMBER> binary = * index_direction;
//         hit = false;

//         for (indiceAux = list_helper.begin(); indiceAux != list_helper.end() && !hit; indiceAux++) {
//             if(* index_direction == * indiceAux) hit = true;
//         }

//         string tag = binary.to_string().substr(0, bits_tags);
//         string index = binary.to_string().substr(bits_tags);
//         string direction = tag + " " + index;

//         if (!hit) {
//             if (list_helper.size() < capacity_cache) {
//                 cache_list.push_back(* index_direction);

//             } else {
//                 indiceAux = find(cache_list.begin(), cache_list.end(), list_helper.front());
//                 (* indiceAux) = (* index_direction);
//                 list_helper.pop_front();
//             }
//             list_helper.push_back(* index_direction);
//             fails++;
//             resu << "\n" << setw(20) << direction << setw(20) << "Fallo" << setw(20) << * index_direction;
//         } else {
//             list_helper.remove(* index_direction);
//             list_helper.push_back(* index_direction);
//             accerts++;
//             resu << "\n" << setw(20) << direction << setw(20) << "Hit" << setw(20) << * index_direction;
//         }
//     }
//     // resu << endl;
//     resu.close();
//     cout << "Proceso completado. Cerrando archivo..." << endl;
//     cout << "Revise el archivo resu.out" << endl;
// }

int main() {
	int block_size ,block_line_size;
	bool emplazamiento, replace_politic;
	readConfigIn(&block_size, &emplazamiento ,&block_line_size, &replace_politic);
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
	
	int number_of_lines = block_size / block_line_size;
	cout << "\nNumero de lineas calculado.\nResultado:" << endl;
    for(list<int> :: iterator line_block = direction_list.begin(); line_block != direction_list.end(); line_block++){
        cout << *line_block << " ";
    }
 
    if (emplazamiento == 0){
    	cout << "\n\nPreparando proceso de Correspondencia Directa" << endl;
    	if (replace_politic == 0) {
    		process_LRU(direction_list, number_of_lines);
    	} else {
    		//replaceFIFO()
    	}
    } else {
    	cout << "\n\nPreparando proceso de Asociativa por Conjuntos";
    	if (replace_politic == 0) {
    		process_LRU(direction_list, number_of_lines);
    	} else {
    		//replaceFIFO()
    	}
    }

	return 0;
}