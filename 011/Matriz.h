/*
 * Implementación de matrices (arrays bidimensionales)
 * Copyright (c) 2020  Alberto Verdejo
 * Modificado por 2023 Ignacio Fábregas
 */

#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <ostream>

template <typename Object>
class Matriz {
public:
    // crea una matriz con fils filas y cols columnas,
    // con todas sus celdas inicializadas al valor e
    Matriz(int fils = 0, int cols = 0, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}
    
    // operadores para poder utilizar notación M[i][j]
    std::vector<Object> const& operator[](int f) const {
        return datos[f];
    }

    std::vector<Object> & operator[](int f) {
        return datos[f];
    }
    
    // Métodos que lanzan una excepción si la posición no existe
    Object const& at(int f, int c) const {
        return datos.at(f).at(c);
    }

    Object & at(int f, int c) {
        return datos.at(f).at(c);
    }
    
    int numfils() const { return datos.size(); }

    int numcols() const { return numfils() > 0 ? datos[0].size() : 0; }
    
    bool posCorrecta(int f, int c) const {
        return 0 <= f && f < numfils() && 0 <= c && c < numcols();
    }

    void print(const Matriz<Object> m) {
        for (int i = 0; i < m.numfils(); i++)
        {
            for (int j = 0; j < m.numcols(); j++)
            {
                std::cout << m[i][j] << " ";
            }
            std::cout << endl;
        }
        std::cout << endl;
    }
    
private:
    std::vector<std::vector<Object>> datos;
};

//Escritura de la Matriz
template <typename Object>
inline std::ostream & operator<<(std::ostream & out, Matriz<Object> const& m) {
   for (int i = 0; i < m.numfils(); ++i) {
      for (int j = 0; j < m.numcols(); ++j) {
         out << m[i][j] << ' ';
      }
      out << '\n';
   }
   return out;
}

#endif /* MATRIZ_H */
