#pragma once
#include "Jugador.h"

class Enemigo : public Jugador
{
public:
	Enemigo(int x, int y, int ancho, int alto,int velocidad);

	int vida;
	int vivo;

	void moverHaciaJugador(Jugador* objetivo);
	void resetVida()
	{
		vida = 3;    
	}

	void setVelocidad(int v)
	{
		velocidad = v;
	}
	
};

