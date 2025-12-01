#include "../include/testes.h"
#include "../include/cliente.h"
#include "../include/funcionario.h"
#include "../include/quarto.h"
#include "../include/estadia.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdio>
#include <iomanip>

// Implementação do GerenciadorTestes
GerenciadorTestes::GerenciadorTestes() {
    testesPassaram = 0;
    testesFalharam = 0;
}

void GerenciadorTestes::executarTeste(const std::string& nome, bool (*funcaoTeste)(), const std::string& descricao) {
    std::cout << "Executando: " << nome << std::endl;
    if (!descricao.empty()) {
        std::cout << "   " << descricao << std::endl;
    }
    
    auto inicio = std::chrono::high_resolution_clock::now();
    
    bool resultado = funcaoTeste();
    
    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);
    double tempoMs = duracao.count() / 1000.0;
    
    ResultadoTeste res;
    res.nome = nome;
    res.passou = resultado;
    res.tempoExecucao = tempoMs;
    
    if (resultado) {
        res.mensagem = " PASSOU";
        testesPassaram++;
        std::cout << "   PASSOU (" << std::fixed << std::setprecision(2) << tempoMs << "ms)" << std::endl;
    } else {
        res.mensagem = " FALHOU";
        testesFalharam++;
        std::cout << "   FALHOU (" << std::fixed << std::setprecision(2) << tempoMs << "ms)" << std::endl;
    }
    
    resultados.push_back(res);
    std::cout << std::endl;
}

bool GerenciadorTestes::validarArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    return arquivo.good();
}

bool GerenciadorTestes::validarRegistro(const std::string& tipo, int codigo) {
    if (tipo == "cliente") {
        return clienteExiste(codigo);
    } else if (tipo == "funcionario") {
        return funcionarioExiste(codigo);
    } else if (tipo == "quarto") {
        return quartoExiste(codigo);
    } else if (tipo == "estadia") {
        return estadiaExiste(codigo);
    }
    return false;
}

void GerenciadorTestes::limparArquivosTeste() {
    // Limpar arquivos de dados (caminhos corretos para execução a partir da pasta tests)
    remove("data/clientes.dat");
    remove("data/funcionarios.dat");
    remove("data/quartos.dat");
    remove("data/estadias.dat");
}

void GerenciadorTestes::prepararAmbienteTeste() {
    limparArquivosTeste();
    inicializarArquivos();
}

void GerenciadorTestes::gerarRelatorio() {
    std::cout << "========================================" << std::endl;
    std::cout << "         RELATÓRIO DE TESTES" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int total = testesPassaram + testesFalharam;
    double percentualSucesso = (total > 0) ? (double)testesPassaram / total * 100.0 : 0.0;
    
    std::cout << "RESUMO:" << std::endl;
    std::cout << "   Total de testes: " << total << std::endl;
    std::cout << "   Passaram: " << testesPassaram << std::endl;
    std::cout << "   Falharam: " << testesFalharam << std::endl;
    std::cout << "   Taxa de sucesso: " << std::fixed << std::setprecision(1) 
              << percentualSucesso << "%" << std::endl;
    
    std::cout << "\n DETALHES:" << std::endl;
    for (const auto& resultado : resultados) {
        std::cout << "   " << (resultado.passou ? "✅" : "❌") 
                  << " " << resultado.nome 
                  << " (" << std::fixed << std::setprecision(2) 
                  << resultado.tempoExecucao << "ms)" << std::endl;
    }
    
    std::cout << "\n" << (testesFalharam == 0 ? " TODOS OS TESTES PASSARAM!" : "  ALGUNS TESTES FALHARAM!") << std::endl;
    std::cout << "========================================" << std::endl;
}

void GerenciadorTestes::salvarRelatorio(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) return;
    
    arquivo << "# RELATÓRIO DE TESTES - SISTEMA HOTEL DESCANSO GARANTIDO\n\n";
    arquivo << "**Data:** " << __DATE__ << " " << __TIME__ << "\n\n";
    
    int total = testesPassaram + testesFalharam;
    double percentualSucesso = (total > 0) ? (double)testesPassaram / total * 100.0 : 0.0;
    
    arquivo << "## RESUMO\n\n";
    arquivo << "- **Total de testes:** " << total << "\n";
    arquivo << "- **Passaram:** " << testesPassaram << "\n";
    arquivo << "- **Falharam:** " << testesFalharam << "\n";
    arquivo << "- **Taxa de sucesso:** " << std::fixed << std::setprecision(1) 
            << percentualSucesso << "%\n\n";
    
    arquivo << "## DETALHES DOS TESTES\n\n";
    arquivo << "| Teste | Status | Tempo (ms) |\n";
    arquivo << "|-------|--------|------------|\n";
    
    for (const auto& resultado : resultados) {
        arquivo << "| " << resultado.nome 
                << " | " << (resultado.passou ? "✅ PASSOU" : "❌ FALHOU")
                << " | " << std::fixed << std::setprecision(2) 
                << resultado.tempoExecucao << " |\n";
    }
    
    arquivo << "\n## CONCLUSÃO\n\n";
    if (testesFalharam == 0) {
        arquivo << " **TODOS OS TESTES PASSARAM!**\n\n";
        arquivo << "O sistema está funcionando corretamente e atende a todos os requisitos testados.\n";
    } else {
        arquivo << " **ALGUNS TESTES FALHARAM**\n\n";
        arquivo << "Verifique os testes que falharam e corrija os problemas antes de prosseguir.\n";
    }
    
    arquivo.close();
}

