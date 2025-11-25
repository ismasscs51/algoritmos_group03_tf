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

	bool atacando;       
	int indiceAtaque;    
	int maxFramesAtaque; 

	int dx;
	int dy;

	int getX() { return x; }
	int getY() { return y; }

	int getCentroX() { return x + ancho / 2; }
	int getCentroY() { return y + alto / 2; }//IA

	bool yaGolpeoEnEsteAtaque;

	Direcciones direccion;

	Jugador(int x, int y);

	Rectangle getHitboxAtaque();

	int getAncho() { return ancho; }
	int getAlto() { return alto; }

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp);
	void mover(BufferedGraphics^ buffer, Bitmap^ bmpCaminar, Bitmap^ bmpAtacar);

};

