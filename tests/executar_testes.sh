#!/bin/bash

echo " SISTEMA DE TESTES AUTOMATIZADOS"
echo "=================================="
echo ""

# Verificar se estamos na pasta tests
if [ ! -f "testes.cpp" ]; then
    echo "Execute este script da pasta tests/"
    echo "   cd tests && ./executar_testes.sh"
    exit 1
fi

# Voltar para a pasta raiz do projeto para compilar e executar
cd ..

# Verificar se estamos na pasta raiz correta
if [ ! -f "src/main.cpp" ]; then
    echo "Estrutura de projeto incorreta!"
    echo "   Certifique-se de estar na pasta raiz do projeto"
    exit 1
fi

# Criar diretório de relatórios se não existir
mkdir -p tests/relatorios

# Compilar programa de testes
echo "Compilando programa de testes..."
clang++ -std=c++11 -Wall -Wextra -O2 -o testes \
    tests/main_testes.cpp \
    tests/testes.cpp \
    src/cliente.cpp \
    src/funcionario.cpp \
    src/quarto.cpp \
    src/estadia.cpp \
    src/utils.cpp \
    -I include/

if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida!"
    echo ""
    
    # Executar testes
    echo "Executando testes..."
    echo ""
    ./testes
    
    # Limpar executável de testes
    rm -f testes
    
    echo ""
    echo "Testes concluídos!"
    
    # Verificar se relatório foi gerado
    if [ -f "tests/relatorios/relatorio-testes.md" ]; then
        echo "Relatório disponível em: tests/relatorios/relatorio-testes.md"
    fi
    
else
    echo "Erro na compilação!"
    exit 1
fi
