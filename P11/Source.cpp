
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
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema consiste en ir comparando los elementos de las listas. Si dos canciones se repiten, se coge como palabra valida y se guarda su posicion.
 Si se repite una cancion en distinto orden en una lista respecto la otra, la anterior cancion o es valida.

 El algoritmo consiste en ir visitando los elementos de las dos listas. Si coincide, 
 se guardan en un vector(k) de enteros la suma de i(posicion en lista de mañana) + j (posicion en lista de tarde) y en un vector de string, la cancion.
 En cuanto coinciden, se llama a la funcion recursiva comparando el siguiente elemento de la lista de mañana, con el primer elemento de tarde.
 Si no, se sigue comparando el elemento del vector de mañana con el siguiente elemento de tarde hasta encontrar uno igual o que j = evening.size().
 
 Al final se comparan los enteros del vector k. Si el indice es mayor que el anterior elemento,se descarta. 

 El algoritmo en el peor caso posible será O(n^2) + O(n*m) ya que se recorre la lista de mañana y la lista de tarde enteras y la matriz solucion entera.

 vector<string> morning = Lista de canciones turno de mañana
 vector<string> evening = Lista de canciones turno de tarde
 int i = posicion de vector morning
 int j = posicion de vector evening
 Matriz<int> cancion(i, j, false) = matriz que guarda las canciones validas
 string sol =  string con la lista solucion

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void reconstruir(const vector<string> morning, const vector<string> evening, Matriz<int> const& cancion,
    int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.append(morning[i]);
    else if (morning[i] == evening[j]) {
        sol.append(morning[i]);
        reconstruir(morning, evening, cancion, i + 1, j - 1, sol);
        sol.append(evening[j]);
    }
    else if (cancion[i][j] == cancion[i + 1][j])
        reconstruir(morning, evening, cancion, i + 1, j, sol);
    else
        reconstruir(morning, evening, cancion, i, j - 1, sol);
}

int lista_graduacion(const vector<string> morning, const vector<string> evening, int i, int j, Matriz<int>& cancion) {
    int& res = cancion[i][j];

    if (res == -1) {
        if (morning[i] == evening[j]) {
            if (i > j) {
                cancion[i][j] = lista_graduacion(morning, evening, i + 1, 0, cancion);
                res = 0;
            }
            else {
                cancion[i][j] = min(lista_graduacion(morning, evening, i + 1, j, cancion), lista_graduacion(morning, evening, i, j + 1, cancion));
                return cancion[i][j];
            }
        }
        else {
            cancion[i][j] = false;
            return min(lista_graduacion(morning, evening, i + 1, j, cancion), lista_graduacion(morning, evening, i, j + 1, cancion));
        }
    }
}

bool resuelveCaso() {
    string lista, song;
    // leer los datos de la entrada
    getline(cin, lista);
    if (!std::cin)  // fin de la entrada
        return false;

    stringstream ss(lista);
    vector<string> morning;
    vector<string> evening;
    int i = 0;
    while (ss >> song) {
        morning.push_back(song);
        ++i;
    }

    getline(cin, lista);
    int j = 0;
    while (ss >> song) {
        evening.push_back(song);
        ++j;
    }
    Matriz<int> cancion(i, j, false);
    // resolver el caso posiblemente llamando a otras funciones
   
    // escribir la solución
    lista_graduacion(morning, evening, 0, 0, cancion);
    string sol;
    reconstruir(morning, evening, cancion, 0, 0, sol);
    cout << sol << "\n";
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
