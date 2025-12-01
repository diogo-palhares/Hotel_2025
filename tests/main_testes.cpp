#include "../include/testes.h"
#include "../include/utils.h"
#include <iostream>

int main() {
    exibirCabecalho("SISTEMA DE TESTES AUTOMATIZADOS");
    
    std::cout << "🎯 Este programa executará todos os testes automatizados" << std::endl;
    std::cout << "   do Sistema Hotel Descanso Garantido." << std::endl;
    std::cout << std::endl;
    std::cout << "⚠️  ATENÇÃO: Os arquivos de dados serão limpos para os testes!" << std::endl;
    std::cout << "   Faça backup se necessário." << std::endl;
    std::cout << std::endl;
    
    std::cout << "Deseja continuar? (s/n): ";
    std::string resposta;
    std::getline(std::cin, resposta);
    
    if (resposta != "s" && resposta != "S" && resposta != "sim" && resposta != "SIM") {
        std::cout << "Testes cancelados pelo usuário." << std::endl;
        return 0;
    }
    
    // Executar todos os testes
    executarTodosTestes();
    
    std::cout << std::endl;
    pausar();
    
    return 0;
}