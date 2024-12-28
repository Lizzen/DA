
/*@ <answer>
 *
 * Nombre y Apellidos: David Ferreras D�az
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>


long long int suma(PriorityQueue<long long int> pq) {
    long long int ret = 0, sum = 0, x = 0, y = 0;
    while (pq.size() > 1) {
        x = pq.top();
        pq.pop();
        y = pq.top();
        pq.pop();
        sum = x + y;
        ret += sum;
        pq.push(sum);
    }

    return ret;
}

bool resuelveCaso() {
    int N;
    // leer los datos de la entrada
    cin >> N;
    if (N == 0)
        return false;

    PriorityQueue<long long int> heap;
    int aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        heap.push(aux);
    }

    // resolver el caso posiblemente llamando a otras funciones
    cout << suma(heap) << "\n";

    // escribir la soluci�n

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
