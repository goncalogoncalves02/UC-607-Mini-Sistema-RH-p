#ifndef GESTOR_RH_H
#define GESTOR_RH_H

#include <string>
#include <vector>

#include "../models/colaborador.h"

class GestorRH {
    public:
        GestorRH();

        void carregarDados();
        void guardarDados() const;

        void adicionarColaborador();
        void listarColaboradores() const;
        void marcarOuDesmarcarAusencia();
        void visualizarCalendario();
        
        private:
            std::vector<Colaborador> m_colaboradores;
            std::string m_nomeFicheiro;

            Colaborador* encontrarColaborador(const std::string& nome);
            const Colaborador* encontrarColaborador(const std::string& nome) const;
        };

#endif // GESTOR_RH_H