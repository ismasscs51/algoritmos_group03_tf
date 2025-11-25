#include "Enemigo.h"
#include <cmath>

Enemigo::Enemigo(int x, int y, int ancho, int alto,int velocidad)
    : Jugador(x, y) {

    this->ancho = ancho;
    this->alto = alto;

    this->velocidad = velocidad;

    indiceX = 0;
    indiceY = 0;

    dx = 0;
    dy = 0;

    vida = 3;
    vivo = true;
}

//Cambie esto con IA el abs Sirve para convertir un número negativo en positivo.
//Lo uso para saber qué tan lejos está el enemigo del jugador
void Enemigo::perseguir(Jugador* objetivo)
{
    int dx_obj = objetivo->getCentroX() - getCentroX();
    int dy_obj = objetivo->getCentroY() - getCentroY();
    if (dx_obj > 0) {
        direccion = Direcciones::Derecha;
    }
    else if (dx_obj < 0) {
        direccion = Direcciones::Izquierda;
    }
    if (dy_obj > 0) {
        direccion = Direcciones::Abajo;
    }
    else if (dy_obj < 0) {
        direccion = Direcciones::Arriba;
    }

    // Para no temblar cuando está encima
    if (abs(dx_obj) < 5 && abs(dy_obj) < 5) {
        direccion = Direcciones::Ninguna;
    }
}
