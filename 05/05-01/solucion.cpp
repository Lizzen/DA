
/*@ <answer>
 *
 * Nombre y Apellidos:  DA27 David Ferreras Díaz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Éste problema consiste en recorrer todos los nodos del digrafo desde el origen para poder dar con la solución, los dos pasados por parámetros.
 Se busca que, mediante operaciones (+1, *2, /3) aplicadas al marcador inicial, se pueda dar con el recorrido que de dicho resultado.
 Para ello hay que recorrer el digrafo mediante un recorrido en anchura para explorar todas las soluciones posibles.

 Este problema tiene una compljidad O(n) donde n = O(v+A) ya que hay que recorrer todos los vértices y sus ayacentes al menos una vez.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


const int MAX = 10000;      // tamano de la cola
const int INF = 1000000000; // ∞

// v : vertice   i: operacion seleccionada
int adyacente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX; // + 1
    case 1: return (v * 2) % MAX; // * 2
    case 2: return v / 3; // / 3
    }
}

int bfs(int origen, int destino) {
    if (origen == destino) return 0;
    vector<int> distancia(MAX, INF);
    distancia[origen] = 0;
    queue<int> cola; cola.push(origen);     // se agrega el nodo a la cola para el recorrido
    while (!cola.empty()) {
        int v = cola.front(); cola.pop();   // se extrae el nodo v de la parte frontal de la cola
        for (int i = 0; i < 3; ++i) {       // se recorren los nodos ayacentes
            int w = adyacente(v, i);

            /* Se verifica si su distancia es infinito.Si lo es se suma 1 a la distancia de v.
            *  Si w es igual al destino, la funcion devuelve la distancia de w. 
            *  Si no, se agregara a la cola para explorar los nodos ayacentes de w en la siguiente iteración.
            */
            if (distancia[w] == INF) {     
                distancia[w] = distancia[v] + 1;
                if (w == destino) return distancia[w];
                else cola.push(w);
            }
        }
    }
}

bool resuelveCaso() {
    int marcador, result;
    // leer los datos de la entrada
    cin >> marcador >> result;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones y escribir solucion
    cout << bfs(marcador, result) << "\n";

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
