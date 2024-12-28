
/*@ <answer>
 *
 * Nombre y Apellidos: David Ferreras Díaz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct paciente {
    string nombre;
    int gravedad;
    int id;
};

struct comp { 
    bool operator()(paciente const& a, paciente const& b) {
        if (a.gravedad == b.gravedad) {
            return a.id < b.id; // Ordena por id
        }
        return a.gravedad > b.gravedad;   // Ordena de mayor a menor
    }
};

string atiende(PriorityQueue<paciente, comp>& heap) {
    paciente a = heap.top(); heap.pop();
    return a.nombre;
}

bool resuelveCaso() {
    int N;
    // leer los datos de la entrada
    cin >> N;
    if (N == 0)
        return false;

    PriorityQueue<paciente, comp> heap;
    char evento;
    string nombre;
    int gravedad;

    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < N; i++) {
        cin >> evento;
        if (evento == 'I') {
            cin >> nombre >> gravedad;
            heap.push({ nombre, gravedad, i });
        }
        else {
            cout << atiende(heap) << "\n";
        }
    }
    // escribir la solución
    cout << "---\n";
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
