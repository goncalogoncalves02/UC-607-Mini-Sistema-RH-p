#include "colaborador.h"

#include <iomanip>
#include <sstream>

namespace {
    // Função auxiliar para formatar a data AAAA-MM-DD
    std::string chaveData(int dia, int mes, int ano) {
        std::ostringstream os;
        os << std::setw(4) << std::setfill('0') << ano
            << "-" << std::setw(2) << std::setfill('0') << mes
            << "-" << std::setw(2) << std::setfill('0') << dia;
        return os.str();
    }
}

void Colaborador::marcarAusencia(int dia, int mes, int ano, TipoAusencia tipo) {
    const std::string chave = chaveData(dia, mes, ano);
    ausencias[chave] = tipo;
}

void Colaborador::desmarcarAusencia(int dia, int mes, int ano) {
    const std::string chave = chaveData(dia, mes, ano);
    ausencias.erase(chave);
}

TipoAusencia Colaborador::obterAusencia(int dia, int mes, int ano) const {
    const std::string chave = chaveData(dia, mes, ano);
    const auto it = ausencias.find(chave);
    if (it == ausencias.end()) {
        return TipoAusencia::Nenhum;
    }
    return it->second;
}