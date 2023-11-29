
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 * Nombre y Apellidos: DA58 Alejandro Zamorano Méndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema consiste en ir comparando los elementos de las listas. Si dos canciones se repiten, se coge como palabra valida y se guarda su posicion.
 Si se repite una cancion en distinto orden en una lista respecto la otra, la anterior cancion o es valida.

 El algoritmo consiste en rellenar la tabla, es decir, la matriz de programacion dinamica. Si coinciden los elementos de las listas, se pasa al elemento siguiente por arriba, 
 si no se hace el maximo entre el elemento de arriba y el de la izquierda.
 Una vez se tiene la matriz, se reconstruye la lista mas larga. Cuando los elementos son iguales, se hace un push back del elemento y se avanza diagonalmnente.
 Si el siguiente elemento de i es mayor al siguiente elemento de j, se avanza i y si no se avanza j.

 El coste del algoritmo es de O(n*m) donde n y m son las longitudes de sus respectivas listas de reproduccion.
 Esto se debe a que la construccion de la matriz, en el peor de los casos se recorreran las dos listas y por lo tanto seran dos iteraciones y tendra un coste O(n*m).
 En cambio, la reconstruccion de la lista de reproduccion tiene un coste proporcional a la longitud de la lista mas larga, que en el peor de los casos sera O(n + m).

 vector<int> morning = Lista de canciones turno de mañana
 vector<int> evening = Lista de canciones turno de tarde
 Matriz<int> M(m + 1, n + 1, 0) = Matriz de programacion dinamica, 0 = infinito
 map<string, int> mapa = mapa con las canciones y sus identificares
 map<int, string> mapaInv = mapa invertido con las canciones y sus identificares
 vector<string> ret =  vector con la lista solucion

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
* const vector<int>& l1 = lista de reproduccion morning
* const vector<int>& l2 = lista de reproduccion evening
* map<int, string> mapa =  mapa invertido con las canciones y sus identificadores
*/
void construirListaReproduccion(const vector<int>& l1, const vector<int>& l2, map<int, string> mapa) {
	int m = l1.size(), n = l2.size();

	// Caso base dentro
	// i==0 M[0][j]=0 lista1 no tiene canciones
	// j==0 M[i][0]=0 lista2 no tiene canciones
	Matriz<int> M(m + 1, n + 1, 0);

	// Recursivo
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (l1[i - 1] == l2[j - 1]) {
				M[i][j] = M[i - 1][j - 1] + 1;
			}
			else {
				M[i][j] = max(M[i - 1][j], M[i][j - 1]);
			}
		}
	}

	// Reconstruir la lista mas larga
	int i = m, j = n;
	vector<string> ret;
	while (i > 0 && j > 0) {
		if (l1[i - 1] == l2[j - 1]) {
			ret.push_back(mapa[l1[i - 1]]);
			--i; --j;
		}
		else if (M[i - 1][j] > M[i][j - 1]) --i;
		else --j;
	}

	// Se imprime la solución
	for (int k = ret.size() - 1; k >= 0; --k) {
		cout << ret[k] << " ";
	}
	cout << "\n";
}

bool resuelveCaso() {
	string lista1, lista2, song;
	// leer los datos de la entrada
	getline(cin, lista1);
	if (!std::cin)  return false;
	getline(cin, lista2);

	stringstream ss1(lista1);
	stringstream ss2(lista2);
	vector<int> morning;
	vector<int> evening;

	map<string, int> mapa;
	map<int, string> mapaInv;
	int cont = 1;

	int tmp;
	while (ss1 >> song) {
		if (mapa.count(song) >= 1) { // Ya esta en el mapa
			tmp = mapa[song];
		}
		else { // No esta en el mapa
			mapa[song] = cont;
			mapaInv[cont] = song;
			tmp = cont;
			cont++;
		}

		morning.push_back(tmp);
	}

	while (ss2 >> song) {
		if (mapa.count(song) >= 1) { // Ya esta en el mapa
			tmp = mapa[song];
		}
		else { // No esta en el mapa
			mapa[song] = cont;
			mapaInv[cont] = song;
			tmp = cont;
			cont++;
		}

		evening.push_back(tmp);
	}


	construirListaReproduccion(morning, evening, mapaInv);


	return true;
}
//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
