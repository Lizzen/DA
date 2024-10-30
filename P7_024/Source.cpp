
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 * Nombre y Apellidos: DA65 Alejandro Zamorano Méndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema consiste en mirar cuantos caminos mínimos llegan a la salida antes del tiempo solicitado.
 Para ello, aplicamos Dijkstra con el grafo inverso desde la salida para comprobar todos los caminos posibles que cumplen la condición y así ahorramos realizar 
 el algoritmo para cada nodo.
 La complejidad del algoritmo es O(V+AlogV) ya que el coste del inverso es O(V+A) y al usar el IndexPQ, el coste será de O(V+AlogV).

 int n : Número de nodos
 int sal : Nodo de salida
 int seg : Tiempo máximo que puede tardar
 int p : Número de aristas
 DigrafoValorado<int> dv(n) : Representación del laberinto en un grafo
 int a : Origen de la arista
 int b : destino de la arista
 int val : tiempo de la arista
 int result : resultado de aristas que cumplen las condiciones

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[v] != INF && dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, sal, seg, p;
    cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> sal >> seg >> p;
    DigrafoValorado<int> dv(n);

    int a, b, val, result = 0;

    for (int i = 0; i < p; i++) {
        cin >> a >> b >> val;
        dv.ponArista({ a - 1, b - 1, val });
    }
    dv = dv.inverso();
    // resolver el caso posiblemente llamando a otras funciones
    Dijkstra<int> djk(dv, sal - 1);
    for (int i = 0; i < p; i++) {
        if (i != sal -1 && djk.distancia(i) <= seg && djk.hayCamino(i)) {
            result++;
        }
    }

    // escribir la solución
    cout << result << "\n";
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
