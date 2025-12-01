#include "estadia.h"
#include "cliente.h"
#include "quarto.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstring>

// Implementação da struct Data
Data::Data() {
    dia = 0;
    mes = 0;
    ano = 0;
}

Data::Data(int d, int m, int a) {
    dia = d;
    mes = m;
    ano = a;
}

bool Data::validar() const {
    if (ano < 2020 || ano > 2030) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    
    // Verificar dias por mês
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Verificar ano bissexto
    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) {
        diasPorMes[1] = 29;
    }
    
    return dia <= diasPorMes[mes - 1];
}

bool Data::operator<(const Data& outra) const {
    if (ano != outra.ano) return ano < outra.ano;
    if (mes != outra.mes) return mes < outra.mes;
    return dia < outra.dia;
}

bool Data::operator==(const Data& outra) const {
    return (dia == outra.dia && mes == outra.mes && ano == outra.ano);
}

void Data::exibir() const {
    std::cout << std::setfill('0') << std::setw(2) << dia << "/"
              << std::setfill('0') << std::setw(2) << mes << "/"
              << ano;
}

std::string Data::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << dia << "/"
        << std::setfill('0') << std::setw(2) << mes << "/"
        << ano;
    return oss.str();
}

// Implementação da struct Estadia
Estadia::Estadia() {
    codigoEstadia = 0;
    codigoCliente = 0;
    numeroQuarto = 0;
    quantidadeHospedes = 0;
    quantidadeDiarias = 0;
    valorTotal = 0.0f;
}

Estadia::Estadia(int codEst, int codCli, int numQuarto, int qtdHosp, 
                const Data& entrada, const Data& saida) {
    codigoEstadia = codEst;
    codigoCliente = codCli;
    numeroQuarto = numQuarto;
    quantidadeHospedes = qtdHosp;
    dataEntrada = entrada;
    dataSaida = saida;
    quantidadeDiarias = 0;
    valorTotal = 0.0f;
}

void Estadia::serialize(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(this), sizeof(Estadia));
}

void Estadia::deserialize(std::ifstream& file) {
    file.read(reinterpret_cast<char*>(this), sizeof(Estadia));
}

void Estadia::exibir() const {
    std::cout << "Código da estadia: " << codigoEstadia << "\n";
    std::cout << "Código do cliente: " << codigoCliente << "\n";
    std::cout << "Número do quarto: " << numeroQuarto << "\n";
    std::cout << "Quantidade de hóspedes: " << quantidadeHospedes << "\n";
    std::cout << "Data de entrada: ";
    dataEntrada.exibir();
    std::cout << "\nData de saída: ";
    dataSaida.exibir();
    std::cout << "\nQuantidade de diárias: " << quantidadeDiarias << "\n";
    std::cout << "Valor total: R$ " << std::fixed << std::setprecision(2) << valorTotal << "\n";
}

bool Estadia::validar() const {
    if (codigoEstadia <= 0) return false;
    if (codigoCliente <= 0) return false;
    if (numeroQuarto <= 0) return false;
    if (quantidadeHospedes <= 0) return false;
    if (!dataEntrada.validar()) return false;
    if (!dataSaida.validar()) return false;
    if (dataSaida < dataEntrada || dataSaida == dataEntrada) return false;
    if (quantidadeDiarias <= 0) return false;
    if (valorTotal <= 0) return false;
    return true;
}

void Estadia::calcularDiariasEValor(float valorDiaria) {
    quantidadeDiarias = calcularDiarias(dataEntrada, dataSaida);
    valorTotal = quantidadeDiarias * valorDiaria;
}

// Funções auxiliares para datas
bool dataValida(int dia, int mes, int ano) {
    Data data(dia, mes, ano);
    return data.validar();
}

Data lerData(const std::string& prompt) {
    int dia, mes, ano;
    
    while (true) {
        std::cout << prompt;
        dia = lerInteiroPositivo("Dia: ");
        mes = lerInteiroPositivo("Mês: ");
        ano = lerInteiroPositivo("Ano: ");
        
        Data data(dia, mes, ano);
        if (data.validar()) {
            return data;
        }
        
        exibirMensagem("Data inválida. Tente novamente.", true);
    }
}

int calcularDiarias(const Data& entrada, const Data& saida) {
    // Conversão simples para cálculo de dias
    // Considera check-in às 14h e check-out às 12h
    
    int diasEntrada = entrada.dia + (entrada.mes * 30) + (entrada.ano * 365);
    int diasSaida = saida.dia + (saida.mes * 30) + (saida.ano * 365);
    
    int diferenca = diasSaida - diasEntrada;
    
    // Mínimo de 1 diária
    return (diferenca > 0) ? diferenca : 1;
}

