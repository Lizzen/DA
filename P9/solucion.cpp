
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras D�az
 * Nombre y Apellidos: DA58 Alejandro Zamorano M�ndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El problema consiste en mirar la distancia de cada v�rtice para saber si se acercan m�s a la planta desalinizadora del norte 
 o la planta desalinizadora del sur.
 Con DijsKstra, se podr�a comprobrar desde (n-2)/2 la distancia que hay entre la planta norte y la planta sur, indicandole el origen y destino.
 Una vez que tienes las distancias minimas al norte o al sur, se puede saber el camino minimo y se descartar�a los caminos que ya ha recorrido 
 los camiones del norte o sur que elevan demasiado el coste para uno u otro.




 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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

    // resolver el caso posiblemente llamando a otras funciones y escribir la soluci�n
    long int mitad = (n - 2) / 2;
    Dijkstra<long int> djkN(dv, 0);
    Dijkstra<long int> djkN(dv, n);

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
