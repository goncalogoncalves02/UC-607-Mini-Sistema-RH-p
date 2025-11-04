#include "util_data.h"

#include <array>

bool eBissexto(int ano) {
    if (ano % 400 == 0) {
        return true;
    }
    if (ano % 100 == 0) {
        return false;
    }
    return ano % 4 == 0;
}

int diasNoMes(int mes, int ano) {
    switch (mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return eBissexto(ano) ? 29 : 28;
        default:
            return 0;
    }
}

bool eDataValida(int dia, int mes, int ano) {
    if (ano < 1900 || mes < 1 || mes > 12) {
        return false;
    }
    const int limiteDias = diasNoMes(mes, ano);
    return dia >= 1 && dia <= limiteDias;
}

int diaDaSemana(int dia, int mes, int ano) {
    // Congruencia de Zeller ajustada para 0=Domingo.
    if (mes < 3) {
        mes += 12;
        --ano;
    }
    const int k = ano % 100;
    const int j = ano / 100;
    const int h = (dia + (13 * (mes + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    // Resultado original: 0=Sabado. Ajustamos para 0=Domingo.
    return (h + 6) % 7;
}

std::string nomeMes(int mes) {
    static const std::array<std::string, 12> nomes = {
        "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    if (mes < 1 || mes > 12) {
        return "Mes";
    }
    return nomes[static_cast<std::size_t>(mes - 1)];
}
