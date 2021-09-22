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
    string filename = "../imagenes/col.png";
    QImage im(filename.c_str());


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
    int multi=0;
    sum=0;
    int yep=16;
    while(terminar!=16){
    for(int i=0;i<16;i++){
        final=0;
        cont=0;
        for(int t=0;t<im.height()/16;t++){
            cont++;
            cred.push_back(promred[multi*yep]);
            multi++;
            if(cont==im.height()/16 || final>15){
                cont=0;
                final++;
                if (final==16 && im.width()%16!=0){}
                else{
                    for (vector<int>::iterator  it = cred.begin() ; it != cred.end(); ++it){ sum=sum+*it; }//promedio largo
    
                    if (final==17 && im.width()%16!=0){
                        int modu=im.width()%16;
                        int divi=im.width()/16;
                        int tot = divi+modu;
                        sum = sum/tot;
                    }//promedio final
    
                    else{ int dip = im.width()/16; sum = sum/dip;}
    
                    promred2.push_back(sum);
                    cred.clear();
                    sum = 0;

                }

            }
        }
    }
    terminar++;
    }


    /*int i=0;
    int o=0;
    re=16;
    sum=0;
    int a;
    cout << "ver vector" << endl;
    cin>> a;
    for (int b=0;b<16*16;b++,sum=o*re){
        i++;
        o++;
        cout << promred[sum] << " ";
        if(i%16==0){
            i=0;
            re++;
            cout<<endl;
        }

    }*/

    cout << promred2.size() << endl;
    cout << promred.size() << endl;
    return 0;



}
