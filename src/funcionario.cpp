#include "funcionario.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

// Implementação dos construtores
Funcionario::Funcionario() {
    codigo = 0;
    memset(nome, 0, sizeof(nome));
    memset(telefone, 0, sizeof(telefone));
    memset(cargo, 0, sizeof(cargo));
    salario = 0.0f;
}

Funcionario::Funcionario(int cod, const std::string& n, const std::string& tel, 
                        const std::string& c, float sal) {
    codigo = cod;
    copiarString(nome, n, sizeof(nome));
    copiarString(telefone, tel, sizeof(telefone));
    copiarString(cargo, c, sizeof(cargo));
    salario = sal;
}

// Funções de serialização
void Funcionario::serialize(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(this), sizeof(Funcionario));
}

void Funcionario::deserialize(std::ifstream& file) {
    file.read(reinterpret_cast<char*>(this), sizeof(Funcionario));
}

// Função para exibir dados
void Funcionario::exibir() const {
    std::cout << "Código: " << codigo << "\n";
    std::cout << "Nome: " << nome << "\n";
    std::cout << "Telefone: " << telefone << "\n";
    std::cout << "Cargo: " << cargo << "\n";
    std::cout << "Salário: R$ " << std::fixed << std::setprecision(2) << salario << "\n";
}

// Função para validar dados
bool Funcionario::validar() const {
    if (codigo <= 0) return false;
    if (strlen(nome) == 0) return false;
    if (strlen(telefone) == 0) return false;
    if (strlen(cargo) == 0) return false;
    if (salario <= 0) return false;
    return true;
}

// Função para obter próximo código
int obterProximoCodigoFuncionario() {
    std::ifstream arquivo(ARQUIVO_FUNCIONARIOS, std::ios::binary);
    if (!arquivo.is_open()) {
        return 1; // Primeiro funcionário
    }
    
    int maiorCodigo = 0;
    Funcionario funcionario;
    
    while (arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(Funcionario))) {
        if (funcionario.codigo > maiorCodigo) {
            maiorCodigo = funcionario.codigo;
        }
    }
    
    arquivo.close();
    return maiorCodigo + 1;
}

// Função para verificar se funcionário existe
bool funcionarioExiste(int codigo) {
    std::ifstream arquivo(ARQUIVO_FUNCIONARIOS, std::ios::binary);
    if (!arquivo.is_open()) {
        return false;
    }
    
    Funcionario funcionario;
    while (arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(Funcionario))) {
        if (funcionario.codigo == codigo) {
            arquivo.close();
            return true;
        }
    }
    
    arquivo.close();
    return false;
}

// Função para buscar funcionário
Funcionario buscarFuncionario(int codigo) {
    Funcionario funcionario;
    std::ifstream arquivo(ARQUIVO_FUNCIONARIOS, std::ios::binary);
    
    if (!arquivo.is_open()) {
        return funcionario; // Retorna funcionário vazio
    }
    
    while (arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(Funcionario))) {
        if (funcionario.codigo == codigo) {
            arquivo.close();
            return funcionario;
        }
    }
    
    arquivo.close();
    return Funcionario(); // Retorna funcionário vazio se não encontrar
}

// Função para listar funcionários
void listarFuncionarios() {
    exibirCabecalho("LISTA DE FUNCIONÁRIOS");
    
    std::ifstream arquivo(ARQUIVO_FUNCIONARIOS, std::ios::binary);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo de funcionários.", true);
        return;
    }
    
    Funcionario funcionario;
    bool encontrouFuncionarios = false;
    
    while (arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(Funcionario))) {
        if (funcionario.validar()) {
            std::cout << "----------------------------------------\n";
            funcionario.exibir();
            encontrouFuncionarios = true;
        }
    }
    
    arquivo.close();
    
    if (!encontrouFuncionarios) {
        std::cout << "Nenhum funcionário cadastrado.\n";
    }
    
    pausar();
}

// Função principal para cadastrar funcionário
int cadastrarFuncionario() {
    exibirCabecalho("CADASTRO DE FUNCIONÁRIO");
    
    // Obter próximo código automaticamente
    int codigo = obterProximoCodigoFuncionario();
    std::cout << "Código do funcionário: " << codigo << " (gerado automaticamente)\n\n";
    
    // Ler dados do funcionário
    std::string nome = lerStringNaoVazia("Nome: ", sizeof(Funcionario().nome) - 1);
    std::string telefone = lerStringNaoVazia("Telefone: ", sizeof(Funcionario().telefone) - 1);
    std::string cargo = lerStringNaoVazia("Cargo: ", sizeof(Funcionario().cargo) - 1);
    float salario = lerFloatPositivo("Salário: R$ ");
    
    // Criar objeto funcionário
    Funcionario funcionario(codigo, nome, telefone, cargo, salario);
    
    // Validar dados
    if (!funcionario.validar()) {
        exibirMensagem("Dados inválidos. Funcionário não foi cadastrado.", true);
        pausar();
        return -1;
    }
    
    // Salvar no arquivo
    std::ofstream arquivo(ARQUIVO_FUNCIONARIOS, std::ios::binary | std::ios::app);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo para salvar funcionário.", true);
        pausar();
        return -1;
    }
    
    funcionario.serialize(arquivo);
    arquivo.close();
    
    exibirMensagem("Funcionário cadastrado com sucesso!");
    std::cout << "\nDados cadastrados:\n";
    std::cout << "----------------------------------------\n";
    funcionario.exibir();
    
    pausar();
    return codigo;
}