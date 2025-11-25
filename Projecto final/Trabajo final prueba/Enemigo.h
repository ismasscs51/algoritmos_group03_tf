#pragma once
#include "Jugador.h"

class Enemigo : public Jugador
{
public:
	Enemigo(int x, int y, int ancho, int alto,int velocidad);

	int vida;
	int vivo;

	void perseguir(Jugador* objetivo);
	
};

