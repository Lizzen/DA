
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


struct tarea {
    long long int comienzo;
    long long int fin;
    long long int repeticion;
};

struct comp { 
    bool operator()(tarea const& a, tarea const& b) {
        return a.comienzo < b.comienzo;   // Ordena de menor a mayor
    }
};

bool conflicto(PriorityQueue<tarea, comp>& heap, const int T) {
    bool fin = false;
    tarea a = heap.top(); heap.pop();
    while (!fin && heap.size() > 0) {
        tarea b = heap.top(); heap.pop();

        if (a.comienzo > T || b.comienzo > T) {
            fin = true;
        }
        else {
            if (a.comienzo == b.comienzo || (a.fin >= b.comienzo)) {
                return true;
            }

            if (a.repeticion > 0) {
                a.comienzo += a.repeticion;
                a.fin += a.repeticion;
                heap.push(a);
            }
            
            a = b;         
        }
    }

    return false;
}

bool resuelveCaso() {
    int N, M;
    long long int T;
    // leer los datos de la entrada
    cin >> N >> M >> T;
    if (!cin)
        return false;

    PriorityQueue<tarea, comp> heap;
    long long int comienzo, fin, repeticion;

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < N; i++) {
        cin >> comienzo >> fin;
        heap.push({ comienzo, fin, 0});
    }

    for (int i = 0; i < M; i++) {
        cin >> comienzo >> fin >> repeticion;
        heap.push({ comienzo, fin, repeticion});
    }
    // escribir la soluci�n
    cout << (conflicto(heap, T) ? "SI\n" :  "NO\n");
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
