#include <vector>
#include "Dibujo.hpp"


class GestorDibujos {
public:
    std::vector<Dibujo> dibujos;


    void Agregar(const Dibujo& dibujo) {
        dibujos.push_back(dibujo);
    }


    void DibujarTodos(ftxui::Screen& screen) const {
        for (size_t i = 0; i < dibujos.size(); ++i)
            dibujos[i].Dibujar(screen);
    }


    void Mover(size_t idx, int dx, int dy) {
        if (idx < dibujos.size()) {
            dibujos[idx].x += dx;
            dibujos[idx].y += dy;
        }
    }


    void CambiarPosicion(size_t idx, int x, int y) {
        if (idx < dibujos.size()) {
            dibujos[idx].x = x;
            dibujos[idx].y = y;
        }
    }
};
