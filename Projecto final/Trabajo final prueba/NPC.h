#pragma once
using namespace System::Drawing;

class NPC
{
private:
    int x, y;
    int ancho, alto;

public:
    bool activo;     // Si esta en el mapa
    int tipo;        // 1 o 2 (para saber que skin usa si quisieras variar)

    NPC(int px, int py, int w, int h)
    {
        x = px;
        y = py;
        ancho = w;
        alto = h;
        activo = true;
        tipo = 1;
    }

    void dibujar(Graphics^ g, Bitmap^ sprite)
    {
        if (!activo) return;
        Rectangle destino = Rectangle(x, y, ancho, alto);
        // Dibujamos todo el sprite o una porcion si es hoja de sprites
        // Asumiremos que las imagenes son individuales por ahora
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