#include "calendario.h"

#include <iostream>
#include <string>

#include "../models/util_data.h"

void mostrarCalendarioMensal(const Colaborador& col, int mes, int ano) {
    int totalDias = diasNoMes(mes, ano);
    if (totalDias <= 0) {
        std::cout << "Mes invalido.\n";
        return;
    }

    std::cout << "\nCalendario de " << col.nome << " - " << nomeMes(mes) << " " << ano << "\n";
    std::cout << "Dom Seg Ter Qua Qui Sex Sab\n";

    int diaSemanaPrimeiro = diaDaSemana(1, mes, ano);
    for (int i = 0; i < diaSemanaPrimeiro; ++i) {
        std::cout << "    "; // avanca com espaços simples
    }

    for (int dia = 1; dia <= totalDias; ++dia) {
        int diaSemanaAtual = diaDaSemana(dia, mes, ano);
        TipoAusencia tipo = col.obterAusencia(dia, mes, ano);

        char marca = ' ';
        if (tipo == TipoAusencia::Ferias) {
            marca = 'F';
        } else if (tipo == TipoAusencia::Falta) {
            marca = 'X';
        } else if (diaSemanaAtual == 0 || diaSemanaAtual == 6) {
            marca = 'W';
        }

        std::string textoDia;
        if (dia < 10) {
            textoDia = " " + std::to_string(dia);
        } else {
            textoDia = std::to_string(dia);
        }

        std::cout << textoDia << marca << " ";

        if (diaSemanaAtual == 6) {
            std::cout << "\n";
        }
    }

    if (diaDaSemana(totalDias, mes, ano) != 6) {
        std::cout << "\n";
    }

    std::cout << "Legenda: F=Ferias, X=Falta, W=Fim de semana\n"; // TODO: adicionar mais tipos se houver
}
