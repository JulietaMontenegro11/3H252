#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include "GestorDibujos.hpp"


using namespace ftxui;
using namespace std;


int main() {


    int ancho = 100;
    int alto = 40; // pantalla más larga
    auto screen = Screen::Create(Dimension::Fixed(ancho), Dimension::Fixed(alto));


    GestorDibujos gestor;


    // ===== SOL =====
    const vector<u32string> sol = {
        U"           |   . ",
        U"           |   . ",
        U"    `.  *  |     .' ",
        U"      `. ._|_* .'  . ",
        U"   . * .'     `.  * ",
        U" ------|       |------- ",
        U"   .  *`._____.' *  . ",
        U"       .'  |* `.  * ",
        U"     .' *  |  . `. ",
        U"         . | .",
        U"         . | .",
    };
    int sol_x = 40;
    int sol_y = 17;
    gestor.Agregar(Dibujo(sol_x, sol_y, sol, Color::Orange4));
    int sol_centro_x = sol_x + sol[0].size() / 2;
    int sol_centro_y = sol_y + sol.size() / 2;


    // ===== PLANETAS =====
    const std::vector<std::u32string> planeta_rojo = {
        U"   ░████░   ",
        U"  ████████  ",
        U"  ███▓▓███  ",
        U"   ░████░   "
    };
    const std::vector<std::u32string> planeta_azul = {
        U"  ░██░  ",
        U" ██████ ",
        U"  ░██░  "
    };
    const std::vector<std::u32string> luna = {
        U"   .-.   ",
        U"  (◉◉)  ",
        U"   `-’   "
    };


    // ===== RADIOS MÁS GRANDES =====
    double radio_planeta_rojo_x = 30.0;
    double radio_planeta_rojo_y = 13.0;


    double radio_planeta_azul_x = 20.0;
    double radio_planeta_azul_y = 9.0;


    double radio_luna_x = 10.0;
    double radio_luna_y = 3.0;


    double angulo_planeta_rojo = 0.0;
    double angulo_planeta_azul = 0.0;
    double angulo_luna = 0.0;


    // Inicializar posiciones correctas
    double px_rojo = sol_centro_x + radio_planeta_rojo_x * cos(angulo_planeta_rojo);
    double py_rojo = sol_centro_y + radio_planeta_rojo_y * sin(angulo_planeta_rojo);


    double px_azul = sol_centro_x + radio_planeta_azul_x * cos(-angulo_planeta_azul);
    double py_azul = sol_centro_y + radio_planeta_azul_y * sin(-angulo_planeta_azul);


    double px_luna = px_rojo + radio_luna_x * cos(angulo_luna);
    double py_luna = py_rojo + radio_luna_y * sin(angulo_luna);


    Dibujo planetaR((int)px_rojo, (int)py_rojo, planeta_rojo, Color::Red);
    Dibujo planetaAzul((int)px_azul, (int)py_azul, planeta_azul, Color::SkyBlue3);
    Dibujo lunaObj((int)px_luna, (int)py_luna, luna, Color::GrayLight);


    gestor.Agregar(planetaR);    // índice 1
    gestor.Agregar(planetaAzul); // índice 2
    gestor.Agregar(lunaObj);     // índice 3


    // ===== ESTRELLAS =====
    std::vector<std::pair<int, int>> estrellas;
    srand(time(NULL));
    for (int i = 0; i < 150; ++i) { // más estrellas
        int x = rand() % ancho;
        int y = rand() % alto;
        estrellas.push_back({x, y});
    }
    std::vector<std::u32string> formas = {U"*", U"+", U"**", U"°", U"¨", U"*.", U"+:", U":*"};
    std::vector<Color> colores = {Color::Orange3, Color::Yellow2, Color::Yellow3, Color::White};


    // ===== BUCLE DE ANIMACIÓN =====
    for (int frame = 0; frame < 1000; ++frame) {
        screen.Clear();


        // Dibujar estrellas aleatorias
        for (auto& e : estrellas) {
            std::u32string forma = formas[rand() % formas.size()];
            Color color = colores[rand() % colores.size()];
            screen.PixelAt(e.first, e.second).character = forma[0];
            screen.PixelAt(e.first, e.second).foreground_color = color;
        }


        // Actualizar posiciones de los planetas y la luna
        px_rojo = sol_centro_x + radio_planeta_rojo_x * cos(angulo_planeta_rojo);
        py_rojo = sol_centro_y + radio_planeta_rojo_y * sin(angulo_planeta_rojo);


        px_azul = sol_centro_x + radio_planeta_azul_x * cos(-angulo_planeta_azul);
        py_azul = sol_centro_y + radio_planeta_azul_y * sin(-angulo_planeta_azul);


        px_luna = px_rojo + radio_luna_x * cos(angulo_luna);
        py_luna = py_rojo + radio_luna_y * sin(angulo_luna);


        gestor.dibujos[1].x = (int)px_rojo;
        gestor.dibujos[1].y = (int)py_rojo;


        gestor.dibujos[2].x = (int)px_azul;
        gestor.dibujos[2].y = (int)py_azul;


        gestor.dibujos[3].x = (int)px_luna;
        gestor.dibujos[3].y = (int)py_luna;


        gestor.DibujarTodos(screen);


        cout << screen.ToString();
        cout << screen.ResetPosition();
        cout << flush;


        this_thread::sleep_for(chrono::milliseconds(100));


        // Incrementar ángulos
        angulo_planeta_rojo += 0.06; // un poco más lento por la órbita grande
        angulo_planeta_azul += 0.1;
        angulo_luna += 0.25;
    }


    return 0;
}
