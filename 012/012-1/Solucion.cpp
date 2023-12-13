
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <climits>
#include <algorithm>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int INF = 100000000;

int min_esfuerzo(vector<int>& cortes) {
    int n = cortes.size();

    // Ordena los cortes de menor a mayor
    sort(cortes.begin(), cortes.end());

    // Inicializa una matriz para almacenar los subproblemas
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

    // El costo de cortar en dos partes es el doble de la longitud
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        if (i < n - 1) {
            dp[i][i + 1] = cortes[i + 1] - cortes[i];
        }
    }

    // Llena la matriz dp utilizando la programación dinámica
    for (int len = 0; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;

            for (int k = i + 1; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + 2 * (cortes[j] - cortes[i]));
            }
        }
    }

    return dp[0][n-1];
}


bool resuelveCaso() {
    int L, N;
    // leer los datos de la entrada
    cin >> L >> N;
    if (L == 0)
        return false;

    vector<int> cortes(N);
    int corte;
    for (int i = 0; i < N; ++i) {
        cin >> corte;
        cortes.push_back(corte);
    }

    // resolver el caso posiblemente llamando a otras funciones
    cout << min_esfuerzo(cortes) << "\n";

    // escribir la solución

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
