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

	int vivo;
	int vida;
	bool invulnerable;
	int tiempoInvulnerable;

	bool atacando;       
	int indiceAtaque;    
	int maxFramesAtaque; 

	int dx;
	int dy;

	int getX() { return x; }
	int getY() { return y; }

	void setX(int nx) { x = nx; }
	void setY(int ny) { y = ny; }

	int getCentroX() { return x + ancho / 2; }
	int getCentroY() { return y + alto / 2; }//IA

	bool yaGolpeoEnEsteAtaque;

	Direcciones direccion;

	Jugador(int x, int y);

	Rectangle getHitboxAtaque();
	void setVelocidad(int v) {
		velocidad = v;
	}

	int getVelocidad() { return velocidad; }

	int getAncho() { return ancho; }
	int getAlto() { return alto; }

	Rectangle getHitboxJugador()
	{
		int hitW = ancho * 0.40;   // ancho del 40% del sprite
		int hitH = alto * 0.60;    // alto del 60% del sprite

		int offsetX = (ancho - hitW) / 2;  // centrar hitbox en el sprite
		int offsetY = alto * 0.35;         // mover hitbox abajo (cerca de los pies)

		return Rectangle(x + offsetX, y + offsetY, hitW, hitH);
	}

	void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp);
	void mover(BufferedGraphics^ buffer, Bitmap^ bmpCaminar, Bitmap^ bmpAtacar);

};

