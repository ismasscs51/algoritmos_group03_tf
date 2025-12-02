#pragma once

using namespace System;
using namespace System::Drawing;

class Aliado
{
private:
    int x, y;
    int ancho, alto;
    bool activo;

public:
    Aliado(int px, int py, int w, int h)
    {
        x = px;
        y = py;
        ancho = w;
        alto = h;
        activo = false;
    }

    void activar()
    {
        activo = true;
    }

    void desactivar()
    {
        activo = false;
    }

    bool estaActivo()
    {
        return activo;
    }

    void setPos(int px, int py)
    {
        x = px;
        y = py;
    }

    void dibujar(Graphics^ g, Bitmap^ sprite)
    {
        if (!activo) return;

        Rectangle destino = Rectangle(x, y, ancho, alto);
        g->DrawImage(sprite, destino);
    }

    Rectangle getHitbox()
    {
        return Rectangle(x, y, ancho, alto);
    }

    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return ancho; }
    int getAlto() { return alto; }
};

