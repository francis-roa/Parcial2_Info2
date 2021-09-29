#include "imagenes.h"

using namespace std;


int main()
{
    string a;
    cout<< "escriba la direccion de la imagen" << endl;
    cin>> a;
    imagen pic(a);
    QImage im;
    im=pic.dar_imagen();

    char r='r',g='g',b='b';

    pic.abrir_archivo();

    if(im.width()>16){
        pic.reduccionc(im,r);
        pic.reduccionc(im,g);
        pic.reduccionc(im,b);
    }
    else if(im.width()<16){
        pic.aumentoc(im,r);
        pic.aumentoc(im,g);
        pic.aumentoc(im,b);
    }
    else{
        pic.igualc(im,r);
        pic.igualc(im,g);
        pic.igualc(im,b);
    }
    pic.cerrar_archivo();
    return 0;
}

