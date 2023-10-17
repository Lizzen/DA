
/*@ <answer>
 *
 * Nombre y Apellidos:  DA27 David Ferreras Díaz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

#include "CicloDirigido.h"  // propios o los de las estructuras de datos de clase

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


bool resuelveCaso() {
    int v = 0, a = 0;
    // leer los datos de la entrada
    cin >> v >> a;

    if (v == 0)  // fin de la entrada
        return false;

    Digrafo g(v);
    int aux1, aux2;

    for (int i = 0; i < a; ++i) {
        cin >> aux1 >> aux2;
        g.ponArista(aux1 - 1, aux2 - 1);
    }

    CicloDirigido o(g);
    // resolver el caso posiblemente llamando a otras funciones y escribir solucion

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
