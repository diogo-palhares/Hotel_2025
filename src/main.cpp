#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"
#include "utils.h"
#include <iostream>

int main() {
    // Inicializar arquivos e diretórios
    inicializarArquivos();
    
    int opcao;
    
    do {
        // Exibir menu principal
        exibirMenuPrincipal();
        
        // Ler opção do usuário
        opcao = lerOpcaoMenu(1, 5);
        
        // Processar opção escolhida
        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
                
            case 2:
                cadastrarFuncionario();
                break;
                
            case 3:
                cadastrarQuarto();
                break;
                
            case 4:
                cadastrarEstadia();
                break;
                
            case 5:
                exibirCabecalho("SAINDO DO SISTEMA");
                exibirMensagem("Obrigado por usar o Sistema Hotel Descanso Garantido!");
                std::cout << "\nAté logo! 👋\n\n";
                break;
                
            default:
                exibirMensagem("Opção inválida!", true);
                pausar();
                break;
        }
        
    } while (opcao != 5);
    
    return 0;
}