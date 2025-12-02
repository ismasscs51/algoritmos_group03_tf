#pragma once
using namespace System::Drawing;

class Recurso
{
private:
    int x, y;
    int ancho, alto;
    int indiceX, indiceY;

public:
    Recurso(int x, int y, int ancho, int alto);

    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return ancho; }
    int getAlto() { return alto; }

    void setX(int v) { x = v; }
    void setY(int v) { y = v; }

    void dibujar(BufferedGraphics^ buffer, Bitmap^ bmp);
};

