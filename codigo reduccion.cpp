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
    vector <int> red;
    vector <int> promred;
    string filename = "../imagenes/col.png";
    QImage im(filename.c_str());


    for(int y=0;y<im.height();y++){
        cont = 0;
        final = 0;
        for(int x=0;x<im.width();x++){
            cont++;
            red.push_back(im.pixelColor(x,y).red());
            if(cont==im.width()/16 || x==im.width()-1) {
                cont = 0;
                final ++;
                if (final==16 && im.width()%16!=0){break;}
                for (vector<int>::iterator  it = red.begin() ; it != red.end(); ++it){sum = sum + *it;}//se saca el promedio
                if (final==17 && im.width()%16!=0){break;sum = sum/(16+(im.width()%16));}
                else{sum = sum/16;}
                promred.push_back(sum);
                red.clear();

            }

        }
    }
    int i=0;
    int a;
    cout << "ver vector" << endl;
    cin>> a;
    for (vector<int>::iterator  it = promred.begin() ; it != promred.end(); ++it){
        i++;
        cout << *it << " ";
        if(i%16==0){cout<<endl;}

    }




    //for(unsigned int i=0;i<promred.size();i++){




    //}



    return 0;



}