// Função para obter próximo código de estadia
int obterProximoCodigoEstadia() {
    std::ifstream arquivo(ARQUIVO_ESTADIAS, std::ios::binary);
    if (!arquivo.is_open()) {
        return 1; // Primeira estadia
    }
    
    int maiorCodigo = 0;
    Estadia estadia;
    
    while (arquivo.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        if (estadia.codigoEstadia > maiorCodigo) {
            maiorCodigo = estadia.codigoEstadia;
        }
    }
    
    arquivo.close();
    return maiorCodigo + 1;
}

// Função para verificar se estadia existe
bool estadiaExiste(int codigo) {
    std::ifstream arquivo(ARQUIVO_ESTADIAS, std::ios::binary);
    if (!arquivo.is_open()) {
        return false;
    }
    
    Estadia estadia;
    while (arquivo.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        if (estadia.codigoEstadia == codigo) {
            arquivo.close();
            return true;
        }
    }
    
    arquivo.close();
    return false;
}

// Função para buscar estadia
Estadia buscarEstadia(int codigo) {
    Estadia estadia;
    std::ifstream arquivo(ARQUIVO_ESTADIAS, std::ios::binary);
    
    if (!arquivo.is_open()) {
        return estadia; // Retorna estadia vazia
    }
    
    while (arquivo.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        if (estadia.codigoEstadia == codigo) {
            arquivo.close();
            return estadia;
        }
    }
    
    arquivo.close();
    return Estadia(); // Retorna estadia vazia se não encontrar
}

// Função para listar estadias
void listarEstadias() {
    exibirCabecalho("LISTA DE ESTADIAS CADASTRADAS");
    
    std::ifstream arquivo(ARQUIVO_ESTADIAS, std::ios::binary);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo de estadias.", true);
        pausar();
        return;
    }
    
    Estadia estadia;
    bool encontrouEstadias = false;
    int contador = 0;
    float faturamentoTotal = 0.0f;
    int totalDiarias = 0;
    
    // Cabeçalho da tabela
    std::cout << std::left << std::setw(6) << "Cód" 
              << std::setw(8) << "Cliente" 
              << std::setw(8) << "Quarto"
              << std::setw(8) << "Hósp."
              << std::setw(12) << "Entrada"
              << std::setw(12) << "Saída"
              << std::setw(6) << "Diár."
              << std::setw(12) << "Valor Total" << "\n";
    std::cout << std::string(72, '=') << "\n";
    
    while (arquivo.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        if (estadia.validar()) {
            contador++;
            faturamentoTotal += estadia.valorTotal;
            totalDiarias += estadia.quantidadeDiarias;
            
            std::cout << std::left << std::setw(6) << estadia.codigoEstadia
                      << std::setw(8) << estadia.codigoCliente
                      << std::setw(8) << estadia.numeroQuarto
                      << std::setw(8) << estadia.quantidadeHospedes
                      << std::setw(12) << estadia.dataEntrada.toString()
                      << std::setw(12) << estadia.dataSaida.toString()
                      << std::setw(6) << estadia.quantidadeDiarias
                      << "R$ " << std::fixed << std::setprecision(2) 
                      << estadia.valorTotal << "\n";
            
            // Mostrar nome do cliente
            Cliente cliente = buscarCliente(estadia.codigoCliente);
            if (cliente.validar()) {
                std::cout << "      👤 Cliente: " << cliente.nome << "\n";
            }
            std::cout << "\n";
            
            encontrouEstadias = true;
        }
    }
    
    arquivo.close();
    
    if (!encontrouEstadias) {
        std::cout << "\n🏨 Nenhuma estadia cadastrada no sistema.\n";
        std::cout << "💡 Use a opção 4 do menu principal para cadastrar estadias.\n";
    } else {
        std::cout << std::string(72, '=') << "\n";
        std::cout << "📊 ESTATÍSTICAS DAS ESTADIAS:\n";
        std::cout << "🏨 Total de estadias: " << contador << "\n";
        std::cout << "🛏️  Total de diárias vendidas: " << totalDiarias << "\n";
        std::cout << "💰 Faturamento total: R$ " << std::fixed 
                  << std::setprecision(2) << faturamentoTotal << "\n";
        std::cout << "📈 Valor médio por estadia: R$ " << std::fixed 
                  << std::setprecision(2) << (faturamentoTotal / contador) << "\n";
        std::cout << "📊 Média de diárias por estadia: " << std::fixed 
                  << std::setprecision(1) << ((float)totalDiarias / contador) << "\n";
    }
    
    pausar();
}