// Implementação dos testes individuais

bool testeInicializacaoArquivos() {
    GerenciadorTestes gerenciador;
    gerenciador.prepararAmbienteTeste();
    
    ASSERT_TRUE(gerenciador.validarArquivo("data/clientes.dat"), "Arquivo de clientes não foi criado");
    ASSERT_TRUE(gerenciador.validarArquivo("data/funcionarios.dat"), "Arquivo de funcionários não foi criado");
    ASSERT_TRUE(gerenciador.validarArquivo("data/quartos.dat"), "Arquivo de quartos não foi criado");
    ASSERT_TRUE(gerenciador.validarArquivo("data/estadias.dat"), "Arquivo de estadias não foi criado");
    
    return true;
}

bool testeCadastroCliente() {
    // Criar cliente de teste
    Cliente cliente(1, "João Silva", "Rua A, 123", "11999999999");
    
    // Salvar no arquivo
    std::ofstream arquivo("data/clientes.dat", std::ios::binary | std::ios::app);
    ASSERT_TRUE(arquivo.is_open(), "Não foi possível abrir arquivo de clientes");
    
    cliente.serialize(arquivo);
    arquivo.close();
    
    // Verificar se foi salvo
    ASSERT_TRUE(clienteExiste(1), "Cliente não foi encontrado após cadastro");
    
    // Buscar e validar dados
    Cliente clienteBuscado = buscarCliente(1);
    ASSERT_EQUAL(1, clienteBuscado.codigo, "Código do cliente incorreto");
    ASSERT_TRUE(std::string(clienteBuscado.nome) == "João Silva", "Nome do cliente incorreto");
    
    return true;
}

bool testeCadastroFuncionario() {
    // Criar funcionário de teste
    Funcionario funcionario(1, "Maria Santos", "11888888888", "Recepcionista", 2500.00f);
    
    // Salvar no arquivo
    std::ofstream arquivo("data/funcionarios.dat", std::ios::binary | std::ios::app);
    ASSERT_TRUE(arquivo.is_open(), "Não foi possível abrir arquivo de funcionários");
    
    funcionario.serialize(arquivo);
    arquivo.close();
    
    // Verificar se foi salvo
    ASSERT_TRUE(funcionarioExiste(1), "Funcionário não foi encontrado após cadastro");
    
    // Buscar e validar dados
    Funcionario funcionarioBuscado = buscarFuncionario(1);
    ASSERT_EQUAL(1, funcionarioBuscado.codigo, "Código do funcionário incorreto");
    ASSERT_TRUE(funcionarioBuscado.salario == 2500.00f, "Salário do funcionário incorreto");
    
    return true;
}

bool testeCadastroQuarto() {
    // Criar quarto de teste
    Quarto quarto(101, 2, 150.00f);
    
    // Salvar no arquivo
    std::ofstream arquivo("data/quartos.dat", std::ios::binary | std::ios::app);
    ASSERT_TRUE(arquivo.is_open(), "Não foi possível abrir arquivo de quartos");
    
    quarto.serialize(arquivo);
    arquivo.close();
    
    // Verificar se foi salvo
    ASSERT_TRUE(quartoExiste(101), "Quarto não foi encontrado após cadastro");
    
    // Buscar e validar dados
    Quarto quartoBuscado = buscarQuarto(101);
    ASSERT_EQUAL(101, quartoBuscado.numero, "Número do quarto incorreto");
    ASSERT_EQUAL(DESOCUPADO, quartoBuscado.status, "Status inicial do quarto deve ser DESOCUPADO");
    
    return true;
}

