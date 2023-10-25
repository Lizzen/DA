
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras D�az
 * Nombre y Apellidos: DA58 Alejandro Zamorano M�ndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h" 
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El problema trata de unir los conjuntos y usar el algoritmo de Kruskal para obtener el camino con mayor coste del
 recorrido de menor coste posible.
 Si existe m�s de un conjunto significa que hay alguna ciudad(v�rtice) que no est� conecta y es imposible llegar a ella,
 por lo tanto devolver� "Imposible".
 
 El problema tiene una complejidad de O(N*M) por la uni�n rapida de aristas donde N es el n�mero de elementos y M las llamadas a unir.
 El algoritmo de Kruskal tiene un coste O(AlogA) donde A es el n�mero de aristas ya que la operaci�n unir y unidos tienen una complejidad lg*V 
 donde V es el n�mero de v�rtices y se producen con una frecuencia V-1 en el caso de unir y A en el caso de unidos.

 Valor max: Coste del camino m�s caro del menor recorrido posible.
 int n: N�mero de v�rtices(ciudades)
 int m: N�mero de aristas(carreteras)
 ConjuntosDisjuntos cj(n): conjuntos disjuntos
 GrafoValorado<int> g(n);  grafo valorado con el coste de cada carretera
 int orig: v�rtice origen
 int dest: v�rtce destino
 int c: coste de la carretera que une v con a
 ARM_Kruskal<int> arm(g): Variable de la clase ARM_Kruskal
 @ </answer> */
 

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    
    
    // resolver el caso posiblemente llamando a otras funciones y escribir la soluci�n
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
