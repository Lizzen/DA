
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

 /*
 int  resolverdor_rec(const string cadena, const int pos, int i, int j, Matriz<int> &m, bool fin_der) {
     int& res = m[i][j];
     string cadena1_aux = cadena;
     string cadena2_aux = cadena;
     if (res == -1)
     {
         if (i >= j)
         {
             res = 0;
         }
         else {
             if (cadena[i] == cadena[j])
             {
                 res = resolverdor_rec(cadena,pos, i+1, j-1, m);
             }
             else {
                 if (!fin_der)
                 {
                     return
                 }
                 int r1 = resolverdor_rec(cadena1_aux.insert(pos, 1, cadena1_aux[i]), pos, i + 1, j, m, false) + 1;
                 int r2 = r1;
                 if (pos == cadena.size())
                 {
                     r2 = resolverdor_rec(cadena2_aux.insert(0, 1, cadena2_aux[j]), pos, i, j - 1, m, true) + 1;
                 }
                 res = min(r1, r2);
             }
         }

     }
     return res;
 }
 */
int resolverdor_rec(const string& cadena, int i, int j, Matriz<int>& m) {
    if (i >= j) {
        return 0;
    }

    int& res = m[i][j];

    if (res == -1) {
        if (cadena[i] == cadena[j]) {
            res = resolverdor_rec(cadena, i + 1, j - 1, m);
        }
        else {
            res = min(resolverdor_rec(cadena, i + 1, j, m), resolverdor_rec(cadena, i, j - 1, m)) + 1;
        }
    }

    return res;
}

void reconstruir_sol(const string& cadena, const Matriz<int>& m, int i, int j, string& palindromo) {
    if (i <= j) {
        if (i == j || cadena[i] == cadena[j]) {
            palindromo.push_back(cadena[i]);
            if (i != j) {
                reconstruir_sol(cadena, m, i + 1, j - 1, palindromo);
            }
        }
        else {
            if (m[i + 1][j] < m[i][j - 1]) {
                palindromo.push_back(cadena[j]);
                reconstruir_sol(cadena, m, i, j - 1, palindromo);
            }
            else {
                palindromo.push_back(cadena[i]);
                reconstruir_sol(cadena, m, i + 1, j, palindromo);
            }
        }
    }
}

bool resuelveCaso() {
    string cadena;
    cin >> cadena;

    if (cadena == "vacio") {
        return false;  // Fin de la entrada
    }

    Matriz<int> m(cadena.size(), cadena.size(), -1);

    int resul = resolverdor_rec(cadena, 0, cadena.size() - 1, m);

    string palindromo;
    reconstruir_sol(cadena, m, 0, cadena.size() - 1, palindromo);

    cout << resul << " " << palindromo << "\n";

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
