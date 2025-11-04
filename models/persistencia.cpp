#include "persistencia.h"

#include <fstream>
#include <sstream>

#include "cifra.h"

namespace {
    char tipoParaChar(TipoAusencia tipo) {
        if (tipo == TipoAusencia::Ferias) {
            return 'F';
        }
        if (tipo == TipoAusencia::Falta) {
            return 'X';
        }
        return '-';
    }

    TipoAusencia charParaTipo(char simbolo) {
        if (simbolo == 'F') {
            return TipoAusencia::Ferias;
        }
        if (simbolo == 'X') {
            return TipoAusencia::Falta;
        }
        return TipoAusencia::Nenhum;
    }

    bool separarData(const std::string& data, int& ano, int& mes, int& dia) {
        if (data.size() != 10 || data[4] != '-' || data[7] != '-') {
            return false;
        }
        try {
            ano = std::stoi(data.substr(0, 4));
            mes = std::stoi(data.substr(5, 2));
            dia = std::stoi(data.substr(8, 2));
        } catch (...) {
            return false;
        }
        return true;
    }
}

bool guardarColaboradores(const std::string& nomeFicheiro, const std::vector<Colaborador>& lista) {
    std::ofstream ficheiro(nomeFicheiro.c_str());
    if (!ficheiro.is_open()) {
        return false;
    }

    // Grava cada colaborador numa linha encriptando primeiro o nome.
    for (const Colaborador& col : lista) {
        const std::string nomeSeguro = Cifra::encriptar(col.nome);
        ficheiro << nomeSeguro;
        for (const auto& entrada : col.ausencias) {
            const char simbolo = tipoParaChar(entrada.second);
            ficheiro << ";" << entrada.first << "," << simbolo;
        }
        ficheiro << "\n";
    }

    return true;
}

std::vector<Colaborador> carregarColaboradores(const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro.c_str());
    if (!ficheiro.is_open()) {
        return {};
    }

    std::vector<Colaborador> lista;
    std::string linha;

    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);
        std::string campo;

        if (!std::getline(ss, campo, ';')) {
            continue;
        }

        Colaborador col;
        col.nome = Cifra::desencriptar(campo);

        // Le cada ausencia separada por ';' e recria o mapa com as datas.
        while (std::getline(ss, campo, ';')) {
            const std::size_t separador = campo.find(',');
            if (separador == std::string::npos || separador + 1 >= campo.size()) {
                continue;
            }

            const std::string data = campo.substr(0, separador);
            const char simbolo = campo[separador + 1];

            int ano = 0;
            int mes = 0;
            int dia = 0;
            if (!separarData(data, ano, mes, dia)) {
                continue;
            }

            const TipoAusencia tipo = charParaTipo(simbolo);
            if (tipo == TipoAusencia::Nenhum) {
                continue;
            }

            col.marcarAusencia(dia, mes, ano, tipo);
        }

        lista.push_back(col);
    }

    return lista;
}