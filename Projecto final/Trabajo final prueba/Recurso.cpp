#include "Recurso.h"

Recurso::Recurso(int x, int y, int ancho, int alto)
{
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;

    indiceX = 0;
    indiceY = 0;
}

void Recurso::dibujar(BufferedGraphics^ buffer, Bitmap^ bmp)
{
    Rectangle porcion(indiceX * ancho, indiceY * alto, ancho, alto);
    Rectangle destino(x, y, ancho, alto);

    buffer->Graphics->DrawImage(bmp, destino, porcion, GraphicsUnit::Pixel);
}
