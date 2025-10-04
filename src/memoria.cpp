#include <iostream>
using namespace std;

class Empleado{
private:
    char nombre[10];     // 10B
    int edad;            //  4B
    char direccion[255]; //255B 
    int telefono;        //  4B
public:
    int LeerEdad(){
        return edad;
    }
}; // -> 273B

int main(int argc, char const *argv[])
{
    //Tamaños de memoria estatica
    //Enteros
    cout<<"Tamaño de int " << sizeof(int) << endl;
    cout<<"Tamaño de long " << sizeof(long) << endl;
    // Punto flotante
    cout<<"Tamaño de float " << sizeof(float) << endl;
    cout<<"Tamaño de double " << sizeof(double) << endl;
    //Bytes
    cout<<"Tamaño de char " << sizeof(char) << endl;
    cout<<"Tamaño de byte " << sizeof(byte) << endl;
    cout<<"Tamaño de bool " << sizeof(bool) << endl;

    cout <<"Tamaño puntero " << sizeof(int *) << endl;
    
    //Tamaño tipos no nativos
    Empleado empleados[10]; //<--2730B
    cout<<"Tamaño Empleado " << sizeof(Empleado) <<endl;
    cout<<"Empleados "<< empleados[0].LeerEdad()<<endl;
    
    int a=37; 
    char b= (char)a;
    cout<< b << endl;
    return 0;
    
} 