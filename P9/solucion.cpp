
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 * Nombre y Apellidos: DA58 Alejandro Zamorano Méndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema consiste en mirar la distancia de cada vértice para saber si se acercan más a la planta desalinizadora del norte
 o la planta desalinizadora del sur.
 Con DijsKstra, se podría comprobrar desde (n-2)/2 la distancia que hay entre la planta norte y la planta sur, indicandole el origen y destino.
 Una vez que tienes las distancias minimas al norte o al sur, se puede saber el camino minimo y se descartaría los caminos que ya ha recorrido
 los camiones del norte o sur que elevan demasiado el coste para uno u otro.




 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, long int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    Valor distancia(int v) const { return dist[v]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    long int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    long int n, m;
    // leer los datos de la entrada
    cin >> n >> m;
    if (!std::cin)
        return false;

    DigrafoValorado<long int> dv(n);
    long int v, a, valor;
    for (int i = 0; i < m; ++i) {
        cin >> v >> a >> valor;
        dv.ponArista({ v - 1, a - 1, valor });
        dv.ponArista({ a - 1, v - 1, valor });
    }

    // resolver el caso posiblemente llamando a otras funciones y escribir la solución
    long int mitad = (n - 2) / 2;
    Dijkstra<long int> djkN(dv, 0);
    vector<long int> costesN;
    for (int i = 1; i < n - 1; ++i) {
        costesN.push_back(djkN.distancia(i));
    }

    Dijkstra<long int> djkS(dv, n - 1);
    vector<long int> costesS;
    for (int i = 1; i < n - 1; ++i) {
        costesS.push_back(djkS.distancia(i));
    }

    sort(costesN.begin(), costesN.end());
    sort(costesS.begin(), costesS.end());

    long int menorCosteTotal = numeric_limits<long int>::max();
    for (int i = 0; i <= mitad; ++i) {
        long int costeTotal = costesN[i] + costesS[mitad - i] + djkN.distancia(n - 1);
        menorCosteTotal = min(menorCosteTotal, costeTotal);
    }

    cout << menorCosteTotal << "\n";

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
