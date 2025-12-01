#ifndef QUARTO_H
#define QUARTO_H

#include <fstream>
#include <iostream>
#include <string>

enum StatusQuarto {
    DESOCUPADO = 0,
    OCUPADO = 1
};

struct Quarto {
    int numero;
    int maxHospedes;
    float valorDiaria;
    StatusQuarto status;  // 0 = desocupado, 1 = ocupado
    
    // Construtor padrão
    Quarto();
    
    // Construtor com parâmetros
    Quarto(int num, int max, float valor);
    
    // Funções de serialização para arquivo binário
    void serialize(std::ofstream& file) const;
    void deserialize(std::ifstream& file);
    
    // Função para exibir dados
    void exibir() const;
    
    // Função para validar dados
    bool validar() const;
    
    // Funções de status
    void ocupar();
    void desocupar();
    bool estaDisponivel() const;
};

// Declarações das funções de gerenciamento
int cadastrarQuarto();
bool quartoExiste(int numero);
Quarto buscarQuarto(int numero);
Quarto buscarQuartoDisponivel(int minHospedes);
bool atualizarStatusQuarto(int numero, StatusQuarto novoStatus);
void listarQuartos();

// Constantes
const char ARQUIVO_QUARTOS[] = "data/quartos.dat";
const int TAMANHO_REGISTRO_QUARTO = sizeof(Quarto);

#endif