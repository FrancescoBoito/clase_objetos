/*
 * Informatica II - Desarrollo y utilizacion de una clase en C++.
 * Tema: mediciones ambientales de El Sereno.
 *
 * Incluye atributos, metodos, constructores, objetos y herencia.
 * Los valores son simulados: no hace falta conectar un sensor.
 * Para compilar: g++ -std=c++11 -Wall -Wextra -pedantic el_sereno.cpp -o el_sereno
 * Para ejecutar en Linux: ./el_sereno
 * Se omiten tildes en comentarios para facilitar su lectura en cualquier editor.
 */

// iostream permite escribir en la consola mediante std::cout.
#include <iostream>

// Una clase define los datos y las operaciones de un tipo de objeto.
class Medicion {
private:
    // Cada objeto tiene su propia temperatura y humedad.
    // private impide modificarlas directamente desde main o desde la clase hija.
    float temperatura; // Temperatura en grados Celsius.
    float humedad;     // Humedad relativa en porcentaje.

public:
    // public permite utilizar estos miembros desde fuera de la clase.
    // El constructor se llama igual que la clase y no tiene tipo de retorno.
    // Se ejecuta automaticamente cuando creamos un objeto.
    // Los parametros reciben los valores iniciales por valor (se copian).
    Medicion(float temperaturaInicial, float humedadInicial)
        : temperatura(temperaturaInicial), humedad(humedadInicial) {
        // La lista despues de ':' inicializa los atributos antes de entrar aqui.
        // El cuerpo queda vacio porque ya se inicializaron ambos atributos.
    }

    // void indica que el metodo realiza una accion sin devolver un resultado.
    // Actualiza los atributos del objeto sobre el que se llama.
    // Suponemos datos validos del sensor: humedad entre 0 y 100 %.
    void actualizar(float nuevaTemperatura, float nuevaHumedad) {
        temperatura = nuevaTemperatura;
        humedad = nuevaHumedad;
    }

    // const al final indica que el metodo no modifica el estado del objeto.
    void mostrar() const {
        // << envia cada texto o valor a la salida de consola.
        // \n produce un salto de linea.
        std::cout << "Temperatura: " << temperatura << " C\n";
        std::cout << "Humedad: " << humedad << " %\n";
    }
}; // La definicion de una clase termina con punto y coma.

// MedicionNodo hereda publicamente de Medicion.
// Una MedicionNodo es una Medicion que tambien identifica el nodo de origen.
// Conserva el acceso publico a actualizar() y mostrar().
class MedicionNodo : public Medicion {
private:
    int identificador; // Numero del nodo que produjo esta medicion.

public:
    // Este constructor recibe los datos de la base y el identificador adicional.
    MedicionNodo(int id, float temperaturaInicial, float humedadInicial)
        : Medicion(temperaturaInicial, humedadInicial), identificador(id) {
        // Primero se construye la parte Medicion mediante su constructor.
        // Luego se inicializa el atributo propio identificador.
        // Los constructores no se heredan automaticamente con esta declaracion.
    }

    // Este metodo propio muestra el identificador y reutiliza el metodo base.
    void mostrarNodo() const {
        std::cout << "Nodo: " << identificador << '\n';
        // :: indica que mostrar pertenece a la clase base Medicion.
        // Evitamos repetir las instrucciones que imprimen temperatura y humedad.
        Medicion::mostrar();
    }
};

// main es el punto donde comienza la ejecucion del programa.
int main() {
    // Creamos un objeto de la clase base y llamamos a su constructor.
    // La f indica que el literal es float, como los parametros del constructor.
    Medicion ambiente(18.5f, 55.0f);

    std::cout << "=== MEDICION GENERAL ===\n";
    // El punto permite llamar a un metodo del objeto ambiente.
    ambiente.mostrar();

    // Creamos un objeto de la clase derivada con su identificador y medicion.
    MedicionNodo nodo1(1, 6.5f, 70.0f);
    // Otro objeto tiene sus propios datos independientes.
    MedicionNodo nodo2(2, 9.0f, 62.0f);

    std::cout << "\n=== NODO 1: DATOS INICIALES ===\n";
    nodo1.mostrarNodo();

    // actualizar() se definio en Medicion y esta disponible por la herencia.
    // Solo cambia nodo1. ambiente y nodo2 conservan sus valores.
    nodo1.actualizar(3.0f, 80.0f);
    std::cout << "\n=== NODO 1: DATOS ACTUALIZADOS ===\n";
    nodo1.mostrarNodo();

    std::cout << "\n=== NODO 2: DATOS INDEPENDIENTES ===\n";
    nodo2.mostrarNodo();

    // Cero indica al sistema operativo que el programa termino correctamente.
    // Los objetos locales se destruyen automaticamente al salir de main.
    return 0;
}
