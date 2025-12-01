#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>

// Funções de validação de entrada
int lerInteiro(const std::string& prompt);
int lerInteiroPositivo(const std::string& prompt);
float lerFloat(const std::string& prompt);
float lerFloatPositivo(const std::string& prompt);
std::string lerString(const std::string& prompt, int tamanhoMax);
std::string lerStringNaoVazia(const std::string& prompt, int tamanhoMax);

// Funções de manipulação de strings
void copiarString(char* destino, const std::string& origem, int tamanhoMax);
std::string trimString(const std::string& str);

// Funções de arquivo
bool arquivoExiste(const std::string& nomeArquivo);
bool criarDiretorio(const std::string& caminho);
void inicializarArquivos();

// Funções de interface
void limparTela();
void pausar();
void exibirCabecalho(const std::string& titulo);
void exibirMensagem(const std::string& mensagem, bool erro = false);

// Funções de menu
void exibirMenuPrincipal();
void exibirMenuListagem();
int lerOpcaoMenu(int minOpcao, int maxOpcao);

#endif