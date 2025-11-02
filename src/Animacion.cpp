#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include "Dibujo.hpp"
#include "GestorDibujos.hpp"

using namespace ftxui;

// Generar tablero
std::vector<std::u32string> GenerarTablero() {
    std::vector<std::u32string> tablero;
    bool blanco = true;
    for (int y = 0; y < 8; ++y) {
        std::u32string fila = U"";
        for (int x = 0; x < 8; ++x) {
            fila += blanco ? U"░░" : U"██";
            blanco = !blanco;
        }
        blanco = !blanco;
        tablero.push_back(fila);
    }
    return tablero;
}

// Obtener posición en base a coordenadas (columna, fila)
auto casilla = [](int col, int fila) {
    return std::pair<int, int>(10 + col * 2, 3 + (7 - fila));
};

int main() {
    auto screen = Screen::Create(Dimension::Fixed(80), Dimension::Fixed(24));
    GestorDibujos gestor;

    // === Tablero ===
    gestor.Agregar(Dibujo(10, 3, GenerarTablero(), Color::GrayLight));

    // === Piezas Unicode ===
    const std::u32string P = U"♙", p = U"♟";
    const std::u32string N = U"♘", n = U"♞";
    const std::u32string B = U"♗", b = U"♝";
    const std::u32string R = U"♖", r = U"♜";
    const std::u32string Q = U"♕", q = U"♛";
    const std::u32string K = U"♔", k = U"♚";

    // === Posiciones iniciales ===
    auto [b2x,b2y] = casilla(1,1);
    auto [b7x,b7y] = casilla(1,6);
    auto [e2x,e2y] = casilla(4,1);
    auto [e7x,e7y] = casilla(4,6);
    auto [g1x,g1y] = casilla(6,0);
    auto [g8x,g8y] = casilla(6,7);
    auto [f1x,f1y] = casilla(5,0);
    auto [c8x,c8y] = casilla(2,7);
    auto [d1x,d1y] = casilla(3,0);
    auto [d8x,d8y] = casilla(3,7);
    auto [a1x,a1y] = casilla(0,0);
    auto [a8x,a8y] = casilla(0,7);

    // === Crear piezas ===
    Dibujo peonB1(b2x,b2y,{P},Color::White);
    Dibujo peonN1(b7x,b7y,{p},Color::RedLight);
    Dibujo peonB2(e2x,e2y,{P},Color::White);
    Dibujo peonN2(e7x,e7y,{p},Color::RedLight);
    Dibujo caballoB(g1x,g1y,{N},Color::White);
    Dibujo caballoN(g8x,g8y,{n},Color::RedLight);
    Dibujo alfilB(f1x,f1y,{B},Color::White);
    Dibujo alfilN(c8x,c8y,{b},Color::RedLight);
    Dibujo reinaB(d1x,d1y,{Q},Color::White);
    Dibujo reinaN(d8x,d8y,{q},Color::RedLight);
    Dibujo torreB(a1x,a1y,{R},Color::White);
    Dibujo torreN(a8x,a8y,{r},Color::RedLight);
    Dibujo reyB(e2x-2,e2y-1,{K},Color::White);
    Dibujo reyN(e7x-2,e7y+1,{k},Color::RedLight);

    gestor.Agregar(peonB1); // 0
    gestor.Agregar(peonN1); // 1
    gestor.Agregar(peonB2); // 2
    gestor.Agregar(peonN2); // 3
    gestor.Agregar(caballoB); // 4
    gestor.Agregar(caballoN); // 5
    gestor.Agregar(alfilB); // 6
    gestor.Agregar(alfilN); // 7
    gestor.Agregar(reinaB); // 8
    gestor.Agregar(reinaN); // 9
    gestor.Agregar(torreB); // 10
    gestor.Agregar(torreN); // 11
    gestor.Agregar(reyB); // 12
    gestor.Agregar(reyN); // 13

    // === Animación por jugadas ===
    int frames = 450;
    for (int f=0; f<frames; ++f) {
        screen.Clear();

        // Peón blanco e2->e4
        if (f<30) gestor.dibujos[2].y = e2y - (f/15);

        // Peón negro e7->e5
        if (f>=30 && f<60) gestor.dibujos[3].y = e7y + ((f-30)/15);

        // Caballo blanco g1->f3
        if (f>=60 && f<90){
            int paso=f-60;
            gestor.dibujos[4].x=g1x - (paso/8);
            gestor.dibujos[4].y=g1y - (paso/15);
        }

        // Caballo negro g8->f6
        if (f>=90 && f<120){
            int paso=f-90;
            gestor.dibujos[5].x=g8x - (paso/8);
            gestor.dibujos[5].y=g8y + (paso/15);
        }

        // Peón blanco b2->b4
        if (f>=120 && f<150) gestor.dibujos[0].y = b2y - ((f-120)/15);

        // Peón negro b7->b5
        if (f>=150 && f<180) gestor.dibujos[1].y = b7y + ((f-150)/15);

        // Alfil blanco f1->b5
        if (f>=180 && f<210){
            int paso=f-180;
            gestor.dibujos[6].x=f1x - (paso/6);
            gestor.dibujos[6].y=f1y - (paso/8);
        }

        // Alfil negro c8->b7
        if (f>=210 && f<240){
            int paso=f-210;
            gestor.dibujos[7].x=c8x - (paso/12);
            gestor.dibujos[7].y=c8y + (paso/12);
        }

        // Reina blanca d1->f3
        if (f>=240 && f<270){
            int paso=f-240;
            gestor.dibujos[8].x=d1x + (paso/8);
            gestor.dibujos[8].y=d1y - (paso/12);
        }

        // Reina negra d8->f6
        if (f>=270 && f<300){
            int paso=f-270;
            gestor.dibujos[9].x=d8x + (paso/8);
            gestor.dibujos[9].y=d8y + (paso/12);
        }

        // Torre blanca a1->a3
        if (f>=300 && f<330) gestor.dibujos[10].y = a1y - ((f-300)/12);

        // Torre negra a8->a6
        if (f>=330 && f<360) gestor.dibujos[11].y = a8y + ((f-330)/12);

        // Rey blanco e1->g1 (enroque)
        if (f>=360 && f<390) gestor.dibujos[12].x = e2x-2 + ((f-360)/12);

        // Rey negro e8->g8 (enroque)
        if (f>=390 && f<420) gestor.dibujos[13].x = e7x-2 + ((f-390)/12);

        // Peón blanco b4->b5
        if (f>=420 && f<450) gestor.dibujos[0].y = b2y - 2 - ((f-420)/15);

        // Dibujar todo
        gestor.DibujarTodos(screen);
        std::cout << screen.ToString();
        std::cout << screen.ResetPosition();
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
    return 0;
}
