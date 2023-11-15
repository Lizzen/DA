/*
 * Implementaci�n de grafos dirigidos valorados
 * Copyright (c) 2020  Alberto Verdejo
 * Modificado por 2023 Ignacio F�bregas
 */

#ifndef DIGRAFOVALORADO_H_
#define DIGRAFOVALORADO_H_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

    template <typename Valor>
class AristaDirigida {
public:
    AristaDirigida() : pimpl(nullptr) {}

    AristaDirigida(long int v, long int w, Valor valor) : pimpl(std::make_shared<AristaDirigida_impl>(v, w, valor)) {}

    int desde() const { return pimpl->v; }

    int hasta() const { return pimpl->w; }

    Valor valor() const { return pimpl->valor; }

    void print(std::ostream& o = std::cout) const {
        o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
    }

    bool operator<(AristaDirigida<Valor> const& b) const {
        return valor() < b.valor();
    }

    bool operator>(AristaDirigida<Valor> const& b) const {
        return b.valor() < valor();
    }

private:
    struct AristaDirigida_impl {
        int v, w;
        Valor valor;
        AristaDirigida_impl(long int v, long int w, Valor valor) : v(v), w(w), valor(valor) {}
    };
    std::shared_ptr<AristaDirigida_impl> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, AristaDirigida<Valor> const& ar) {
    ar.print(o);
    return o;
}

template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor>>;  // lista de adyacentes a  un v�rtice

template <typename Valor>
class DigrafoValorado {
public:

    /** Crea un grafo dirigido y valorado con V v�rtices */
    DigrafoValorado(long int v) : _V(v), _A(0), _ady(_V) {}

    /**
     * Crea un grafo dirigido y valorado a partir de los datos en el flujo de entrada (si puede).
     * primer es el �ndice del primer v�rtice del grafo en el entrada.
     */
    DigrafoValorado(std::istream& flujo, int primer = 0) : _A(0) {
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
    long int V() const { return _V; }

    /** Devuelve el n�mero de aristas del grafo. */
    long int A() const { return _A; }

    /**
     * A�ade la arista dirigida v-w al grafo.
     * @throws invalid_argument si alg�n v�rtice no existe
     */
    void ponArista(AristaDirigida<Valor> arista) {
        int v = arista.desde(), w = arista.hasta();
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::invalid_argument("Vertice inexistente");
        ++_A;
        _ady[v].push_back(arista);
    }

    /** Comprueba si hay arista de v a w. */
    bool hayArista(long int v, long int w) const {
        for (auto a : _ady[v])
            if (a.hasta() == w) return true;
        return false;
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws invalid_argument si v no existe
     */
    AdysDirVal<Valor> const& ady(long int v) const {
        if (v < 0 || v >= _V)
            throw std::invalid_argument("Vertice inexistente");
        return _ady[v];
    }

    /** Devuelve el grafo dirigido inverso. */
    DigrafoValorado<Valor> inverso() const {
        DigrafoValorado<Valor> inv(_V);
        for (auto v = 0; v < _V; ++v) {
            for (auto a : _ady[v]) {
                inv.ponArista({ a.hasta(), a.desde(), a.valor() });
            }
        }
        return inv;
    }

    /** Muestra el grafo en el stream de salida o */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vértices, " << _A << " aristas\n";
        for (auto v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto a : _ady[v]) {
                o << a << " ";
            }
            o << "\n";
        }
    }

private:
    long int _V;   //n�mero de v�rtices
    long int _A;   //n�mero de aristas
    std::vector<AdysDirVal<Valor>> _ady;   // vector de listas de adyacentes

};

/** Para mostrar grafos por la salida est�ndar. */
template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, const DigrafoValorado<Valor>& g) {
    g.print(o);
    return o;
}


#endif /*  DIGRAFOVALORADO_H_ */