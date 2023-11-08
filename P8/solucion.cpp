
/*@ <answer>
 *
 * Nombre y Apellidos: DA27 David Ferreras D�az
 * Nombre y Apellidos: DA58 Alejandro Zamorano M�ndez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Aplicando la logica el menor valor del precio para las resistencias siempre seran las de menos amperaje posible, por tanto para que no exista la posibilidad
 para que cogiendo dos resistencias sumen el valor necesitado por Leocadia sera un simple sumatorio de los n primeros valores que seran el numero maximo de
 amperaje entre dos, ya que por ejemplo en el 3� caso cogiendo los 110 primeros valores y posteriormente los 190 que restan >=220 sera lo idoneo, esto
 podria parecer exclusivo de los valores pares ya que la division entre 2 % 0, pero con un valor impar serviria igual, ya que, por ejemplo en el 2� caso, si aumentamos
 el limite en 5 la division /2 es 2.5 que si redondeamos a 3 no funciona ya que cogeriamos los valores 1, 2 y 3, 2+3=5 por tanto no sirve.
 Si llega a la mitad, se sumar� las resistencias desde el amperaje maximo (s) hasta n resistencias.

 En coclusi�n, para todo caso, las resistencias con un amperaje de s/2 hasta s no son v�lidas ya que siempre habr�a un par que su suma es s.
 Realizando esta operacion la complejidad de este algoritmo seria O(n) ya que solo estamos sumando la cantidad dada por el nresistencias

int n -> Numero de resistencias solicitadas por el quiosquero
int s -> Numero el cual no puede ser igual a la suma de ningun par de resistencias
int coste -> Suma del dinero requerido por el quiosquero
int mitad -> mitad del valor del amperaje (s) permitido. Desde la mitad hasta s, ninguna de las resistencias ser�n validas.
int valor -> el coste de la resistencia i.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

int resistencias(int n, int s) {
    int mitad = s / 2, coste = 1, valor = 1;

    for (int i = 1; i < n; ++i) {
        if (i == mitad) {
            valor = s;
        }
        else {
            valor++;
        }

        coste += valor;
    }

    return coste;
}

bool resuelveCaso() {
    int n, s;
    cin >> n >> s;
    // leer los datos de la entrada

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones y escribir la soluci�n
    if (n > 1) {
        cout << resistencias(n, s) << "\n";
    }
    else {
        cout << "1" << "\n";
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
