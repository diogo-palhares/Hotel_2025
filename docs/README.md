# Documentação Técnica

## 📋 Documentos Disponíveis

- [Arquitetura](arquitetura.md) - Estrutura do sistema
- [Funções](funcoes.md) - Referência das funções principais
- [Arquivos](arquivos.md) - Formato dos dados binários
- [Manual](manual.md) - Guia do usuário
- [Testes](testes.md) - Casos de teste

## 🎯 Visão Geral

Sistema de hotel em C++11 com:
- **4 entidades**: Cliente, Funcionário, Quarto, Estadia
- **Persistência**: Arquivos binários com acesso direto
- **Interface**: Menu textual
- **Testes**: 15 testes automatizados

## 🏗️ Arquitetura

```
Interface (main.cpp) 
    ↓
Módulos de Negócio (cliente.cpp, funcionario.cpp, quarto.cpp, estadia.cpp)
    ↓
Persistência (serialização binária)
    ↓
Arquivos (.dat)
```