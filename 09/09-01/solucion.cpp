
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 * Nombre y Apellidos: DA58 Alejandro Zamorano Méndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int tuneles(vector<pair<int, int>> &edificios) {
    int numTuneles = 0;
    int extrEActual = 0;

    for (const auto& edificio : edificios) {
        int extrW = edificio.first;
        int extrE = edificio.second;

        if (extrW > extrEActual) {
            numTuneles++;
            extrEActual = extrE;
        }
    }

    return numTuneles;
}

bool resuelveCaso() {
    int n;
    cin >> n;

    if (n == 0)  // fin de la entrada
        return false;

    // leer los datos de la entrada
    vector<pair<int, int>> edificios;
    for (int i = 0; i < n; ++i) {
        long int w, e;
        cin >> w >> e;
        edificios.push_back({ w,e });
    }

    // resolver el caso posiblemente llamando a otras funciones y escribir la solución
    cout << tuneles(edificios) << "\n";

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