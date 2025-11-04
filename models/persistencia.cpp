#include "persistencia.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

#include "cifra.h"

// Funções auxiliares diretas para converter tipos de ausência.
static char tipoParaCharSimples(TipoAusencia tipo) {
    if (tipo == TipoAusencia::Ferias) {
        return 'F';
    }
    if (tipo == TipoAusencia::Falta) {
        return 'X';
    }
    return '-';
}

static TipoAusencia charParaTipoSimples(char simbolo) {
    if (simbolo == 'F') {
        return TipoAusencia::Ferias;
    }
    if (simbolo == 'X') {
        return TipoAusencia::Falta;
    }
    return TipoAusencia::Nenhum;
}

// Função que separa AAAA-MM-DD em números inteiros.
static bool separarDataSimples(const std::string& data, int& ano, int& mes, int& dia) {
    if (data.size() != 10) {
        return false;
    }
    if (data[4] != '-' || data[7] != '-') {
        return false;
    }

    std::string parteAno = data.substr(0, 4);
    std::string parteMes = data.substr(5, 2);
    std::string parteDia = data.substr(8, 2);

    ano = std::atoi(parteAno.c_str());
    mes = std::atoi(parteMes.c_str());
    dia = std::atoi(parteDia.c_str());

    return true;
}

bool guardarColaboradores(const std::string& nomeFicheiro, const std::vector<Colaborador>& lista) {
    std::ofstream ficheiro(nomeFicheiro.c_str());
    if (!ficheiro.is_open()) {
        return false;
    }

    // Cada linha tem o nome encriptado e as ausencias separadas por ';'.
    for (std::size_t i = 0; i < lista.size(); ++i) {
        const Colaborador& col = lista[i];
        std::string nomeSeguro = Cifra::encriptar(col.nome);
        ficheiro << nomeSeguro;

        std::map<std::string, TipoAusencia>::const_iterator it = col.ausencias.begin();
        while (it != col.ausencias.end()) {
            char simbolo = tipoParaCharSimples(it->second);
            ficheiro << ";" << it->first << "," << simbolo;
            ++it;
        }

        ficheiro << "\n";
    }

    return true;
}

std::vector<Colaborador> carregarColaboradores(const std::string& nomeFicheiro) {
    std::ifstream ficheiro(nomeFicheiro.c_str());
    if (!ficheiro.is_open()) {
        return std::vector<Colaborador>(); // Ficheiro pode não existir ainda.
    }

    std::vector<Colaborador> lista;
    std::string linha;

    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) {
            continue;
        }

        // Primeiro campo até ao ';' é o nome encriptado.
        std::size_t pos = linha.find(';');
        std::string campoNome;
        if (pos == std::string::npos) {
            campoNome = linha;
        } else {
            campoNome = linha.substr(0, pos);
        }

        Colaborador col;
        col.nome = Cifra::desencriptar(campoNome);

        // Lemos as restantes partes (data,sinal) uma a uma.
        std::size_t inicio = (pos == std::string::npos) ? std::string::npos : pos + 1;
        while (inicio != std::string::npos && inicio < linha.size()) {
            std::size_t proximo = linha.find(';', inicio);
            std::string bloco;
            if (proximo == std::string::npos) {
                bloco = linha.substr(inicio);
                inicio = std::string::npos;
            } else {
                bloco = linha.substr(inicio, proximo - inicio);
                inicio = proximo + 1;
            }

            std::size_t posVirgula = bloco.find(',');
            if (posVirgula == std::string::npos) {
                continue;
            }

            std::string textoData = bloco.substr(0, posVirgula);
            char simboloBruto = bloco[posVirgula + 1];

            int ano = 0;
            int mes = 0;
            int dia = 0;
            if (!separarDataSimples(textoData, ano, mes, dia)) {
                continue;
            }

            TipoAusencia tipo = charParaTipoSimples(simboloBruto);
            if (tipo == TipoAusencia::Nenhum) {
                continue;
            }

            col.marcarAusencia(dia, mes, ano, tipo);
        }

        lista.push_back(col);
    }

    return lista;
}
