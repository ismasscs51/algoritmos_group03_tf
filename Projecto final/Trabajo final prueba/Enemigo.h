#pragma once
#include "Jugador.h"

class Enemigo : public Jugador
{
public:
	Enemigo(int x, int y, int ancho, int alto,int velocidad);
	void perseguir(Jugador* objetivo);
	
};

