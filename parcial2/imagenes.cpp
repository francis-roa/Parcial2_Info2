#include "imagenes.h"
imagen::imagen (string g){

    name=g;

};

void imagen::reduccionc(QImage im,char color){
    int cont, final = 0, sum = 0;
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

    cred.clear();
    if(im.height()<16)
    {
        promred2=aumentof(im,promred);
    }
    else if(im.height()>16){
        promred2=reduccionf(im,promred);
        promred.clear();
        //se rota la información en sentido horario
        promred2=rotar(promred2);
    }
    escribir(promred2,color);
    cout << promred2.size() << endl;
    cout << endl;
}

vector<int> imagen::reduccionf(QImage im, vector<int> promred)
{
    int terminar=1,final=0,ko=0,b = 0, baux=0,sum=0,yep=0,altoprom = im.height()/16;
    vector<int> promred2;

    //se obtienen las nuevas columnas
    //se rota la información en sentido antihorario
    while(terminar!=17){

        while(final!=16){

            while(baux!=altoprom)
            {
                sum= sum + promred[b*16+yep];
                b++;
                baux++;
                if(ko==1 && baux==im.height()%16){break;}
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
    return promred2;
}

void imagen::aumentoc(QImage im, char color){
    int x1=im.width(),x2=16;
    vector <int> mod_data;
    for(int y=0;y<im.height();y++)
    {
        for(int x=0;x<x1;x++)
        {
            mod_data.push_back(agregar(color, im, x, y));
            if(x1<=x+(x2-x1) && (x+x2-x1)<=x2)
            {
                for(int clon=1;clon<x2/x1;clon++)
                {
                    mod_data.push_back(agregar(color, im, x, y));
                }
            }
            if(x+1==x1 && mod_data.size()%16!=0)
            {
                x=x-(x2-x1*2)+1;
            }
        }
    }
    if(im.height()<16)
    {
        mod_data=aumentof(im,mod_data);
    }
    else if(im.height()>16)
    {
        mod_data=reduccionf(im,mod_data);
        mod_data=rotar(mod_data);
    }
    escribir(mod_data,color);
    cout<<endl;
    cout<<mod_data.size()<<endl;
}

vector<int> imagen::aumentof(QImage im, vector<int> nuev_image)
{
    int y1=im.height(), y2=16,y=0,x=0,itera=16,aumento=0;
    int iaux=0, copy;
    vector<int>::iterator it;
    vector<int> nuev;
    nuev.reserve(256);
    for(vector<int>::iterator i=nuev_image.begin(); i!=nuev_image.end();i++,iaux++)
    {
        copy=nuev_image[iaux];
        nuev.push_back(copy);
    }
    it=nuev.begin();
    while(y < y2-y1)
    {
        if(y1<=y+(y2-y1) && (y+y2-y1)<=y2)
        {
            for(int clon=1;clon<y2/y1;clon++)
            {
                while(x<16)
                {
                    //nuev_image.insert(it+itera,nuev_image[1*x+aumento]);
                    //nuev[itera]=nuev_image[1*x+aumento];
                    nuev.insert(it+itera,nuev[x+aumento]);
                    x=x+1;
                    itera=itera+1;
                    it=nuev.begin();
                }
            }
        }

        x=0;
        if(y+1==y1 && nuev.size()/16<16)
        {
            y=y-(y2-y1*2)+1;
            itera=16*y;
        }
        else{
            y=y+1;
            aumento=aumento+32;
            itera=itera+16;
        }
    }
    return nuev;
}

//devuelve el valor R, G o B del pixel con coordenadas (x,y)
int imagen::agregar(char col,QImage im,int x,int y){
    int dato=0;
    if(col=='r'){dato=im.pixelColor(x,y).red();}
    else if(col=='g'){dato=im.pixelColor(x,y).green();}
    else if(col=='b'){dato=im.pixelColor(x,y).blue();}
    return dato;
}

//se escriben los datos en un archivo de texto y se muestran en consola
void imagen::escribir(vector<int> datos, char color)
{
    for(int i=0; i<16*16;i++)
    {
        //escribir formato
        if(i==0){
            if(color=='r'){
                cout <<"byte r[]={"<<datos[i] << ", ";//inicio del formato
                outfile<<"byte r[]={"<<datos[i] << ", ";
            }
            else if(color=='g'){
                cout <<"byte g[]={"<<datos[i] << ", ";//inicio del formato
                outfile<<"byte g[]{"<<datos[i] << ", ";
            }
            else if(color=='b'){
                cout <<"byte b[]={"<<datos[i] << ", ";//inicio del formato
                outfile<<"byte b[]={"<<datos[i] << ", ";
            }
        }
        else if(i==16*16-1){
            cout << datos[i] << "}";//fin del formato
            outfile << datos[i] << "}\n";
        }
        else if(i%16==0 && i!=0){
            cout<<endl<<datos[i]<<", ";//cambio de fila en el formato
            outfile << "\n"<<datos[i]<<", ";
        }
        else{
            cout << datos[i] << ", ";//resto del formato
            outfile <<datos[i] << ", ";
        }
    }
    outfile<<"\n";
}

void imagen::igualc(QImage im,char color)
{
    vector<int> data,data2;
    for(int y=0;y<im.height();y++)
    {
        for(int x=0;x<im.width();x++)
        {
            data.push_back(agregar(color,im,x,y));
        }
    }
    if(im.height()<16)
    {
        data=aumentof(im,data);

    }
    else if(im.height()>16)
    {
        data=reduccionf(im,data);
        data=rotar(data);
    }
    escribir(data,color);
    cout<<endl;
}

vector<int> imagen::rotar(vector<int> mod_data)
{
    int sum=0,o=0,oaux=0,i=0;
    vector<int> mod_data2;
    for (int b=0;b<16*16;b++,sum=o*16+oaux){
        i++;
        o++;
        if(i%16==0){
            i=0;
            oaux++;
            o=0;
        }
        mod_data2.push_back(mod_data[sum]);
    }
    return mod_data2;
}

QImage imagen::dar_imagen(void){

    QImage im(name.c_str());

return im;
}

void imagen::abrir_archivo(){

    outfile.open("../datos.txt");

};

void imagen::cerrar_archivo(){

    outfile.close();

};
