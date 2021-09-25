#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <QImage>

using namespace std;

void reduccion(QImage,char);
void aumentoc(QImage);
vector<int> aumentof(QImage, vector<int>);
int agregar(char,QImage,int,int);
ofstream outfile;

int main()
{
    int redu=0;
    string name = "../pruebas_parcial2/imagenes/ocho_ocho.jpg";
    QImage im(name.c_str());
    cin>>redu;
    char r='r',g='g',b='b';
    outfile.open("../pruebas_parcial2/datos.txt");
    if(redu==2){
        reduccion(im,r);
        reduccion(im,g);
        reduccion(im,b);
    }
    else{
        aumentoc(im);
    }
    outfile.close();
    return 0;
}

void reduccion(QImage im,char color){
    int cont, final = 0, sum = 0, altoprom = im.height()/16;;
    vector <int> cred;
    vector <int> promred;
    vector <int> promred2;

    //se obtienen las nuevas filas
    for(int y=0;y<im.height();y++){
        cont = 0;
        final = 0;
        for(int x=0;x<im.width();x++){
            cont++;
            cred.push_back(agregar(color,im,x,y));
            //cred.push_back(im.pixelColor(x,y).red());
            if(cont==im.width()/16 || x==im.width()-1) {
                cont = 0;
                final ++;
                if (final==16 && im.width()%16!=0){}
                else{for (vector<int>::iterator  it = cred.begin() ; it != cred.end(); ++it){sum = sum + *it;}//se saca el promedio

                if (final==17 && im.width()%16!=0){
                    int modu=im.width()%16;
                    int divi=im.width()/16;
                    int tot = divi+modu;
                    sum = sum/tot;
                }//promedio final

                else{int dip = im.width()/16;sum = sum/dip;}
                promred.push_back(sum);
                cred.clear();
                sum = 0;
                }
            }
        }
    }

    //imprimir en consola las filas promediadas
    int i=0;
    cred.clear();
    int terminar=1;
    final=0;
    int ko=0;
    int b = 0, baux=0;
    sum=0;
    int yep=0;

    //se obtienen las nuevas columnas
    //se rota la información hacia la izquierda
    while(terminar!=17){

        while(final!=16){

            while(baux!=altoprom)
            {
                sum= sum + promred[b*16+yep];
                b++;
                baux++;
                if(ko==1 && b==im.height()%16){break;}
            }
            if(final==15 && im.height()%16!=0 && ko!=1){ko=1;}
            else{final++;
                if(ko!=1){sum = sum/altoprom;}
                else{int y=altoprom+(im.height()%16);sum = sum/y;}
                promred2.push_back(sum);
                sum=0;
            }
            baux=0;
        }
        final=0;
        yep++;
        terminar++;
        b=0;
        ko=0;
    }
    i=0;
    int o=0,oaux=0;
    sum=0;


    //escribir el formato en un archivo de texto
    //se "rota" la información
    for (int b=0;b<16*16;b++,sum=o*16+oaux){
        i++;
        o++;
        //escribir formato
        if(b==0){
            cout <<"{"<<promred2[sum] << ",";//inicio del formato
            outfile<<"{"<<promred2[sum] << ",";
        }
        else if(b==16*16-1){
            cout << promred2[sum] << "}";//fin del formato
            outfile << promred2[sum] << "}";
        }
        else{
            cout << promred2[sum] << " ,";//resto del formato
            outfile <<promred2[sum] << ",";
        }
        if(i%16==0){
            i=0;
            oaux++;
            o=0;
            cout<<endl;
            outfile << "\n";
        }
    }
    cout << promred2.size() << endl;
    cout << promred.size() << endl;
}

void aumentoc(QImage im){
    int x1=im.width(),x2=16;
    vector <int> mod_data;
    for(int y=0;y<im.height();y++)
    {
        for(int x=0;x<x1;x++)
        {
            mod_data.push_back(im.pixelColor(x,y).red());
            if(x1<=x+(x2-x1) && (x+x2-x1)<=x2)
            {
                for(int clon=1;clon<x2/x1;clon++)
                {
                    mod_data.push_back(im.pixelColor(x,y).red());
                }
            }
        }
    }
    mod_data=aumentof(im,mod_data);
    for(unsigned long long i=0;i<mod_data.size();i++)
    {
        if(i%16==0 && i!=0)
        {
            cout<<endl<<mod_data[i]<<", ";
        }
        else
        {
            cout<<mod_data[i]<<", ";
        }
    }
    cout<<endl;
    cout<<mod_data.size();
}

vector<int> aumentof(QImage im, vector<int> nuev_image)
{
    int y1=im.height(), y2=16,y=0,x=0,itera=16,aumento=0;
    vector<int>::iterator it=nuev_image.begin();
    while(y < y2-y1)
    {
        if(y1<=y+(y2-y1) && (y+y2-y1)<=y2)
        {
            for(int clon=1;clon<y2/y1;clon++)
            {
                while(x<16)
                {
                    nuev_image.insert(it+itera,nuev_image[1*x+aumento]);
                    x=x+1;
                    itera=itera+1;
                    it=nuev_image.begin();
                }
            }
        }
        itera=itera+16;
        x=0;
        y=y+1;
        aumento=aumento+32;
    }
    return nuev_image;
}

int agregar(char col,QImage im,int x,int y){
    int dato=0;
    if(col=='r'){dato=im.pixelColor(x,y).red();}
    else if(col=='g'){dato=im.pixelColor(x,y).green();}
    else if(col=='b'){dato=im.pixelColor(x,y).blue();}
    return dato;
}
