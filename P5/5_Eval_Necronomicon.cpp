
/*@ <answer>
 *
 * Nombre y Apellidos: D58 Alejandro Zamorano Méndez y D27 David Ferreras Díaz 
 *
 *@ </answer> */


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Digrafo.h"	// propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste del programa es O(V+A) ya que recorremos todo el grafo en el dfs para poder comprobar si existe un ciclo y tambien para si el programa puede
 finalizar para poder saber si el programa es valido siempre, a veces o nunca. Para ello primero creamos el grafo con un vertice extra de los requeridos
 ya que este no tendra adyacencia ninguna y nos podra decir si finaliza el programa o no, luego construimos el grafo de forma que los saltos J o C tengan
 bien guardados sus destinos. Posteriormente nos metemos en el CicloDirigido y realizamos el bfs comprobando si el programa finaliza (gracias a la adyacencia
 del vertice extra como nombre anteriormente) y tambien comprobamos la existencia de un ciclo recorriendo los diferentes destinos de los vertices del grafo.

	bool termina -> Si es true el programa llega el final en caso contrario no
	bool hayCiclo -> Comprueba la existencia de ciclos en el programa
	vector<bool> apilado -> Devuelve true o false dependiendo si el vector ha sido apilado anteriormente para detectar un ciclo en el grafo
	vector<bool> visit -> Vector encargado de comprobar si ese vertice a sido visitado o no
	int nCasos -> Numero de funciones (vertices) del programa
	char ins -> Instruccion del programa (A, J o C)
	int salto -> Vertice destino de C o J
	Digrafo programa(nCasos + 1) -> Grafo dirigido que guarda el programa que queremos comprobar
	CicloDirigido sol(programa) -> Objeto encargado de obetener la solucion a nuestro problema


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CicloDirigido {
public:
	CicloDirigido(Digrafo const& g) :visit(g.V(), false), termina(false), apilado(g.V(), false), hayCiclo(false) {
		dfs(g, 0);
	}

	bool acaba() const { return termina; }
	bool hayCiclos() const { return hayCiclo; }

private:
	bool termina;
	bool hayCiclo;
	vector<bool> apilado;
	vector<bool> visit;

	//Funcion que apila el vertice y busca por todos los adyacentes si el grafo termina o hay un ciclo.
	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;

		if (g.ady(v).size() == 0) termina = true;
		else {
			for (int w : g.ady(v)) {
				if (!visit[w]) 
					dfs(g, w);
				else if (apilado[w]) 
					hayCiclo = true;
			}
		}

		apilado[v] = false;
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int nCasos;
	cin >> nCasos;
	if (!std::cin)		// fin de la entrada 
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	char ins;
	int salto;
	Digrafo programa(nCasos + 1);

	for (int i = 0; i < nCasos; ++i) {
		cin >> ins;
		if (ins == 'A') {
			programa.ponArista(i, i + 1);
		}
		else {
			cin >> salto;
			if (ins == 'J') {
				programa.ponArista(i, salto - 1);
			}
			else if (ins == 'C') {
				programa.ponArista(i, salto - 1);
				programa.ponArista(i, i + 1);
			}
		}
	}


	CicloDirigido sol(programa);

	// escribir la solución

	if (!sol.acaba()) cout << "NUNCA" << endl;
	else {
		if (sol.hayCiclos()) cout << "A VECES" << endl;
		else cout << "SIEMPRE" << endl;
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
