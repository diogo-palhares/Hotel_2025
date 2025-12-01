#include "cliente.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

// Implementação dos construtores
Cliente::Cliente() {
    codigo = 0;
    memset(nome, 0, sizeof(nome));
    memset(endereco, 0, sizeof(endereco));
    memset(telefone, 0, sizeof(telefone));
}

Cliente::Cliente(int cod, const std::string& n, const std::string& end, const std::string& tel) {
    codigo = cod;
    copiarString(nome, n, sizeof(nome));
    copiarString(endereco, end, sizeof(endereco));
    copiarString(telefone, tel, sizeof(telefone));
}

// Funções de serialização
void Cliente::serialize(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(this), sizeof(Cliente));
}

void Cliente::deserialize(std::ifstream& file) {
    file.read(reinterpret_cast<char*>(this), sizeof(Cliente));
}

// Função para exibir dados
void Cliente::exibir() const {
    std::cout << "Código: " << codigo << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Endereço: " << endereco << "\n";
    std::cout << "Telefone: " << telefone << "\n";
}

// Função para validar dados
bool Cliente::validar() const {
    if (codigo <= 0) return false;
    if (strlen(nome) == 0) return false;
    if (strlen(endereco) == 0) return false;
    if (strlen(telefone) == 0) return false;
    return true;
}

// Função para obter próximo código
int obterProximoCodigo() {
    std::ifstream arquivo(ARQUIVO_CLIENTES, std::ios::binary);
    if (!arquivo.is_open()) {
        return 1; // Primeiro cliente
    }
    
    int maiorCodigo = 0;
    Cliente cliente;
    
    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        if (cliente.codigo > maiorCodigo) {
            maiorCodigo = cliente.codigo;
        }
    }
    
    arquivo.close();
    return maiorCodigo + 1;
}

// Função para verificar se cliente existe
bool clienteExiste(int codigo) {
    std::ifstream arquivo(ARQUIVO_CLIENTES, std::ios::binary);
    if (!arquivo.is_open()) {
        return false;
    }
    
    Cliente cliente;
    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        if (cliente.codigo == codigo) {
            arquivo.close();
            return true;
        }
    }
    
    arquivo.close();
    return false;
}

// Função para buscar cliente
Cliente buscarCliente(int codigo) {
    Cliente cliente;
    std::ifstream arquivo(ARQUIVO_CLIENTES, std::ios::binary);
    
    if (!arquivo.is_open()) {
        return cliente; // Retorna cliente vazio
    }
    
    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        if (cliente.codigo == codigo) {
            arquivo.close();
            return cliente;
        }
    }
    
    arquivo.close();
    return Cliente(); // Retorna cliente vazio se não encontrar
}

// Função para listar clientes
void listarClientes() {
    exibirCabecalho("LISTA DE CLIENTES CADASTRADOS");
    
    std::ifstream arquivo(ARQUIVO_CLIENTES, std::ios::binary);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo de clientes.", true);
        pausar();
        return;
    }
    
    Cliente cliente;
    bool encontrouClientes = false;
    int contador = 0;
    
    // Cabeçalho da tabela
    std::cout << std::left << std::setw(8) << "Código" 
              << std::setw(25) << "Nome" 
              << std::setw(30) << "Endereço" 
              << std::setw(15) << "Telefone" << "\n";
    std::cout << std::string(78, '=') << "\n";
    
    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        if (cliente.validar()) {
            contador++;
            std::cout << std::left << std::setw(8) << cliente.codigo
                      << std::setw(25) << cliente.nome
                      << std::setw(30) << cliente.endereco
                      << std::setw(15) << cliente.telefone << "\n";
            encontrouClientes = true;
        }
    }
    
    arquivo.close();
    
    if (!encontrouClientes) {
        std::cout << "\n Nenhum cliente cadastrado no sistema.\n";
        std::cout << "Use a opção 1 do menu principal para cadastrar clientes.\n";
    } else {
        std::cout << std::string(78, '=') << "\n";
        std::cout << "Total de clientes cadastrados: " << contador << "\n";
    }
    
    pausar();
}

// Função principal para cadastrar cliente
int cadastrarCliente() {
    exibirCabecalho("CADASTRO DE CLIENTE");
    
    // Obter próximo código automaticamente
    int codigo = obterProximoCodigo();
    std::cout << "Código do cliente: " << codigo << " (gerado automaticamente)\n\n";
    
    // Ler dados do cliente
    std::string nome = lerStringNaoVazia("Nome: ", sizeof(Cliente().nome) - 1);
    std::string endereco = lerStringNaoVazia("Endereço: ", sizeof(Cliente().endereco) - 1);
    std::string telefone = lerStringNaoVazia("Telefone: ", sizeof(Cliente().telefone) - 1);
    
    // Criar objeto cliente
    Cliente cliente(codigo, nome, endereco, telefone);
    
    // Validar dados
    if (!cliente.validar()) {
        exibirMensagem("Dados inválidos. Cliente não foi cadastrado.", true);
        pausar();
        return -1;
    }
    
    // Salvar no arquivo
    std::ofstream arquivo(ARQUIVO_CLIENTES, std::ios::binary | std::ios::app);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo para salvar cliente.", true);
        pausar();
        return -1;
    }
    
    cliente.serialize(arquivo);
    arquivo.close();
    
    exibirMensagem("Cliente cadastrado com sucesso!");
    std::cout << "\nDados cadastrados:\n";
    std::cout << "----------------------------------------\n";
    cliente.exibir();
    
    pausar();
    return codigo;
}
