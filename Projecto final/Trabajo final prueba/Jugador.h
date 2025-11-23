#pragma once

using namespace System::Drawing;
enum Direcciones { Ninguna, Abajo, Arriba, Izquierda, Derecha };

class Jugador
{
protected:
	int x;
	int y;
	int ancho;
	int alto;
	int indiceX, indiceY;
	Direcciones ultimaTecla;
public:
	int dx;
	int dy;

	Direcciones direccion;
	Jugador(int x, int y);

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp);
	void mover(BufferedGraphics^ buffer, Bitmap^ bmp);
};

