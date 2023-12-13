
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

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema consiste en ir calculando el número de combinacioes de monedas posibles para que de la cantidad a pagar.
 Una vez se tiene la matriz de programacion dinamica, los resultados infinitos se descartan, y los demás se compara el mínimo con el valor de la matriz dp[i][j].
 En la función se comprueba de cuantas formas para obtener la cantidad a pagar, es la que menos monedas usa. Para ello se comprueba, si es multiplo, las posibles combinaciones posibles 
 con el numero monedas[i] que se pueda formar. Para ello, necesitamos el minimo entre el numero minimo de monedas que necesitamos y el numero de combinaciones posibles 
 entre n numeros < dp[i][j] + j - sum(n*monedas[i]).
 Se descartan todos los resultados que necesitan mas monedas que el minimo.
 Si coinciden, se suma 1 al contador de resultados que consiguen el minimo, si hay un nuevo minimo se resetea.

 Al ser ascendente, la llamada inicial es dp(1, 1).
 Caso base: dp[i, i] = INF(Infinito);
 Caso recursivo, i < j:
    dp(i, j) = min{dp[i, j], dp[i, j - monedas] + 1} 

 int C: Cantidad a pagar
 int N: Numero de tipos de moneda del sistema monetario
 vector<int> monedas(N): vector de valores de las monedas
 int min_monedas: minimo de monedas necesarias
 vector<int> dp(C + 1, INF)
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1000000;
int tipos_monedas(vector<int> monedas, int C) {
    int n = monedas.size() - 1;
    vector<int> dp(C + 1, INF);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = monedas[i - 1]; j <= C; ++j) {
            dp[j] = min(dp[j], dp[j - monedas[i - 1]] + 1);
        }
    }

    vector<int> sol(C);
    if (dp[C] != INF) {  // Caso base
        int i = n, j = C;
        while (j > 0) { // no se ha pagado todo
            if (monedas[i] < j && dp[j] < dp[j - monedas[i]] + 1) {
                // tomamos una moneda de tipo i
                dp[j] = dp[j - monedas[i]];
                j = j - monedas[i];
            }
            else // no tomamos más monedas de tipo i
                --i;
        }
    }

    return dp[C];
}

bool resuelveCaso() {
    int C, N;
   // leer los datos de la entrada
    cin >> C >> N;
   if (!std::cin)  // fin de la entrada
      return false;

   vector<int> monedas(N);
   int moneda;
   for (int i = 0; i < N; ++i) {
       cin >> moneda;
       monedas.push_back(moneda);
   }
   // resolver el caso posiblemente llamando a otras funciones
   
   // escribir la solución
   cout << tipos_monedas(monedas, C) << "\n";

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
