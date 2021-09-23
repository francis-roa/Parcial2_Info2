#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <QImage>

using namespace std;


int main(){
    int cont;
    int final = 0;
    int sum = 0;
    vector <int> cred;
    vector <int> promred;
    vector <int> promred2;
    string name = "../pruebas_parcial2/imagenes/col.png";
    QImage im(name.c_str());
    int altoprom = im.height()/16;


    for(int y=0;y<im.height();y++){
        cont = 0;
        final = 0;
        for(int x=0;x<im.width();x++){
            cont++;
            cred.push_back(im.pixelColor(x,y).red());
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
    /*int i=0;
    int a;
    cout << "ver vector" << endl;
    cin>> a;
    for (vector<int>::iterator  it = promred.begin() ; it != promred.end(); ++it){
        i++;
        cout << *it << " ";
        if(i%16==0){cout<<endl;}

    }*/

    cred.clear();
    int terminar=1;
    final=0;
    int ko=0;
    int b = 0, baux=0;
    sum=0;
    int yep=0;
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
    }

    /*int i=0;
    int o=0,oaux=0;
    sum=0;
    int a;
    cout << "ver vector" << endl;
    cin>> a;
    for (int b=0;b<16*16;b++,sum=o*16+oaux){
        i++;
        o++;
        cout << promred2[sum] << " ";
        if(i%16==0){
            i=0;
            oaux++;
            o=0;
            cout<<endl;
        }

    }*/
    for(unsigned long long i=0;i<promred2.size();i++){
        cout<<promred2[i]<<" ";
        if(i%16==0){
            cout<<endl;
        }
    }
    cout << promred2.size() << endl;
    cout << promred.size() << endl;
    return 0;

}
