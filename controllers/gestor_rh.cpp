#include "gestor_rh.h"

#include <iostream>
#include <sstream>

#include "../views/calendario.h"
#include "../models/persistencia.h"
#include "../models/util_data.h"

static std::string lerLinhaSimples(const std::string& pergunta) {
    std::cout << pergunta;
    std::string texto;
    std::getline(std::cin, texto);
    return texto;
}

static int lerNumeroSimples(const std::string& pergunta) {
    while (true) {
        std::cout << pergunta;
        std::string resposta;
        std::getline(std::cin, resposta);
        std::istringstream conversor(resposta);
        int valor = 0;
        if (conversor >> valor) {
            return valor;
        }
        std::cout << "Valor invalido. Escreva um numero.\n";
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

void GestorRH::adicionarColaborador() {
    std::string nome = lerLinhaSimples("Nome do colaborador: ");
    if (nome.empty()) {
        std::cout << "Nome vazio. Operacao cancelada.\n";
        return;
    }

    if (encontrarColaborador(nome) != nullptr) {
        std::cout << "Ja existe um colaborador com esse nome.\n";
        return;
    }

    Colaborador novo;
    novo.nome = nome;
    m_colaboradores.push_back(novo);
    std::cout << "Colaborador adicionado com sucesso.\n";
}

void GestorRH::listarColaboradores() const {
    if (m_colaboradores.empty()) {
        std::cout << "Ainda nao existem colaboradores.\n";
        return;
    }

    std::cout << "Lista de colaboradores:\n";
    for (std::size_t i = 0; i < m_colaboradores.size(); ++i) {
        std::cout << i + 1 << " - " << m_colaboradores[i].nome << "\n";
    }
}

void GestorRH::marcarOuDesmarcarAusencia() {
    if (m_colaboradores.empty()) {
        std::cout << "Adicione colaboradores antes de marcar ausencias.\n";
        return;
    }

    std::string nome = lerLinhaSimples("Nome do colaborador: ");
    Colaborador* col = encontrarColaborador(nome);
    if (col == nullptr) {
        std::cout << "Colaborador nao encontrado.\n";
        return;
    }

    std::cout << "Escolha uma opcao:\n";
    std::cout << "1 - Marcar ferias\n";
    std::cout << "2 - Marcar falta\n";
    std::cout << "3 - Desmarcar ausencia\n";
    int opcao = lerNumeroSimples("Opcao: ");

    int dia = lerNumeroSimples("Dia (1-31): ");
    int mes = lerNumeroSimples("Mes (1-12): ");
    int ano = lerNumeroSimples("Ano (>=1900): ");

    if (!eDataValida(dia, mes, ano)) {
        std::cout << "Data invalida.\n";
        return;
    }

    int diaSemanaAtual = diaDaSemana(dia, mes, ano);
    bool fimDeSemana = (diaSemanaAtual == 0 || diaSemanaAtual == 6);

    if (opcao == 1) {
        if (fimDeSemana) {
            std::cout << "Nao pode marcar ferias ao fim de semana.\n";
            return;
        }
        col->marcarAusencia(dia, mes, ano, TipoAusencia::Ferias);
        std::cout << "Ferias marcadas.\n";
    } else if (opcao == 2) {
        if (fimDeSemana) {
            std::cout << "Nao pode marcar faltas ao fim de semana.\n";
            return;
        }
        col->marcarAusencia(dia, mes, ano, TipoAusencia::Falta);
        std::cout << "Falta marcada.\n";
    } else if (opcao == 3) {
        col->desmarcarAusencia(dia, mes, ano);
        std::cout << "Ausencia removida se existia.\n";
    } else {
        std::cout << "Opcao invalida.\n";
    }
}

void GestorRH::visualizarCalendario() {
    if (m_colaboradores.empty()) {
        std::cout << "Adicione colaboradores antes de visualizar calendarios.\n";
        return;
    }

    std::string nome = lerLinhaSimples("Nome do colaborador: ");
    const Colaborador* col = encontrarColaborador(nome);
    if (col == nullptr) {
        std::cout << "Colaborador nao encontrado.\n";
        return;
    }

    int mes = lerNumeroSimples("Mes (1-12): ");
    int ano = lerNumeroSimples("Ano (>=1900): ");
    if (mes < 1 || mes > 12 || ano < 1900) {
        std::cout << "Mes ou ano invalidos.\n";
        return;
    }

    mostrarCalendarioMensal(*col, mes, ano);
}

Colaborador* GestorRH::encontrarColaborador(const std::string& nome) {
    for (Colaborador& col : m_colaboradores) {
        if (col.nome == nome) {
            return &col;
        }
    }
    return nullptr;
}

const Colaborador* GestorRH::encontrarColaborador(const std::string& nome) const {
    for (const Colaborador& col : m_colaboradores) {
        if (col.nome == nome) {
            return &col;
        }
    }
    return nullptr;
}
