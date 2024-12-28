
/*@ <answer>
 *
 * Nombre y Apellidos: David Ferreras D�az
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
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


struct cliente {
    int caja;
    int periodo;
};

struct comp { 
    bool operator()(cliente const& a, cliente const& b) {
        if (a.periodo == b.periodo) {
            return a.caja < b.caja;
        }
        return a.periodo < b.periodo;   // Ordena de menor a mayor
    }
};

void receptor(PriorityQueue<cliente, comp>& heap, const int periodo) {
    cliente a = heap.top(); heap.pop();
    a.periodo += periodo;
    heap.push(a);
}

bool resuelveCaso() {
    int N, C;
    // leer los datos de la entrada
    cin >> N >> C;
    if (N == 0 && C == 0)
        return false;

    PriorityQueue<cliente, comp> heap;
    long long int id;
    int periodo;
    for (int i = 0; i < N; i++) {
        heap.push({ i + 1, 0 });
    }

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < C; i++) {
        cin >> periodo;
        receptor(heap, periodo);
    }

    // escribir la soluci�n
    cout << heap.top().caja << "\n";
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
