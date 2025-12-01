@echo off
echo  SISTEMA DE TESTES AUTOMATIZADOS
echo ==================================
echo.

REM Verificar se estamos na pasta tests
if not exist "testes.cpp" (
    echo Execute este script da pasta tests/
    echo    cd tests && executar_testes.bat
    pause
    exit /b 1
)

REM Voltar para a pasta raiz do projeto
cd ..

REM Verificar se estamos na pasta raiz correta
if not exist "src\main.cpp" (
    echo Estrutura de projeto incorreta!
    echo    Certifique-se de estar na pasta raiz do projeto
    pause
    exit /b 1
)

REM Criar diretório de relatórios se não existir
if not exist "tests\relatorios" mkdir tests\relatorios

REM Compilar programa de testes
echo Compilando programa de testes...
g++ -std=c++11 -Wall -Wextra -O2 -o testes.exe tests/main_testes.cpp tests/testes.cpp src/cliente.cpp src/funcionario.cpp src/quarto.cpp src/estadia.cpp src/utils.cpp -I include/

if %errorlevel% equ 0 (
    echo Compilação bem-sucedida!
    echo.
    
    REM Executar testes
    echo Executando testes...
    echo.
    testes.exe
    
    REM Limpar executável de testes
    del testes.exe
    
    echo.
    echo Testes concluídos!
    
    REM Verificar se relatório foi gerado
    if exist "tests\relatorios\relatorio-testes.md" (
        echo Relatório disponível em: tests\relatorios\relatorio-testes.md
    )
    
) else (
    echo Erro na compilação!
    pause
    exit /b 1
)

pause