// Função principal para cadastrar estadia
int cadastrarEstadia() {
    exibirCabecalho("CADASTRO DE ESTADIA");
    
    // 1. Verificar se existe pelo menos um cliente
    std::ifstream arquivoClientes(ARQUIVO_CLIENTES, std::ios::binary);
    if (!arquivoClientes.is_open()) {
        exibirMensagem("Erro ao acessar arquivo de clientes.", true);
        pausar();
        return -1;
    }
    
    Cliente clienteTeste;
    bool existeCliente = false;
    while (arquivoClientes.read(reinterpret_cast<char*>(&clienteTeste), sizeof(Cliente))) {
        if (clienteTeste.validar()) {
            existeCliente = true;
            break;
        }
    }
    arquivoClientes.close();
    
    if (!existeCliente) {
        exibirMensagem("Não há clientes cadastrados. Cadastre um cliente primeiro.", true);
        pausar();
        return -1;
    }
    
    // 2. Obter código da estadia
    int codigoEstadia = obterProximoCodigoEstadia();
    std::cout << "Código da estadia: " << codigoEstadia << " (gerado automaticamente)\n\n";
    
    // 3. Ler e validar código do cliente
    int codigoCliente;
    while (true) {
        codigoCliente = lerInteiroPositivo("Código do cliente: ");
        if (clienteExiste(codigoCliente)) {
            Cliente cliente = buscarCliente(codigoCliente);
            std::cout << "Cliente encontrado: " << cliente.nome << "\n\n";
            break;
        }
        exibirMensagem("Cliente não encontrado. Tente novamente.", true);
    }
    
    // 4. Ler quantidade de hóspedes
    int quantidadeHospedes = lerInteiroPositivo("Quantidade de hóspedes: ");
    
    // 5. Ler datas
    std::cout << "\n--- DATA DE ENTRADA ---\n";
    Data dataEntrada = lerData("");
    
    std::cout << "\n--- DATA DE SAÍDA ---\n";
    Data dataSaida;
    while (true) {
        dataSaida = lerData("");
        if (dataSaida < dataEntrada || dataSaida == dataEntrada) {
            exibirMensagem("Data de saída deve ser posterior à data de entrada.", true);
        } else {
            break;
        }
    }
    
    // 6. Buscar quarto disponível
    std::cout << "\nBuscando quarto disponível...\n";
    Quarto quarto = buscarQuartoDisponivel(quantidadeHospedes);
    
    if (quarto.numero == 0 || !quarto.validar()) {
        exibirMensagem("Não há quartos disponíveis com capacidade adequada.", true);
        pausar();
        return -1;
    }
    
    std::cout << "Quarto encontrado:\n";
    std::cout << "----------------------------------------\n";
    quarto.exibir();
    std::cout << "----------------------------------------\n";
    
    // 7. Criar estadia
    Estadia estadia(codigoEstadia, codigoCliente, quarto.numero, 
                   quantidadeHospedes, dataEntrada, dataSaida);
    
    // 8. Calcular diárias e valor total
    estadia.calcularDiariasEValor(quarto.valorDiaria);
    
    // 9. Validar estadia
    if (!estadia.validar()) {
        exibirMensagem("Dados da estadia inválidos.", true);
        pausar();
        return -1;
    }
    
    // 10. Salvar estadia
    std::ofstream arquivo(ARQUIVO_ESTADIAS, std::ios::binary | std::ios::app);
    if (!arquivo.is_open()) {
        exibirMensagem("Erro ao abrir arquivo para salvar estadia.", true);
        pausar();
        return -1;
    }
    
    estadia.serialize(arquivo);
    arquivo.close();
    
    // 11. Atualizar status do quarto para ocupado
    if (!atualizarStatusQuarto(quarto.numero, OCUPADO)) {
        exibirMensagem("Estadia salva, mas erro ao atualizar status do quarto.", true);
    }
    
    // 12. Exibir resultado
    exibirMensagem("Estadia cadastrada com sucesso!");
    std::cout << "\nResumo da estadia:\n";
    std::cout << "========================================\n";
    estadia.exibir();
    
    pausar();
    return codigoEstadia;
}