bool testeCadastroEstadia() {
    // Primeiro, garantir que existe cliente e quarto
    testeCadastroCliente();
    testeCadastroQuarto();
    
    // Criar estadia de teste
    Data entrada(15, 12, 2024);
    Data saida(17, 12, 2024);
    Estadia estadia(1, 1, 101, 2, entrada, saida);
    estadia.calcularDiariasEValor(150.00f);
    
    // Salvar no arquivo
    std::ofstream arquivo("data/estadias.dat", std::ios::binary | std::ios::app);
    ASSERT_TRUE(arquivo.is_open(), "Não foi possível abrir arquivo de estadias");
    
    estadia.serialize(arquivo);
    arquivo.close();
    
    // Verificar se foi salvo
    ASSERT_TRUE(estadiaExiste(1), "Estadia não foi encontrada após cadastro");
    
    // Buscar e validar dados
    Estadia estadiaBuscada = buscarEstadia(1);
    ASSERT_EQUAL(1, estadiaBuscada.codigoEstadia, "Código da estadia incorreto");
    ASSERT_TRUE(estadiaBuscada.quantidadeDiarias > 0, "Quantidade de diárias deve ser maior que zero");
    
    return true;
}

bool testeValidacaoCliente() {
    Cliente clienteValido(1, "João", "Rua A", "123456789");
    Cliente clienteInvalido; // Construtor padrão cria cliente inválido
    
    ASSERT_TRUE(clienteValido.validar(), "Cliente válido não passou na validação");
    ASSERT_FALSE(clienteInvalido.validar(), "Cliente inválido passou na validação");
    
    return true;
}

bool testeValidacaoFuncionario() {
    Funcionario funcionarioValido(1, "Maria", "123456789", "Recepcionista", 2000.0f);
    Funcionario funcionarioInvalido; // Construtor padrão cria funcionário inválido
    
    ASSERT_TRUE(funcionarioValido.validar(), "Funcionário válido não passou na validação");
    ASSERT_FALSE(funcionarioInvalido.validar(), "Funcionário inválido passou na validação");
    
    return true;
}

bool testeValidacaoQuarto() {
    Quarto quartoValido(101, 2, 150.0f);
    Quarto quartoInvalido; // Construtor padrão cria quarto inválido
    
    ASSERT_TRUE(quartoValido.validar(), "Quarto válido não passou na validação");
    ASSERT_FALSE(quartoInvalido.validar(), "Quarto inválido passou na validação");
    
    return true;
}

bool testeValidacaoEstadia() {
    Data entrada(15, 12, 2024);
    Data saida(17, 12, 2024);
    Data entradaInvalida(32, 13, 2025); // Data inválida
    
    Estadia estadiaValida(1, 1, 101, 2, entrada, saida);
    estadiaValida.calcularDiariasEValor(150.0f);
    
    Estadia estadiaInvalida(1, 1, 101, 2, entradaInvalida, saida);
    
    ASSERT_TRUE(estadiaValida.validar(), "Estadia válida não passou na validação");
    ASSERT_FALSE(estadiaInvalida.validar(), "Estadia inválida passou na validação");
    
    return true;
}

bool testeBuscaCliente() {
    testeCadastroCliente(); // Garantir que existe cliente
    
    Cliente cliente = buscarCliente(1);
    ASSERT_TRUE(cliente.validar(), "Cliente buscado é inválido");
    ASSERT_EQUAL(1, cliente.codigo, "Código do cliente buscado incorreto");
    
    Cliente clienteInexistente = buscarCliente(999);
    ASSERT_FALSE(clienteInexistente.validar(), "Busca por cliente inexistente deveria retornar cliente inválido");
    
    return true;
}

bool testeBuscaQuarto() {
    testeCadastroQuarto(); // Garantir que existe quarto
    
    Quarto quarto = buscarQuarto(101);
    ASSERT_TRUE(quarto.validar(), "Quarto buscado é inválido");
    ASSERT_EQUAL(101, quarto.numero, "Número do quarto buscado incorreto");
    
    Quarto quartoInexistente = buscarQuarto(999);
    ASSERT_FALSE(quartoInexistente.validar(), "Busca por quarto inexistente deveria retornar quarto inválido");
    
    return true;
}

bool testeAtualizacaoStatusQuarto() {
    testeCadastroQuarto(); // Garantir que existe quarto
    
    // Testar ocupação
    ASSERT_TRUE(atualizarStatusQuarto(101, OCUPADO), "Falha ao ocupar quarto");
    
    Quarto quarto = buscarQuarto(101);
    ASSERT_EQUAL(OCUPADO, quarto.status, "Status do quarto não foi atualizado para OCUPADO");
    
    // Testar desocupação
    ASSERT_TRUE(atualizarStatusQuarto(101, DESOCUPADO), "Falha ao desocupar quarto");
    
    quarto = buscarQuarto(101);
    ASSERT_EQUAL(DESOCUPADO, quarto.status, "Status do quarto não foi atualizado para DESOCUPADO");
    
    return true;
}

