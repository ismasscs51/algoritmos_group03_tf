#pragma once
#include "Jugador.h"

class Recurso : public Jugador
{
public:
	Recurso(int x, int y, int ancho, int alto);
	void dibujarRecurso(BufferedGraphics^ buffer, Bitmap^ bmp);
};

