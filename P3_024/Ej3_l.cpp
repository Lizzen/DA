#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  // Para std::sort
using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>
 *
 * Nombre y Apellidos: DA65 Alejandro Zamorano Méndez
 * Nombre y Apellidos: DA27 David Ferreras Díaz
 *
 *@ </answer> */

 /*@ <answer>

  Escribe aquí un comentario general sobre la solución, explicando cómo
  se resuelve el problema y cuál es el coste de la solución, en función
  del tamaño del problema.

  El problema consiste en ordenar el canal más visto durante un periodo de tiempo. Para ello iremos actualizando el resultado en función
  a los cambios de espectadores durante un periodo de tiempo.
  Para ello hemos implementado un IndexPQ que se encargará de actualizar los espectadores para cada canal y otro encargado de guardar el tiempo
  de más vistos ordenados de mayor a menor.
  En resultado se necesita un comparador greater personalizado para ordenar los canales de menor a mayor en el caso que la prioridad sea igual.

  La complejidad del algoritmo en su caso peor será 2*(N log(n)) donde n es el número de canales ya que el coste de push es (log(n)) y por lo tanto la implementación del heapsort
  es (NlogN). Como en la salida, el coste de pop es (log(n)), su complejidad también será (nlog(n)).

  int minutos : minutos a comparar
  int canales : número de canales a comparar
  int actualizaciones: número de actualizaciones en ese periodo de tiempo
  IndexPQ<int, std::greater<int>> audiencias(canales+1) : heapshort ordenado por el número de audiencia de mayor a menor
  vector<int> v(canales+1) : Guarda los minutos más vistos
  vector<Canal> resultados : vector para almacenar los resultados ordenados de mayor a menor y ordena por canales de menor a mayor si la prioridad es igual
  int aux : número de canal
  int instante : instante actual
  int inst : instante anterior
  int canal : canal a actualizar
  int espectadores : nuevos expectadores
  @ </answer> */


  // Estructura para almacenar el canal y sus minutos
struct Canal {
    int id;
    int minutos;
};

// Comparador para ordenar los canales
bool compararCanales(const Canal& a, const Canal& b) {
    if (a.minutos == b.minutos) {
        return a.id < b.id; // Si los minutos son iguales, ordenar por ID
    }
    return a.minutos > b.minutos; // Ordenar de mayor a menor por minutos
}

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
bool resuelveCaso() {
    // leer los datos de la entrada
    int minutos, canales, actualizaciones;
    cin >> minutos >> canales >> actualizaciones;

    if (!std::cin)  // fin de la entrada
        return false;

    IndexPQ<int, std::greater<int>> audiencias(canales + 1);
    vector<int> v(canales + 1);

    int aux;
    for (int i = 0; i < canales; ++i) {
        cin >> aux;
        audiencias.push(i + 1, aux);
        v[i + 1] = 0;
    }

    int instante, inst = 0, canal, espectadores;

    for (int i = 0; i < actualizaciones; i++) {
        cin >> instante;
        v[audiencias.top().elem] += (instante - inst);
        cin >> canal;
        while (canal > 0) {
            cin >> espectadores;
            audiencias.update(canal, espectadores);
            cin >> canal;
        }
        inst = instante;
    }

    v[audiencias.top().elem] += (minutos - inst);

    // Resolver el caso posiblemente llamando a otras funciones
    vector<Canal> resultados(canales + 1);
    for (int i = 1; i <= canales; ++i) {
        resultados.push_back({ i, v[i] });
    }

    sort(resultados.begin(), resultados.end(), compararCanales);

    // Escribir la solución
    for (const auto& canal : resultados) {
        if (canal.minutos != 0) {
            cout << canal.id << " " << canal.minutos << "\n";
        }
        
    }
    cout << "---\n";

    return true;
}

// Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
