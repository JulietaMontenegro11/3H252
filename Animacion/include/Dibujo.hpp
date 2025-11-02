#include <vector>
#include <string>
#include <ftxui/screen/screen.hpp>


class Dibujo {
public:
    int x, y; // posición
    std::vector<std::u32string> figura;
    ftxui::Color color;


    Dibujo() : x(0), y(0), color(ftxui::Color::White) {}


    Dibujo(int x, int y, const std::vector<std::u32string>& figura, ftxui::Color color = ftxui::Color::White)
        : x(x), y(y), figura(figura), color(color) {}


    void Dibujar(ftxui::Screen& screen) const {
        for (size_t i = 0; i < figura.size(); ++i) {
            for (size_t j = 0; j < figura[i].size(); ++j) {
                if (figura[i][j] != U' ') {
                    int px = x + (int)j;
                    int py = y + (int)i;
                    if (px >= 0 && px < screen.dimx() && py >= 0 && py < screen.dimy()) {
                        auto& pixel = screen.PixelAt(px, py);
                        pixel.character = figura[i][j];
                        pixel.foreground_color = color;
                        pixel.bold = true;
                    }
                }
            }
        }
    }
};
