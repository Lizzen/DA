
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras D�az
 * Nombre y Apellidos: DA58 Alejandro Zamorano Mend�z
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
//#include <...>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El programa consite en ir recorriendo la matriz visitando el  elemento mtr[i][j] a la derecha o abajo del actual.
 En el programa se va marcando todas las casillas visitadas. 
 Se mira si el elemento siguiente (i + mtr[i][j] para abajo, j + mtr[i][j] para la derecha) se puede visitar. Si se puede,
 visitar� la casilla con una funci�n recursiva, si no se puede en ninguno, se marcar� d�ndole el valor a la matriz auxiiar 0.
 Por defecto, la matriz auxiliar est� inicializada a -1.
 Como cada funci�n va retornando el cuantos caminos posibles existen desde �l, al final se devolver� el total de caminos posibles
 existentes para ir desde mtr[0][0] hasta mtr[n][m] solo moviendose abajo o a la derecha.

 El programa est� resuelto con programaci�n din�mica descendente a trav�s de recursi�n.
 El coste del algoritmo es O(n*m) ya que en el peor caso posible se visitar�n todos los elementos de la matriz.
 La funci�n recursiva se resume en: 
 Se calcula 2(n sobre m) - 1 terminos, (m+1)(n-m+1)-1 terminos distintos.

 int n = n�mero de filas de la matriz.
 int m = n�mero de columnas de la matriz.
 Matriz<int> mtr =  matriz del caso.
 Matriz<long long int> aux = matriz auxiliar que tambi�n sirve para marcar.

 long long int abajo_o_derecha(const int i, const int j, const int filas, const int cols, Matriz<int> const& mtr, Matriz<long long int>& aux)

 const int i = fila actual.
 const int j = columna actual.
 const int filas = n�mero de filas de la matriz.
 const int cols = n�mero de filas de la matriz.
 Matriz<int> mtr =  matriz del caso.
 Matriz<long long int>& aux = matriz auxiliar que tambi�n sirve para marcar.
 int newFila = Siguiente elemento a la derecha.
 int newCols = Siguiente elemento abajo.
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

long long int abajo_o_derecha(const int i, const int j, const int filas, const int cols, Matriz<int> const& mtr, Matriz<long long int>& aux) {
    
    if (j == cols && i == filas) {return 1;}
    else if (aux[i][j] != -1) { return aux[i][j]; }

    int newFila = i + mtr[i][j];
    int newCols = j + mtr[i][j];
    
    if (newFila <= filas && newCols <= cols) {
        aux[i][j] = abajo_o_derecha(newFila, j, filas, cols, mtr, aux) + abajo_o_derecha(i, newCols, filas, cols, mtr, aux);
    }
    else if (newFila > filas && newCols <= cols) {
        aux[i][j] = abajo_o_derecha(i, newCols, filas, cols, mtr, aux);
    }
    else if (newFila <= filas && newCols > cols) {
        aux[i][j] = abajo_o_derecha(newFila, j, filas, cols, mtr, aux);
    }
    else {
        aux[i][j] = 0;
    }
        
    return aux[i][j];
}

bool resuelveCaso() {
    int n, m;
    // leer los datos de la entrada
    cin >> n >> m;
    if (!std::cin)  // fin de la entrada
        return false;

    int elem;
    Matriz<int> mtr(n, m, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> elem;
            mtr[i][j] = elem;
        }
    }

    // resolver el caso posiblemente llamando a otras funciones y escribir la soluci�n
    Matriz<long long int> aux(n, m, -1);
    cout << abajo_o_derecha(0, 0, n - 1, m - 1, mtr, aux) << "\n";

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
