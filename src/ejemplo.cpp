#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
#include <ftxui/screen/screen.hpp>
using namespace ftxui;

int main (int argc, char const *argv[])
{
    Screen pantalla = Screen::Create(
        Dimension::Full(),
        Dimension::Fixed(10)
    );

    int x=0;
    int y=0;
    while(true)
    {
        Pixel& pixel= pantalla.PixelAt(x,y);
    pixel.foreground_color = Color::Red;
    pixel.background_color = Color::Green;
    pixel.character = 'X';

    pantalla.Print();
    this_thread::sleep_for(chrono::milliseconds(50));
    pantalla.Clear();
    cout<<pantalla.ResetPosition();
    x++;
    }
    
    return 0;
}

