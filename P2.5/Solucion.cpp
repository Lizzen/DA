
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 * Nombre y Apellidos: DA58 Alejandro Zamorano Méndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Este problema se resuelve con una cola de prioridad auxiliar por escaños, votos y coeficiente para poder 
 otorgar los escaños de forma correcta. Ademas se guardara la posicion de cada partido para obtenerlo
 de forma ordenada en un vector auxiliar que nos proporcionara la solucion.

 Para ello se utilizan dos funcines cuya complejidad es O(Nlog(N)) ya que las funciones de reordenación son logaritmicas
 y ademas lo recorremos para todos los casos del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

typedef struct {
    double votos;
    double coef;
    double escano;
    int pos;
}tCandidato;

bool operator < (tCandidato c1, tCandidato c2) {
    return ((c1.coef > c2.coef) || (c1.coef == c2.coef && c1.votos > c2.votos) || (c1.coef == c2.coef && c1.votos == c2.votos && c1.pos < c2.pos));
}

void resuelveEscanos(PriorityQueue<tCandidato>& cola, int escanos, vector<int>& sol){
    tCandidato aux;
    for (int i = escanos; i > 0; i--) {
        cola.pop(aux);
        sol[aux.pos] += 1;
        aux.escano++;
        aux.coef = aux.votos / (1.0 + aux.escano);
        cola.push(aux);
    }
}

bool resuelveCaso() {
    int c, e;
    // leer los datos de la entrada
    std::cin >> c >> e;
    if (c == 0 && e == 0)
        return false;

    PriorityQueue<tCandidato> cola;
    vector<int> escanos;
    escanos.reserve(c);
    tCandidato candidato;
    
    for (int i = 0; i < c; i++) {
        escanos.push_back(0);
        cin >> candidato.votos;
        candidato.escano = 0;
        candidato.coef = candidato.votos / (1.0 + candidato.escano);
        candidato.pos = i;
        cola.push(candidato);
    }

    // resolver el caso posiblemente llamando a otras funciones
    resuelveEscanos(cola, e, escanos);
    // escribir la solución
    for (int i = 0; i < c; ++i) {
        cout << escanos[i] << " ";
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
