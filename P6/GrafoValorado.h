/*
 * Implementaci�n de grafos no dirigidos valorados
 * Copyright (c) 2020  Alberto Verdejo
 * Modificado por 2023 Ignacio F�bregas
 */

#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>


template <typename Valor>
class Arista {
public:
    Arista() : pimpl(nullptr) {}
    Arista(int v, int w, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, valor)) {}

    int uno() const { return pimpl->v; }

    int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }

    Valor valor() const { return pimpl->valor; }

    //M�todo para depurar
    void print(std::ostream& o = std::cout) const {
        o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
    }

    bool operator<(Arista<Valor> const& b) const {
        return valor() < b.valor();
    }

    bool operator>(Arista<Valor> const& b) const {
        return b.valor() < valor();
    }

private:
    struct Arista_impl {
        int v, w;
        Valor valor;
        Arista_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
    };

    std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, Arista<Valor> const& ar) {
    ar.print(o);
    return o;
}

template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un v�rtice

template <typename Valor>
class GrafoValorado {
public:

    /** Crea un grafo valorado con V v�rtices, sin aristas. */
    GrafoValorado(int V) : _V(V), _A(0), _ady(_V) { }

    /**
     * Crea un grafo valorado a partir de los datos en el flujo de entrada (si puede).
     * primer es el �ndice del primer v�rtice del grafo en el entrada.
     */
    GrafoValorado(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        Valor c;
        flujo >> E;
        while (E--) {
            flujo >> v >> w >> c;
            ponArista({ v - primer, w - primer, c });
        }
    }

    /** Devuelve el n�mero de v�rtices del grafo. */
    int V() const { return _V; }

    /** Devuelve el n�mero de aristas del grafo. */
    int A() const { return _A; }

    /**
     * A�ade una arista al grafo.
     * @throws invalid_argument si alg�n v�rtice no existe
     */
    void ponArista(Arista<Valor> arista) {
        int v = arista.uno(), w = arista.otro(v);
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::invalid_argument("Vertice inexistente");
        ++_A;
        _ady[v].push_back(arista);
        _ady[w].push_back(arista);
    }

    /**
     * Devuelve la lista de adyacentes de v.
     * @throws invalid_argument si v no existe
     */
    AdysVal<Valor> const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::invalid_argument("Vertice inexistente");
        return _ady[v];
    }

    /** Devuelve las aristas del grafo. */
    std::vector<Arista<Valor>> aristas() const {
        std::vector<Arista<Valor>> ars;
        for (int v = 0; v < V(); ++v)
            for (auto arista : ady(v))
                if (v < arista.otro(v))
                    ars.push_back(arista);
        return ars;
    }

    /**  Muestra el grafo en el stream de salida o */
    void print(std::ostream& o = std::cout) const {
        o << _V << " v�rtices, " << _A << " aristas\n";
        for (auto v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto const& w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }

private:
    int _V;   //n�mero de v�rtices
    int _A;   //n�mero de aristas
    std::vector<AdysVal<Valor>> _ady;   //vector de listas de adyacentes
};

/** ara mostrar grafos por la salida est�ndar. */
template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, GrafoValorado<Valor> const& g) {
    g.print(o);
    return o;
}

#endif /* GRAFOVALORADO_H_ */
