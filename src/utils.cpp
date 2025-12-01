#include "utils.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sys/stat.h>

// Funções de validação de entrada
int lerInteiro(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        } else {
            std::cout << "Erro: Digite um número inteiro válido.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int lerInteiroPositivo(const std::string& prompt) {
    int valor;
    while (true) {
        valor = lerInteiro(prompt);
        if (valor > 0) {
            return valor;
        }
        std::cout << "Erro: O valor deve ser positivo (maior que zero).\n";
    }
}

float lerFloat(const std::string& prompt) {
    float valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        } else {
            std::cout << "Erro: Digite um número decimal válido.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

float lerFloatPositivo(const std::string& prompt) {
    float valor;
    while (true) {
        valor = lerFloat(prompt);
        if (valor > 0) {
            return valor;
        }
        std::cout << "Erro: O valor deve ser positivo (maior que zero).\n";
    }
}

std::string lerString(const std::string& prompt, int tamanhoMax) {
    std::string valor;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, valor);
        valor = trimString(valor);
        
        if (valor.length() <= static_cast<size_t>(tamanhoMax)) {
            return valor;
        }
        std::cout << "Erro: Texto muito longo. Máximo " << tamanhoMax << " caracteres.\n";
    }
}

std::string lerStringNaoVazia(const std::string& prompt, int tamanhoMax) {
    std::string valor;
    while (true) {
        valor = lerString(prompt, tamanhoMax);
        if (!valor.empty()) {
            return valor;
        }
        std::cout << "Erro: Este campo não pode estar vazio.\n";
    }
}

// Funções de manipulação de strings
void copiarString(char* destino, const std::string& origem, int tamanhoMax) {
    int tamanho = std::min(static_cast<int>(origem.length()), tamanhoMax - 1);
    origem.copy(destino, tamanho);
    destino[tamanho] = '\0';
}

std::string trimString(const std::string& str) {
    size_t inicio = str.find_first_not_of(" \t\n\r");
    if (inicio == std::string::npos) return "";
    
    size_t fim = str.find_last_not_of(" \t\n\r");
    return str.substr(inicio, fim - inicio + 1);
}

// Funções de arquivo
bool arquivoExiste(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo.c_str());
    return arquivo.good();
}

bool criarDiretorio(const std::string& caminho) {
    struct stat st = {0};
    if (stat(caminho.c_str(), &st) == -1) {
        #ifdef _WIN32
            return mkdir(caminho.c_str()) == 0;
        #else
            return mkdir(caminho.c_str(), 0755) == 0;
        #endif
    }
    return true; // Diretório já existe
}

void inicializarArquivos() {
    // Criar diretório data se não existir
    criarDiretorio("data");
    
    // Verificar e criar arquivos vazios se necessário
    const char* arquivos[] = {
        "data/clientes.dat",
        "data/funcionarios.dat", 
        "data/quartos.dat",
        "data/estadias.dat"
    };
    
    for (int i = 0; i < 4; i++) {
        if (!arquivoExiste(arquivos[i])) {
            std::ofstream arquivo(arquivos[i], std::ios::binary);
            arquivo.close();
        }
    }
}

// Funções de interface
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void exibirCabecalho(const std::string& titulo) {
    limparTela();
    std::cout << "========================================\n";
    std::cout << "    HOTEL DESCANSO GARANTIDO\n";
    std::cout << "========================================\n";
    std::cout << titulo << "\n";
    std::cout << "----------------------------------------\n\n";
}

void exibirMensagem(const std::string& mensagem, bool erro) {
    if (erro) {
        std::cout << "\n❌ ERRO: " << mensagem << "\n";
    } else {
        std::cout << "\n✅ " << mensagem << "\n";
    }
}

// Funções de menu
void exibirMenuPrincipal() {
    exibirCabecalho("MENU PRINCIPAL");
    std::cout << "1. Cadastrar Cliente\n";
    std::cout << "2. Cadastrar Funcionário\n";
    std::cout << "3. Cadastrar Quarto\n";
    std::cout << "4. Cadastrar Estadia\n";
    std::cout << "5. Sair\n\n";
}

int lerOpcaoMenu(int minOpcao, int maxOpcao) {
    int opcao;
    while (true) {
        opcao = lerInteiro("Escolha uma opção: ");
        if (opcao >= minOpcao && opcao <= maxOpcao) {
            return opcao;
        }
        std::cout << "Erro: Opção inválida. Escolha entre " 
                  << minOpcao << " e " << maxOpcao << ".\n";
    }
}