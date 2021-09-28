#ifndef IMAGENES_H
#define IMAGENES_H
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <QImage>

using namespace std;

#endif // IMAGENES_H

class imagen {
private:
    string name;
    ofstream outfile;

public:
    imagen(string);
    void reduccionc(QImage,char);
    vector<int> reduccionf(QImage,vector<int>);
    void aumentoc(QImage,char);
    vector<int> aumentof(QImage, vector<int>);
    void igualc(QImage,char);
    int agregar(char,QImage,int,int);
    void escribir(vector<int>);
    vector<int> rotar(vector<int>);
    QImage dar_imagen(void);
    void abrir_archivo();
    void cerrar_archivo();

};
