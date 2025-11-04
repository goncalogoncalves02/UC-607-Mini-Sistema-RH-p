#include "controllers/gestor_rh.h"

#include <iostream>
#include <sstream>
#include <string>

int lerOpcao() {
    std::cout << "Opcao: ";
    std::string linha;
    std::getline(std::cin, linha);
    std::istringstream iss(linha);
    int valor = 0;
    if (!(iss >> valor)) {
        std::cout << "Valor inválido. Tente novamente." << std::endl;
    }
    return valor;
}

int main() {
    GestorRH gestor;
    gestor.carregarDados();

    bool correr = true;
    while (correr) {
        std::cout << "\n=== Mini Sistema RH ===\n";
        std::cout << "1. Adicionar Colaborador\n";
        std::cout << "2. Listar Colaboradores\n";
        std::cout << "3. Marcar/Desmarcar Ausencia\n";
        std::cout << "4. Visualizar Calendario\n";
        std::cout << "5. Guardar e Sair\n";
    

        // Usamos o GestorRH para executar as operações conforme a opção do utilizador
        const int opcao = lerOpcao();
        switch (opcao) {
            case 1:
                gestor.adicionarColaborador();
                break;
            case 2:
                gestor.listarColaboradores();
                break;
            case 3:
                gestor.marcarOuDesmarcarAusencia();
                break;
            case 4:
                gestor.visualizarCalendario();
                break;
            case 5:
                correr = false;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
                break;  
        }
    }

    gestor.guardarDados();
    std::cout << "Programa terminado.\n";
    return 0;
}
