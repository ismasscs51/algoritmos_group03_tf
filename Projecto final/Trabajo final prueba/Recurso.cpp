#include "Recurso.h"

Recurso::Recurso(int x, int y, int alto, int ancho) 
	: Jugador(x, y) 
{
	this->ancho = ancho;
	this->alto = alto;

	indiceX = 0;
	indiceY = 0;

	dx = 0;
	dy = 0;
	
}

void Recurso::dibujarRecurso(BufferedGraphics^ buffer, Bitmap^ bmp)
{
	Rectangle porcion = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
	Rectangle destino = Rectangle(x, y, ancho, alto);

	buffer->Graphics->DrawImage(bmp, destino, porcion, GraphicsUnit::Pixel);


}

