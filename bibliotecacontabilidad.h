#include<string>
#include<vector>
#include<array>

#ifndef BIBLIOTECACONTABILIDAD_H
#define BIBLIOTECACONTABILIDAD_H

using namespace std;

namespace bibliotecacontabilidad
{
    class estadisticas
    {
    public:
        //bibliotecacontabilidad();
        vector<string> diferentes (vector<array<string,5>> const &elementos,int columna);

        void resumir (vector<string> &cabecera, vector<array<string,5>> const &elementos,
                      int columna, vector<array<float,3>> &resumen);

        string maximobeneficio (vector<string> const &cabecera);

        string minimobeneficio (vector<string> const &cabecera);

        float suma (vector<array<float,3>> const &resumen, unsigned int columna);

        float media (vector<array<float,3>> const &resumen, unsigned int columna);

        void escribirbalancetxt (string archivo, string mejorproducto, string peorproducto, string mejormes, string peormes,
                                 float gastostotales, float ventastotales, float balance, float mediagastos, float mediaventas,
                                 vector<string> const &productos, vector<array<float,3>> const &resumenproductos,
                                 vector<string> const &meses, vector<array<float,3>> const &resumenmeses);

        void visualizaranalisis (string archivo);
    };
}

#endif // BIBLIOTECACONTABILIDAD_H






//#include<string>
//#include<vector>
//#include<array>

//#ifndef BIBLIOTECACONTABILIDAD_H
//#define BIBLIOTECACONTABILIDAD_H

//class bibliotecacontabilidad
//{
//public:
//    bibliotecacontabilidad();
//    std::vector<std::string> diferentes(std::vector<std::array<std::string,5>> const & elementos,int columna);
//    void resumir (std::vector<std::string> & cabecera, std::vector<std::array<std::string,5>> const & elementos,
//                  int columna, std::vector<std::array<float,3>> & resumen);
//};

//#endif // BIBLIOTECACONTABILIDAD_H
