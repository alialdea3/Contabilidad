//Bibliografia: (seguro que se me olvidan muchos)
//
//  Libreria estática: (Muchas prueba y error)
//      https://www.youtube.com/watch?v=nqS5WNZZnzU
//      https://docs.microsoft.com/es-es/cpp/build/walkthrough-creating-and-using-a-static-library-cpp?view=msvc-170
//  Formatos cout con float, tabulador y negrita:
//      https://qastack.mx/programming/5907031/printing-the-correct-number-of-decimal-points-with-cout
//      https://aprende.olimpiada-informatica.org/cpp-double-cout-formatting
//      https://www.it-swarm-es.com/es/c%2B%2B/salida-en-negrita-en-c/1052076612/
//  Escribir y leer archivos:
//      https://www.delftstack.com/es/howto/cpp/cpp-write-to-file/
//      https://decodigo.com/c-plus-plus-crear-archivo-de-texto
//      https://decodigo.com/c-plus-plus-leer-archivo-de-texto

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <iomanip>
#include <set>
#include "bibliotecacontabilidad.h"

using namespace std;

//************************************************************************
//Ordena ascendente vector cabecera y vector datosresumeen por una de sus columnas

void ordenar (vector<string> & cabecera, vector<array<float,3>> & resumen, unsigned int columna){
    array<float,3> Aux;
    string AuxS;

    for(unsigned int i=0;i<=cabecera.size()-1;i++)   //Ordenar por el método burbuja
        for(unsigned int j=0;j<=cabecera.size()-2;j++)
            if (resumen[j][columna]>resumen[j+1][columna]){
                Aux=resumen[j];
                AuxS=cabecera[j];
                resumen[j]=resumen[j+1];
                cabecera[j]=cabecera[j+1];
                resumen[j+1]=Aux;
                cabecera[j+1]=AuxS;
            }
}
//************************************************************************

int main() {

    string ficheroentrada = "datosempresa2021c.txt";
    string ficherosalida = "balance2021.txt";
    string linea;
    array<string,5> lineaarray;
    vector<array<string,5>> datosarchivo;
    int columna{0};
    int posicion{0};

    vector<string> meses;
    vector<array<float,3>> resumenmeses;//gastos produccion, ingresos ventas, balance
    vector<string> productos;
    vector<array<float,3>> resumenproductos;//gastos produccion, ingresos ventas, balance

    ifstream ArchivoTexto(ficheroentrada);

    if ( !ArchivoTexto.is_open() ) {
        cerr << "Error de apertura del archivo: " << ficheroentrada << endl;
        return(0);
        }

    while (0==0) {  //Bucle infinito, le damos salida dentro del bucle,
                    //al principio puse while !ArchivoTexto.eof(), pero no detecta que es fin de archivo
                    //hasta que no lee la siguiente linea y ve que no existe
        getline( ArchivoTexto, linea );
        if (ArchivoTexto.eof()) break; //salida justo tras leer linea xra se de cuenta es fin archivo
        linea = linea + ':';
        while (linea.size()>0){
            while (linea[posicion] != ':') posicion++;
            lineaarray[columna]=linea.substr(0,posicion);
            columna++;
            linea.erase(0,posicion+1);
            posicion=0;
            }
        datosarchivo.push_back(lineaarray);
        columna=0;
        }

    ArchivoTexto.close();

//************************************************************************
//Crear listas de resumen de productos y de meses y ordenarlas por balance

//se le pasa la lista cabecera de resumen que queremos crear, la lista total de datos, y la columna de la cabecera a resumir y la lista resumen que quermos crear
    bibliotecacontabilidad::estadisticas().resumir(productos,datosarchivo,1,resumenproductos);
//ordena la lista de cabecera y resumen por una columna determinada para luego sacar las estadisticas de maximos y minimos
    ordenar(productos,resumenproductos,2);

    bibliotecacontabilidad::estadisticas().resumir(meses,datosarchivo,0,resumenmeses);
    ordenar(meses,resumenmeses,2);

//************************************************************************
    string mejorproducto, peorproducto, mejormes, peormes;
    float gastostotales, ventastotales, balance, mediagastos, mediaventas;
//introduce en las variables las estadisticas del los resumenes anteriores, se utiliza la biblioteca  creada
    mejorproducto=bibliotecacontabilidad::estadisticas().maximobeneficio(productos);
    peorproducto=bibliotecacontabilidad::estadisticas().minimobeneficio(productos);
    mejormes=bibliotecacontabilidad::estadisticas().maximobeneficio(meses);
    peormes=bibliotecacontabilidad::estadisticas().minimobeneficio(meses);
    gastostotales=bibliotecacontabilidad::estadisticas().suma(resumenmeses,0);
    ventastotales=bibliotecacontabilidad::estadisticas().suma(resumenmeses,1);
    balance=ventastotales-gastostotales;
    mediagastos=bibliotecacontabilidad::estadisticas().media(resumenmeses,0);
    mediaventas=bibliotecacontabilidad::estadisticas().media(resumenmeses,1);

    bibliotecacontabilidad::estadisticas().escribirbalancetxt(ficherosalida,mejorproducto,peorproducto, mejormes, peormes,
                                                              gastostotales, ventastotales, balance, mediagastos, mediaventas,
                                                              productos, resumenproductos, meses, resumenmeses);
    bibliotecacontabilidad::estadisticas().visualizaranalisis(ficherosalida);

    return(0);

}


