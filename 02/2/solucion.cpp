
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


struct ucm {
    long long int id;
    long long int periodo;
    int iniPeriodo;
};

struct comp { 
    bool operator()(ucm const& a, ucm const& b) {
        if (a.periodo == b.periodo) {
            return a.id < b.id; // Ordena por id
        }
        return a.periodo < b.periodo;   // Ordena de menor a mayor
    }
};

long long int receptor(PriorityQueue<ucm, comp>& heap) {
    ucm a = heap.top(); heap.pop();
    a.periodo += a.iniPeriodo;
    heap.push(a);
    return a.id;
}

bool resuelveCaso() {
    int N;
    // leer los datos de la entrada
    cin >> N;
    if (N == 0)
        return false;

    PriorityQueue<ucm, comp> heap;
    long long int id;
    int periodo;
    for (int i = 0; i < N; i++) {
        cin >> id >> periodo;
        heap.push({id, periodo, periodo});
    }

    int k = 0;
    cin >> k;
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < k; i++) {
        cout << receptor(heap) << "\n";
    }

    // escribir la soluci�n
    cout << "---\n";
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
