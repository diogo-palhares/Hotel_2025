#ifndef CLIENTE_H
#define CLIENTE_H

#include <fstream>
#include <iostream>
#include <string>

struct Cliente {
    int codigo;
    char nome[100];      // Tamanho fixo para acesso direto
    char endereco[200];  // Tamanho fixo para acesso direto
    char telefone[20];   // Tamanho fixo para acesso direto
    
    // Construtor padrão
    Cliente();
    
    // Construtor com parâmetros
    Cliente(int cod, const std::string& n, const std::string& end, const std::string& tel);
    
    // Funções de serialização para arquivo binário
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);
    
    // Função para exibir dados
    void exibir() const;
    
    // Função para validar dados
    bool validar() const;
};

// Declarações das funções de gerenciamento
int cadastrarCliente();
bool clienteExiste(int codigo);
Cliente buscarCliente(int codigo);
int obterProximoCodigo();
void listarClientes();

// Constantes
const char ARQUIVO_CLIENTES[] = "data/clientes.dat";
const int TAMANHO_REGISTRO_CLIENTE = sizeof(Cliente);

#endif