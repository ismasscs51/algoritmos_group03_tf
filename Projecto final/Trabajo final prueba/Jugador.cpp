#include "Jugador.h"

Jugador::Jugador(int x, int y) {
	this->x = x;
	this->y = y;
	dx = 0;
	dy = 0;
	ultimaTecla = Direcciones::Abajo;
	direccion = Direcciones::Ninguna;

	ancho = 128;
	alto = 128;

	indiceX = 0;
	indiceY = 0;

	velocidad = 10;

	atacando = false;
	indiceAtaque = 0;
	maxFramesAtaque = 6;
}


void Jugador::dibujar(BufferedGraphics^ buffer, Bitmap^ bmp) {
	Rectangle porcionAusar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
	Rectangle aumentoPersonaje = Rectangle(x, y, ancho * 1, alto * 1);
	buffer->Graphics->DrawImage(bmp, aumentoPersonaje, porcionAusar, GraphicsUnit::Pixel);
	x += dx;
	y += dy;

}
void Jugador::mover(BufferedGraphics^ buffer, Bitmap^ bmpCaminar, Bitmap^ bmpAtacar) {

	if (atacando) {

		switch (ultimaTecla)
		{
		case Direcciones::Arriba:    indiceY = 0; break;
		case Direcciones::Izquierda: indiceY = 1; break;
		case Direcciones::Abajo:     indiceY = 2; break;
		case Direcciones::Derecha:   indiceY = 3; break;
		}

		indiceX = indiceAtaque;

		Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle destino = Rectangle(x, y, ancho, alto);
		buffer->Graphics->DrawImage(bmpAtacar, destino, porcion, GraphicsUnit::Pixel);

		indiceAtaque++;

		if (indiceAtaque >= maxFramesAtaque) {
			atacando = false;
			indiceAtaque = 0;
		}

		return; // mientras ataca, no caminamos
	}

	switch (direccion)
	{
	case Direcciones::Arriba:
		indiceY = 0;
		if (indiceX >= 0 && indiceX < 8)
			indiceX++;
		else
			indiceX = 0;
		dy = -velocidad;
		dx = 0;
		ultimaTecla = Arriba;
		break;

	case Direcciones::Abajo:
		indiceY = 2;
		if (indiceX >= 0 && indiceX < 8)
			indiceX++;
		else
			indiceX = 0;
		dy = velocidad;
		dx = 0;
		ultimaTecla = Abajo;
		break;

	case Direcciones::Izquierda:
		indiceY = 1;
		if (indiceX >= 0 && indiceX < 8)
			indiceX++;
		else
			indiceX = 0;
		dy = 0;
		dx = -velocidad;
		ultimaTecla = Izquierda;
		break;

	case Direcciones::Derecha:
		indiceY = 3;
		if (indiceX >= 0 && indiceX < 8)
			indiceX++;
		else
			indiceX = 0;
		dy = 0;
		dx = velocidad;
		ultimaTecla = Derecha;
		break;
	case Direcciones::Ninguna:
		dx = 0;
		dy = 0;
		switch (ultimaTecla) {
		case Direcciones::Abajo:
			indiceY = 2;
			indiceX = 0;
			break;
		case Direcciones::Izquierda:
			indiceY = 1;
			indiceX = 0;
			break;
		case Direcciones::Arriba:
			indiceY = 0;
			indiceX = 0;
			break;
		case Direcciones::Derecha:
			indiceY = 3;
			indiceX = 0;
			break;
		}

		break;
	}

	dibujar(buffer, bmpCaminar);

}