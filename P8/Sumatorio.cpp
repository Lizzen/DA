/*@ <answer>
 *
 * Nombre y Apellidos: DA58 Alejandro Zamorano Méndez
 * Nombre y Apellidos: DA27 David Ferreras Diaz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;
  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Aplicando la logica el menor valor del precio para las resistencias siempre seran las de menos amperaje posible, por tanto para que no exista la posibilidad
 para que cogiendo dos resistencias sumen el valor necesitado por Leocadia sera un simple sumatorio de los n primeros valores que seran el numero maximo de 
 resistencias entre dos, ya que por ejemplo en el 3º caso cogiendo los 110 primeros valores y posteriormente los 190 que restan >=220 sera lo idoneo, esto
 podria parecer exclusivo de los valores pares ya que la division entre 2 con un valor impar serviria igual, ya que, por ejemplo en el 2º caso, si aumentamos
 el limite en 5 la division /2 es 2.5 que si redondeamos a 3 no funciona ya que cogeriamos los valores 1, 2 y 3, 2+3=5 por tanto no sirve.
 Por tanto esta solucion estaria usando la siguiente formula:

    Total = (Sumatorio de n = 0 hasta maximoResistencias /2) + (Sumatorio de n = max hasta max + (nresistencias - (max/2)))

Realizando esta operacion la complejidad de este algoritmo seria O(n) ya que solo estamos sumando la cantidad dada por el nresistencias


int nresistencias -> Numero de resistencias solicitadas por el quiosquero
int max -> Numero el cual no puede ser igual a la suma de ningun par de resistencias
int total -> Suma del dinero requerido por el quiosquero

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int nresistencias = 0;
    int max = 0;

    cin >> nresistencias;
    cin >> max;

    if (!std::cin)  // fin de la entrada
        return false;

    int total = 0;

    for (int i = 0; i <= (max/2); i++) //Usamos max/2 ya que el valor (max/2)+1 provocaria que si cogemos el valor (max/2)-1 de el valor que no queremos 
        total += i;
    for (int i = max; i < (max + (nresistencias - (max/2))); i++) //En este caso cogemos el resto de resistencias que nos quedan por coger, estas serian las que ya tenemos menos las que faltan, para ello forzamos el numero maximo de resistencia que sabemos que deberemos tener, haciendo el calculo indicado en el for
        total += i;

    cout << total << endl;

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
