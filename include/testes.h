#ifndef TESTES_H
#define TESTES_H

#include <string>
#include <vector>

// Estrutura para armazenar resultado de um teste
struct ResultadoTeste {
    std::string nome;
    bool passou;
    std::string mensagem;
    double tempoExecucao;
};

// Classe para gerenciar testes
class GerenciadorTestes {
private:
    std::vector<ResultadoTeste> resultados;
    int testesPassaram;
    int testesFalharam;
    
public:
    GerenciadorTestes();
    
    // Executar um teste individual
    void executarTeste(const std::string& nome, bool (*funcaoTeste)(), const std::string& descricao = "");
    
    // Funções auxiliares para validação
    bool validarArquivo(const std::string& nomeArquivo);
    bool validarRegistro(const std::string& tipo, int codigo);
    
    // Relatório final
    void gerarRelatorio();
    void salvarRelatorio(const std::string& nomeArquivo);
    
    // Limpeza
    void limparArquivosTeste();
    void prepararAmbienteTeste();
};

// Macros para facilitar os testes
#define ASSERT_TRUE(condicao, mensagem) \
    if (!(condicao)) { \
        std::cout << "FALHOU: " << mensagem << std::endl; \
        return false; \
    }

#define ASSERT_FALSE(condicao, mensagem) \
    if (condicao) { \
        std::cout << "FALHOU: " << mensagem << std::endl; \
        return false; \
    }

#define ASSERT_EQUAL(esperado, atual, mensagem) \
    if ((esperado) != (atual)) { \
        std::cout << "FALHOU: " << mensagem << " (Esperado: " << esperado << ", Atual: " << atual << ")" << std::endl; \
        return false; \
    }

// Declarações das funções de teste
bool testeInicializacaoArquivos();
bool testeCadastroCliente();
bool testeCadastroFuncionario();
bool testeCadastroQuarto();
bool testeCadastroEstadia();
bool testeValidacaoCliente();
bool testeValidacaoFuncionario();
bool testeValidacaoQuarto();
bool testeValidacaoEstadia();
bool testeBuscaCliente();
bool testeBuscaQuarto();
bool testeAtualizacaoStatusQuarto();
bool testeCalculoDiarias();
bool testeSerializacao();
bool testeIntegridadeArquivos();

// Função principal para executar todos os testes
void executarTodosTestes();

#endif
