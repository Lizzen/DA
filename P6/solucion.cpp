
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 * Nombre y Apellidos: DA58 Alejandro Zamorano Méndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h" 
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema trata de unir los conjuntos y usar el algoritmo de Kruskal para obtener el camino con mayor coste del
 recorrido de menor coste posible.
 Si existe más de un conjunto significa que hay alguna ciudad(vértice) que no está conecta y es imposible llegar a ella,
 por lo tanto devolverá "Imposible".
 
 El problema tiene una complejidad de O(N*M) por la unión rapida de aristas donde N es el número de elementos y M las llamadas a unir.
 El algoritmo de Kruskal tiene un coste O(AlogA) donde A es el número de aristas ya que la operación unir y unidos tienen una complejidad lg*V 
 donde V es el número de vértices y se producen con una frecuencia V-1 en el caso de unir y A en el caso de unidos.

 Valor max: Coste del camino más caro del menor recorrido posible.
 int n: Número de vértices(ciudades)
 int m: Número de aristas(carreteras)
 ConjuntosDisjuntos cj(n): conjuntos disjuntos
 GrafoValorado<int> g(n);  grafo valorado con el coste de cada carretera
 int orig: vértice origen
 int dest: vértce destino
 int c: coste de la carretera que une v con a
 ARM_Kruskal<int> arm(g): Variable de la clase ARM_Kruskal
 @ </answer> */
 

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor max;
public:
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }

    Valor costeMax() const {
        return max;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        max = 0;
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                if (max < a.valor()) {
                    max = a.valor();
                }
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};

bool resuelveCaso() {
    int n, m;
    // leer los datos de la entrada
    cin >> n >> m;
    if (!std::cin)  // fin de la entrada
        return false;

    ConjuntosDisjuntos cj(n);
    GrafoValorado<int> g(n);
  
    int orig, dest, c;
    for (int i = 0; i < m; ++i) {
        cin >> orig >> dest >> c;
        cj.unir(orig - 1, dest - 1);
        g.ponArista({ orig - 1 , dest - 1 , c });
    }
    
    
    // resolver el caso posiblemente llamando a otras funciones y escribir la solución
    if (cj.num_cjtos() > 1) {
        cout << "Imposible" << "\n";
    }
    else {
        ARM_Kruskal<int> arm(g);
        cout << arm.costeMax() << "\n";
    }
     
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
