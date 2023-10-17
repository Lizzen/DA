#ifndef CICLODIRIGIDO_H_
#define CICLODIRIGIDO_H_

#include "Digrafo.h"
#include <iostream>
#include <deque>

using namespace std;

class CicloDirigido {
public:
	// g es DAG
	CicloDirigido(Digrafo const& g) : visit(g.V(), false),
		apilado(g.V(), false), _orden(g.V()) {
		for (int v = g.V() -1; v > -1; --v) {
			if (!visit[v] && !hayciclo)
				dfs(g, v);
		}
		imprimir(g.V());
	}

	void imprimir(int v) {

		if (hayciclo) {
			cout << "imposible" << "\n";
			return;
		}

		for (int i = 0; i < v; ++i) {
			cout << _orden[i] + 1<< " ";
		}

		cout << "\n";
	}

private:
	std::vector<bool> visit;
	std::vector<bool> apilado;
	bool hayciclo = false;
	std::deque<int> _orden; // ordenación topológica
	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (hayciclo) {
				return;
			}
			if (!visit[w]) {
				dfs(g, w);
			}
			else if (apilado[w]) {
				hayciclo = true;
			}
		}
		apilado[v] = false;
		_orden.push_front(v);
	}
};

#endif