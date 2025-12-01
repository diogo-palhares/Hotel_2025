#include "quarto.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Implementação dos construtores
Quarto::Quarto() {
    numero = 0;
    maxHospedes = 0;
    valorDiaria = 0.0f;
    status = DESOCUPADO;
}

Quarto::Quarto(int num, int max, float valor) {
    numero = num;
    maxHospedes = max;
    valorDiaria = valor;
    status = DESOCUPADO; // Sempre inicia desocupado
}

// Funções de serialização
void Quarto::serialize(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(this), sizeof(Quarto));
}

void Quarto::deserialize(std::ifstream& file) {
    file.read(reinterpret_cast<char*>(this), sizeof(Quarto));
}

// Função para exibir dados
void Quarto::exibir() const {
    std::cout << "Número: " << numero << "\n";
    std::cout << "Máximo de hóspedes: " << maxHospedes << "\n";
    std::cout << "Valor da diária: R$ " << std::fixed << std::setprecision(2) << valorDiaria << "\n";
    std::cout << "Status: " << (status == DESOCUPADO ? "Desocupado" : "Ocupado") << "\n";
}

// Função para validar dados
bool Quarto::validar() const {
    if (numero <= 0) return false;
    if (maxHospedes <= 0) return false;
    if (valorDiaria <= 0) return false;
    return true;
}

// Funções de status
void Quarto::ocupar() {
    status = OCUPADO;
}

void Quarto::desocupar() {
    status = DESOCUPADO;
}

bool Quarto::estaDisponivel() const {
    return status == DESOCUPADO;
}

// Função para verificar se quarto existe
bool quartoExiste(int numero) {
    std::ifstream arquivo(ARQUIVO_QUARTOS, std::ios::binary);
    if (!arquivo.is_open()) {
        return false;
    }
    
    Quarto quarto;
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.numero == numero) {
            arquivo.close();
            return true;
        }
    }
    
    arquivo.close();
    return false;
}

// Função para buscar quarto
Quarto buscarQuarto(int numero) {
    Quarto quarto;
    std::ifstream arquivo(ARQUIVO_QUARTOS, std::ios::binary);
    
    if (!arquivo.is_open()) {
        return quarto; // Retorna quarto vazio
    }
    
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.numero == numero) {
            arquivo.close();
            return quarto;
        }
    }
    
    arquivo.close();
    return Quarto(); // Retorna quarto vazio se não encontrar
}

// Função para buscar quarto disponível com capacidade adequada
Quarto buscarQuartoDisponivel(int minHospedes) {
    std::ifstream arquivo(ARQUIVO_QUARTOS, std::ios::binary);
    Quarto quarto;
    
    if (!arquivo.is_open()) {
        return quarto; // Retorna quarto vazio
    }
    
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.estaDisponivel() && quarto.maxHospedes >= minHospedes && quarto.validar()) {
            arquivo.close();
            return quarto;
        }
    }
    
    arquivo.close();
    return Quarto(); // Retorna quarto vazio se não encontrar
}

// Função para atualizar status do quarto
bool atualizarStatusQuarto(int numero, StatusQuarto novoStatus) {
    std::fstream arquivo(ARQUIVO_QUARTOS, std::ios::binary | std::ios::in | std::ios::out);
    if (!arquivo.is_open()) {
        return false;
    }
    
    Quarto quarto;
    std::streampos posicao;
    
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.numero == numero) {
            // Voltar para a posição do registro
            posicao = arquivo.tellg();
            posicao -= sizeof(Quarto);
            arquivo.seekp(posicao);
            
            // Atualizar status
            quarto.status = novoStatus;
            quarto.serialize(arquivo);
            arquivo.close();
            return true;
        }
    }
    
    arquivo.close();
    return false;
}

// Função para listar quartos
void listarQuartos() {
    exibirCabecalho("LISTA DE QUARTOS");
    
    std::ifstream arquivo(ARQUIVO_QUARTOS, std::ios::binary);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo de quartos.", true);
        return;
    }
    
    Quarto quarto;
    bool encontrouQuartos = false;
    
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.validar()) {
            std::cout << "----------------------------------------\n";
            quarto.exibir();
            encontrouQuartos = true;
        }
    }
    
    arquivo.close();
    
    if (!encontrouQuartos) {
        std::cout << "Nenhum quarto cadastrado.\n";
    }
    
    pausar();
}

// Função principal para cadastrar quarto
int cadastrarQuarto() {
    exibirCabecalho("CADASTRO DE QUARTO");
    
    // Ler dados do quarto
    int numero;
    while (true) {
        numero = lerInteiroPositivo("Número do quarto: ");
        if (!quartoExiste(numero)) {
            break;
        }
        exibirMensagem("Já existe um quarto com este número. Tente outro.", true);
    }
    
    int maxHospedes = lerInteiroPositivo("Quantidade máxima de hóspedes: ");
    float valorDiaria = lerFloatPositivo("Valor da diária: R$ ");
    
    // Criar objeto quarto
    Quarto quarto(numero, maxHospedes, valorDiaria);
    
    // Validar dados
    if (!quarto.validar()) {
        exibirMensagem("Dados inválidos. Quarto não foi cadastrado.", true);
        pausar();
        return -1;
    }
    
    // Salvar no arquivo
    std::ofstream arquivo(ARQUIVO_QUARTOS, std::ios::binary | std::ios::app);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo para salvar quarto.", true);
        pausar();
        return -1;
    }
    
    quarto.serialize(arquivo);
    arquivo.close();
    
    exibirMensagem("Quarto cadastrado com sucesso!");
    std::cout << "\nDados cadastrados:\n";
    std::cout << "----------------------------------------\n";
    quarto.exibir();
    
    pausar();
    return numero;
}