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
void Enemigo::moverHaciaJugador(Jugador* objetivo)
{
    float dx = objetivo->getCentroX() - getCentroX();
    float dy = objetivo->getCentroY() - getCentroY();

    float distancia = sqrt(dx * dx + dy * dy);

    if (distancia < 1) return; // evita division por cero

    float nx = dx / distancia; // normalizar vector
    float ny = dy / distancia;

    // mover enemigo de forma suave hacia el jugador
    x += nx * velocidad;
    y += ny * velocidad;

    // actualizar direccion (para animaciones)
    if (fabs(dx) > fabs(dy))
    {
        direccion = (dx > 0) ? Direcciones::Derecha : Direcciones::Izquierda;
    }
    else
    {
        direccion = (dy > 0) ? Direcciones::Abajo : Direcciones::Arriba;
    }
}
