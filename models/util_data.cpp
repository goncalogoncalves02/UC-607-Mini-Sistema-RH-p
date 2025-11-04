#include "util_data.h"

// Função pequena para saber se o ano é bissexto.
bool eBissexto(int ano) {
    if (ano % 400 == 0) {
        return true;
    }
    if (ano % 100 == 0) {
        return false;
    }
    return (ano % 4 == 0);
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
            if (eBissexto(ano)) {
                return 29;
            }
            return 28;
        default:
            return 0; // TODO: tratar meses inválidos melhor
    }
}

bool eDataValida(int dia, int mes, int ano) {
    if (ano < 1900) {
        return false;
    }
    if (mes < 1 || mes > 12) {
        return false;
    }
    int limiteDias = diasNoMes(mes, ano);
    return (dia >= 1 && dia <= limiteDias);
}

int diaDaSemana(int dia, int mes, int ano) {
    // Congruência de Zeller versão clássica. 0 = Domingo, 6 = Sábado.
    int mesConvertido = mes;
    int anoConvertido = ano;
    if (mesConvertido < 3) {
        mesConvertido += 12;
        anoConvertido -= 1;
    }

    int k = anoConvertido % 100;
    int j = anoConvertido / 100;

    int parte1 = (13 * (mesConvertido + 1)) / 5;
    int parte2 = k / 4;
    int parte3 = j / 4;
    int h = (dia + parte1 + k + parte2 + parte3 + (5 * j)) % 7;

    int resultado = (h + 6) % 7;
    return resultado;
}

std::string nomeMes(int mes) {
    static const char* nomes[12] = {
        "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    if (mes < 1 || mes > 12) {
        return "Mes";
    }
    return nomes[mes - 1];
}
