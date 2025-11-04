#include "cifra.h"

#include <cctype>

namespace {
const int CHAVE = 3;

char cifrarCaractere(char c, int deslocamento) {
    if (std::isupper(static_cast<unsigned char>(c))) {
        return static_cast<char>('A' + (c - 'A' + deslocamento + 26) % 26);
    }
    if (std::islower(static_cast<unsigned char>(c))) {
        return static_cast<char>('a' + (c - 'a' + deslocamento + 26) % 26);
    }
    return c;  // caracteres nao alfabeticos ficam iguais
}
} 

std::string Cifra::encriptar(const std::string& texto) {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = cifrarCaractere(c, CHAVE);
    }
    return resultado;
}

std::string Cifra::desencriptar(const std::string& texto) {
    std::string resultado = texto;
    for (char& c : resultado) {
        c = cifrarCaractere(c, -CHAVE);
    }
    return resultado;
}