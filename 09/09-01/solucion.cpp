
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras D�az
 * Nombre y Apellidos: DA58 Alejandro Zamorano M�ndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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

    // resolver el caso posiblemente llamando a otras funciones y escribir la soluci�n
    cout << tuneles(edificios) << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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