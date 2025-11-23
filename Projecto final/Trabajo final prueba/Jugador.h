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
	int velocidad;
	Direcciones ultimaTecla;

public:
	int dx;
	int dy;

	int getX() { return x; }
	int getY() { return y; }

	int getCentroX() { return x + ancho / 2; }
	int getCentroY() { return y + alto / 2; }//IA


	Direcciones direccion;
	Jugador(int x, int y);

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp);
	void mover(BufferedGraphics^ buffer, Bitmap^ bmp);
};

