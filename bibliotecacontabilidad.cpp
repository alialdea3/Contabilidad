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

#include "bibliotecacontabilidad.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <iomanip>
#include <set>

using namespace std;

namespace bibliotecacontabilidad
{

//************************************************************************
//construir un vector con los elementos diferentes, separandolos de la columna del vector elementos

vector<string> estadisticas::diferentes(vector<array<string,5>> const & elementos,int columna){
    set<string> dif;//la variable tipo set es como un vector, pero los elementos no se pueden repetir, por lo que cuando
                    //introduces un valor que ya existe simplemente no se añade
    for(unsigned int fila=0;fila<=elementos.size()-1;fila++) dif.insert((elementos[fila][columna]));// se inserta y se desplaza lo dem
    vector<string> aux(dif.begin(), dif.end());//transformamos un set a vector, lo busque en google

    return aux;
}
//************************************************************************
//Resumir la lista por los elementos de una cabecera que están en la columna establecida

void estadisticas::resumir (vector<string> & cabecera, vector<array<string,5>> const & elementos, int columna, vector<array<float,3>> & resumen){
    unsigned int i;//solo valor +
    cabecera = estadisticas::diferentes(elementos,columna);
    for (i=0;i<=cabecera.size()-1;i++) resumen.push_back({0,0,0});  //inicializar a 0 el vector con el tamaño correspondiente a la cabecera, para que sea mas facil lgo

    for (i=0;i<=cabecera.size()-1;i++){
        for(unsigned int fila=0;fila<=elementos.size()-1;fila++){// en la biblioteca no compila si pones int i =0 sin el unsinged
            if (elementos[fila][columna]==cabecera[i]){
                if (elementos[fila][3]=="Venta"){
                    resumen[i][1]= resumen[i][1] + (stof(elementos[fila][2]) * stof(elementos[fila][4]));
                }
                else resumen[i][0]= resumen[i][0] + (stof(elementos[fila][2]) * stof(elementos[fila][4]));
            }
         }
        resumen[i][2]= resumen[i][1] - resumen[i][0];
        }
}
//************************************************************************
//Devuelve el elemento de la lista con el maximo beneficio
string estadisticas::maximobeneficio (vector<string> const & cabecera){
    return cabecera[cabecera.size()-1];
}
//************************************************************************
//Devuelve el elemento de la lista con el minimo beneficio
string estadisticas::minimobeneficio (vector<string> const & cabecera){
    return cabecera[0];
}
//************************************************************************
//Devuelve la suma de la columna de la lista
float estadisticas::suma (vector<array<float,3>> const & resumen, unsigned int columna){
    float aux=0;
    for(unsigned int i=0;i<=resumen.size()-1;i++)
        aux=aux+resumen[i][columna];
    return aux;
}
//************************************************************************
//Devuelve la media de la columna de la lista
float estadisticas::media (vector<array<float,3>> const & resumen, unsigned int columna){
    return (suma(resumen,columna)/resumen.size());
}
//************************************************************************
//Escribe en un archivo el analisis contable de la empresa
void estadisticas::escribirbalancetxt (string archivo, string mejorproducto, string peorproducto, string mejormes, string peormes,
                                       float gastostotales, float ventastotales, float balance, float mediagastos, float mediaventas,
                                       vector<string> const &productos, vector<array<float,3>> const &resumenproductos,
                                       vector<string> const &meses, vector<array<float,3>> const &resumenmeses){

    ofstream archivotxtbalance( archivo );

    archivotxtbalance << "ESTADISTICAS ANUALES DE LA EMPRESA 'MUEBLES AMABLE'" << endl << endl;

    archivotxtbalance << fixed;
    archivotxtbalance << setprecision(2);
    archivotxtbalance <<"\e[1mProducto\t\t     Coste\t\tFacturacion\t\t Beneficio\e[0m"<<endl;

    for(unsigned int i=0;i<=productos.size()-1;i++)
       archivotxtbalance <<productos[i]<<"\t\t"<< setw(10)<<resumenproductos[i][0]<<"\t\t"
                         << setw(11)<<resumenproductos[i][1]<<"\t\t"<< setw(10)<< resumenproductos[i][2]<<endl;
    archivotxtbalance <<endl;

    archivotxtbalance << fixed;
    archivotxtbalance << setprecision(2);
    archivotxtbalance <<"\e[1mMes\t\t     Coste\t\tFacturacion\t\t Beneficio\e[0m"<<endl;

    for(unsigned int i=0;i<=meses.size()-1;i++)
       archivotxtbalance <<meses[i]<<"\t\t"<< setw(10)<<resumenmeses[i][0]<<"\t\t"
                         << setw(11)<<resumenmeses[i][1]<<"\t\t"<< setw(10)<< resumenmeses[i][2]<<endl;

    archivotxtbalance << endl << endl;


    archivotxtbalance << "El producto con el MÁXIMO beneficio anual es: " << mejorproducto << endl;
    archivotxtbalance << "El producto con el MÍNIMO beneficio anual es: " << peorproducto << endl;
    archivotxtbalance << endl;
    archivotxtbalance << "El MEJOR mes del año es: " << mejormes << endl;
    archivotxtbalance << "El PEOR mes del año es: " << peormes << endl;
    archivotxtbalance << endl;
    archivotxtbalance << fixed;
    archivotxtbalance << setprecision(2);
    archivotxtbalance << "Los GASTOS totales son: " << gastostotales << endl;
    archivotxtbalance << "Las VENTAS totales son: " << ventastotales << endl;
    archivotxtbalance << "\e[1mEl BENEFICIO anual es: " << balance << "\e[0m" << endl;
    archivotxtbalance << endl;
    archivotxtbalance << "La media mensual de GASTOS son: " << mediagastos << endl;
    archivotxtbalance << "La media mensual de VENTAS son: " << mediaventas << endl;

    archivotxtbalance.close();
}
//************************************************************************
//Visualiza el analisis contable de la empresa leido de un archivo
void estadisticas::visualizaranalisis (string archivo){

    ifstream archivotxtbalance(archivo);

    if ( !archivotxtbalance.is_open() ) {
        cerr << "Error de apertura del archivo: " << archivo << endl;
        return;
        }

    string linea;
    cout <<endl<<endl;
    while (0==0) {          //mientras no sea el final del archivo
        getline( archivotxtbalance, linea );
        if (archivotxtbalance.eof()) break; //salida justo tras leer linea xra se de cuenta es fin archivo
        cout << linea << endl;
        }
    cout <<endl<<endl;

    archivotxtbalance.close();
}
//************************************************************************

}
