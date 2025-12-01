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

void Quarto::serialize(std::fstream& file) const {
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
            quarto.serialize(arquivo);  // Agora funciona com fstream
            arquivo.close();
            return true;
        }
    }
    
    arquivo.close();
    return false;
}

// Função para listar quartos
void listarQuartos() {
    exibirCabecalho("LISTA DE QUARTOS CADASTRADOS");
    
    std::ifstream arquivo(ARQUIVO_QUARTOS, std::ios::binary);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo de quartos.", true);
        pausar();
        return;
    }
    
    Quarto quarto;
    bool encontrouQuartos = false;
    int contador = 0;
    int quartosDisponiveis = 0;
    int quartosOcupados = 0;
    float valorMedio = 0.0f;
    
    // Cabeçalho da tabela
    std::cout << std::left << std::setw(8) << "Número" 
              << std::setw(12) << "Hóspedes" 
              << std::setw(15) << "Diária"
              << std::setw(12) << "Status" << "\n";
    std::cout << std::string(47, '=') << "\n";
    
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.validar()) {
            contador++;
            valorMedio += quarto.valorDiaria;
            
            if (quarto.status == DESOCUPADO) {
                quartosDisponiveis++;
            } else {
                quartosOcupados++;
            }
            
            std::cout << std::left << std::setw(8) << quarto.numero
                      << std::setw(12) << quarto.maxHospedes
                      << "R$ " << std::fixed << std::setprecision(2) 
                      << std::setw(12) << quarto.valorDiaria
                      << (quarto.status == DESOCUPADO ? "🟢 Livre" : "🔴 Ocupado") << "\n";
            encontrouQuartos = true;
        }
    }
    
    arquivo.close();
    
    if (!encontrouQuartos) {
        std::cout << "\n🏨 Nenhum quarto cadastrado no sistema.\n";
        std::cout << "💡 Use a opção 3 do menu principal para cadastrar quartos.\n";
    } else {
        std::cout << std::string(47, '=') << "\n";
        std::cout << "📊 ESTATÍSTICAS DOS QUARTOS:\n";
        std::cout << "🏨 Total de quartos: " << contador << "\n";
        std::cout << "🟢 Quartos disponíveis: " << quartosDisponiveis << "\n";
        std::cout << "🔴 Quartos ocupados: " << quartosOcupados << "\n";
        std::cout << "💰 Valor médio da diária: R$ " << std::fixed 
                  << std::setprecision(2) << (valorMedio / contador) << "\n";
        
        if (quartosDisponiveis > 0) {
            std::cout << "✅ Taxa de ocupação: " << std::fixed 
                      << std::setprecision(1) 
                      << ((float)quartosOcupados / contador * 100) << "%\n";
        }
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