#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <fstream>
#include <iostream>
#include <string>

struct Funcionario {
    int codigo;
    char nome[100];     // Tamanho fixo para acesso direto
    char telefone[20];  // Tamanho fixo para acesso direto
    char cargo[50];     // Tamanho fixo para acesso direto
    float salario;
    
    // Construtor padrão
    Funcionario();
    
    // Construtor com parâmetros
    Funcionario(int cod, const std::string& n, const std::string& tel, 
                const std::string& c, float sal);
    
    // Funções de serialização para arquivo binário
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);
    
    // Função para exibir dados
    void exibir() const;
    
    // Função para validar dados
    bool validar() const;
};

// Declarações das funções de gerenciamento
int cadastrarFuncionario();
bool funcionarioExiste(int codigo);
Funcionario buscarFuncionario(int codigo);
int obterProximoCodigoFuncionario();
void listarFuncionarios();

// Constantes
const char ARQUIVO_FUNCIONARIOS[] = "data/funcionarios.dat";
const int TAMANHO_REGISTRO_FUNCIONARIO = sizeof(Funcionario);

#endif