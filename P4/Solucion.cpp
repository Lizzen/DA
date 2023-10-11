
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras d�az
 * Nombre y Apellidos: DA58 Alejandro Zamorano M�ndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "CaminoMasCorto.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 La complejidad del c�digo es O(n) ya que crear el grafo supone un coste (V + A) y recorrerlo es grado(v).
 Esto se debe a que recorre todos los v�rtices buscando el menor coste de las distancias de Alex y Lucas respecto a un v�rtice y 
 el v�rtice respecto al trabajo.
 
 El camino correcto ser� el camino donde Lucas y Alex empiezan a coincidir, si es posible.

 v son los vertices
 a son las aristas
 pa es el vertice inicial de Alex
 pl es el vertice inicial de Lucas
 pt es el vertice inicial del trabajo
 ca es el camino mas corto desde el vertice respecto a Alex
 cl es el camino mas corto desde el vertice respecto a Lucas
 ct es el camino mas corto desde el vertice respecto al trabajo
 total es el total del coste de cada posible camino
 min es el coste minimo buscado

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int v = 0, a, pa, pl, pt;

    cin >> v >> a >> pa >> pl >> pt;

    if (v == 0) {       // fin de entrada si no hay vertices
        return false;
    }

    Grafo g(v);

    int auxG1, auxG2;
    for (int i = 0; i < a; ++i) {
        cin >> auxG1 >> auxG2;
        g.ponArista(auxG1 - 1, auxG2 - 1);
    }

    CaminoMasCorto ca(g, pa -1);
    CaminoMasCorto cl(g, pl -1);
    CaminoMasCorto ct(g, pt -1);
    int min = 200000, total;

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < v; ++i) {
        total = ca.camino(i) + cl.camino(i) + ct.camino(i);
        
        if (total < min) {
            min = total;
        }
    }
    // escribir la soluci�n
    cout << min << "\n";

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
