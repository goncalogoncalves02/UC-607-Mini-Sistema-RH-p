#include "gestor_rh.h"

#include <iostream>
#include <sstream>

#include "../views/calendario.h"
#include "../models/persistencia.h"
#include "../models/util_data.h"

namespace {
    std::string lerLinha(const std::string& pedido) {
        std::cout << pedido;
        std::string linha;
        std::getline(std::cin, linha);  // Permite receber textos com espacos.
        return linha;
    }

    int lerNumero(const std::string& pedido) {
        while (true) {
            std::cout << pedido;
            std::string linha;
            std::getline(std::cin, linha);
            std::istringstream iss(linha);
            int valor = 0;
            if (iss >> valor) {
                return valor;
            }
            std::cout << "Valor invalido. Tente novamente.\n";
        }
    }
} 

GestorRH::GestorRH() : m_nomeFicheiro("colaboradores.csv") {}

void GestorRH::carregarDados() {
    m_colaboradores = carregarColaboradores(m_nomeFicheiro);
    if (!m_colaboradores.empty()) {
        std::cout << "Foram carregados " << m_colaboradores.size() << " colaboradores.\n";
    }
}

void GestorRH::guardarDados() const {
    if (guardarColaboradores(m_nomeFicheiro, m_colaboradores)) {
        std::cout << "Dados guardados em " << m_nomeFicheiro << ".\n";
    } else {
        std::cout << "Nao foi possivel guardar os dados no ficheiro.\n";
    }
}