
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


struct candidatura {
    int id;
    double votos;
    double coef;
};

struct comp { 
    bool operator()(candidatura const& a, candidatura const& b) {
        if (a.coef == b.coef && a.votos == b.votos) {
            return a.id < b.id; // Ordena por id
        }
        else if (a.coef == b.coef) {
            return a.votos > b.votos;
        }
        return a.coef > b.coef;   // Ordena de mayor a menor
    }
};

void escanos(PriorityQueue<candidatura, comp>& heap, const int N, vector<double>& esc) {
    for (int i = N; i > 0; i--) {
        candidatura a = heap.top(); heap.pop();
        esc[a.id] += 1;
        a.coef = a.votos / (1.0 + esc[a.id]);
        heap.push(a);
    }
}

bool resuelveCaso() {
    int C, N;
    // leer los datos de la entrada
    cin >> C >> N;
    if (N == 0 && C == 0)
        return false;

    PriorityQueue<candidatura, comp> heap;
    double coef = 0, votos;
    vector<double> esc(C);
    for (int i = 0; i < C; i++) {
        cin >> votos;
        coef = votos / (1.0 + 0);
        esc[i] = 0;
        heap.push({i, votos, coef});
    }
    
    // resolver el caso posiblemente llamando a otras funciones
    escanos(heap, N, esc);
    // escribir la solución
    for (int escano : esc) {
        cout << escano << " ";
    }

    cout << "\n";
    
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
