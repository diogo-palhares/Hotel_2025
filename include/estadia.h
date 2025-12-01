#ifndef ESTADIA_H
#define ESTADIA_H

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

struct Data {
    int dia;
    int mes;
    int ano;
    
    // Construtor padrão
    Data();
    
    // Construtor com parâmetros
    Data(int d, int m, int a);
    
    // Funções de validação e comparação
    bool validar() const;
    bool operator<(const Data& outra) const;
    bool operator==(const Data& outra) const;
    
    // Função para exibir
    void exibir() const;
    
    // Função para converter para string
    std::string toString() const;
};

struct Estadia {
    int codigoEstadia;
    int codigoCliente;
    int numeroQuarto;
    int quantidadeHospedes;
    Data dataEntrada;
    Data dataSaida;
    int quantidadeDiarias;
    float valorTotal;
    
    // Construtor padrão
    Estadia();
    
    // Construtor com parâmetros
    Estadia(int codEst, int codCli, int numQuarto, int qtdHosp, 
            const Data& entrada, const Data& saida);
    
    // Funções de serialização para arquivo binário
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);
    
    // Função para exibir dados
    void exibir() const;
    
    // Função para validar dados
    bool validar() const;
    
    // Função para calcular diárias e valor total
    void calcularDiariasEValor(float valorDiaria);
};

// Declarações das funções de gerenciamento
int cadastrarEstadia();
bool estadiaExiste(int codigo);
Estadia buscarEstadia(int codigo);
int obterProximoCodigoEstadia();
void listarEstadias();

// Funções auxiliares para datas
int calcularDiarias(const Data& entrada, const Data& saida);
bool dataValida(int dia, int mes, int ano);
Data lerData(const std::string& prompt);

// Constantes
const char ARQUIVO_ESTADIAS[] = "data/estadias.dat";
const int TAMANHO_REGISTRO_ESTADIA = sizeof(Estadia);

#endif