#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <map>
#include <string>

// Representa os tipos de ausência possíveis
enum class TipoAusencia {
    Nenhum,
    Ferias,
    Falta
};

// Estrutura que guarda o nome e as ausências marcadas
struct Colaborador {
    std::string nome;
    std::map<std::string, TipoAusencia> ausencias;

    void marcarAusencia(int dia, int mes, int ano, TipoAusencia tipo);
    void desmarcarAusencia(int dia, int mes, int ano);
    TipoAusencia obterAusencia(int dia, int mes, int ano) const;
};

#endif // COLABORADOR_H