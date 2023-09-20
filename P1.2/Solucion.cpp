
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n <= 0)
        return false;

    Set<int> arbol;
    int elem, m, cons;
    for (int i = 0; i < n; ++i) {
        cin >> elem;
        arbol.insert(elem);
    }

    if (arbol.empty()) {
        return true;
    }

    cin >> m;
    // resolver el caso posiblemente llamando a otras funciones
    arbol.print();
    for (int i = 0; i < m; ++i) {
        cin >> cons;
        int k = arbol.kesimo(cons);

        if (k == -1) {
            cout << "??\n";
        }
        else {
            cout << k << "\n";
        }
    }
    // escribir la solución
    cout << "---" << "\n";
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
