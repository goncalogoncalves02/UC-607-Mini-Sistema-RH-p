#ifndef UTIL_DATA_H
#define UTIL_DATA_H

#include <string>

bool eBissexto(int ano);
int diasNoMes(int mes, int ano);
bool eDataValida(int dia, int mes, int ano);
int diaDaSemana(int dia, int mes, int ano);  // 0 = Domingo, 6 = Sabado
std::string nomeMes(int mes);

#endif
