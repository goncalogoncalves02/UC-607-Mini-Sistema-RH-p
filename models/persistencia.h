#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <string>
#include <vector>

#include "colaborador.h"

bool guardarColaboradores(const std::string& nomeFicheiro, const std::vector<Colaborador>& lista);
std::vector<Colaborador> carregarColaboradores(const std::string& nomeFicheiro);

#endif