bool testeCalculoDiarias() {
    Data entrada(15, 12, 2024);
    Data saida(17, 12, 2024);
    
    int diarias = calcularDiarias(entrada, saida);
    ASSERT_TRUE(diarias > 0, "Cálculo de diárias deve retornar valor positivo");
    
    // Teste com datas iguais (mínimo 1 diária)
    Data mesmaData(15, 12, 2024);
    int diariasMinimas = calcularDiarias(mesmaData, mesmaData);
    ASSERT_EQUAL(1, diariasMinimas, "Datas iguais devem resultar em 1 diária");
    
    return true;
}

bool testeSerializacao() {
    // Teste de serialização/deserialização de cliente
    Cliente clienteOriginal(1, "Teste", "Endereço Teste", "123456789");
    
    // Salvar
    std::ofstream arquivoSaida("test_temp.dat", std::ios::binary);
    clienteOriginal.serialize(arquivoSaida);
    arquivoSaida.close();
    
    // Carregar
    Cliente clienteCarregado;
    std::ifstream arquivoEntrada("test_temp.dat", std::ios::binary);
    clienteCarregado.deserialize(arquivoEntrada);
    arquivoEntrada.close();
    
    // Verificar
    ASSERT_EQUAL(clienteOriginal.codigo, clienteCarregado.codigo, "Código não foi serializado corretamente");
    ASSERT_TRUE(std::string(clienteOriginal.nome) == std::string(clienteCarregado.nome), "Nome não foi serializado corretamente");
    
    // Limpar arquivo temporário
    remove("test_temp.dat");
    
    return true;
}

bool testeIntegridadeArquivos() {
    GerenciadorTestes gerenciador;
    gerenciador.prepararAmbienteTeste();
    
    // Cadastrar alguns registros
    testeCadastroCliente();
    testeCadastroFuncionario();
    testeCadastroQuarto();
    
    // Verificar integridade
    ASSERT_TRUE(clienteExiste(1), "Integridade do arquivo de clientes comprometida");
    ASSERT_TRUE(funcionarioExiste(1), "Integridade do arquivo de funcionários comprometida");
    ASSERT_TRUE(quartoExiste(101), "Integridade do arquivo de quartos comprometida");
    
    return true;
}

// Função principal para executar todos os testes
void executarTodosTestes() {
    std::cout << "INICIANDO TESTES AUTOMATIZADOS" << std::endl;
    std::cout << "========================================" << std::endl;
    
    GerenciadorTestes gerenciador;
    gerenciador.prepararAmbienteTeste();
    
    // Executar todos os testes
    gerenciador.executarTeste("Inicialização de Arquivos", testeInicializacaoArquivos, "Verifica se os arquivos de dados são criados corretamente");
    gerenciador.executarTeste("Cadastro de Cliente", testeCadastroCliente, "Testa o cadastro e persistência de clientes");
    gerenciador.executarTeste("Cadastro de Funcionário", testeCadastroFuncionario, "Testa o cadastro e persistência de funcionários");
    gerenciador.executarTeste("Cadastro de Quarto", testeCadastroQuarto, "Testa o cadastro e persistência de quartos");
    gerenciador.executarTeste("Cadastro de Estadia", testeCadastroEstadia, "Testa o cadastro e persistência de estadias");
    gerenciador.executarTeste("Validação de Cliente", testeValidacaoCliente, "Testa as regras de validação de clientes");
    gerenciador.executarTeste("Validação de Funcionário", testeValidacaoFuncionario, "Testa as regras de validação de funcionários");
    gerenciador.executarTeste("Validação de Quarto", testeValidacaoQuarto, "Testa as regras de validação de quartos");
    gerenciador.executarTeste("Validação de Estadia", testeValidacaoEstadia, "Testa as regras de validação de estadias");
    gerenciador.executarTeste("Busca de Cliente", testeBuscaCliente, "Testa a busca de clientes no arquivo");
    gerenciador.executarTeste("Busca de Quarto", testeBuscaQuarto, "Testa a busca de quartos no arquivo");
    gerenciador.executarTeste("Atualização de Status", testeAtualizacaoStatusQuarto, "Testa a atualização de status dos quartos");
    gerenciador.executarTeste("Cálculo de Diárias", testeCalculoDiarias, "Testa o cálculo de diárias entre datas");
    gerenciador.executarTeste("Serialização", testeSerializacao, "Testa a serialização/deserialização de dados");
    gerenciador.executarTeste("Integridade de Arquivos", testeIntegridadeArquivos, "Verifica a integridade dos arquivos de dados");
    
    // Gerar relatório
    gerenciador.gerarRelatorio();
    gerenciador.salvarRelatorio("relatorios/relatorio-testes.md");
    
    std::cout << "\n Relatório salvo em: tests/relatorios/relatorio-testes.md" << std::endl;
}
