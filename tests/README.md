# Testes Automatizados - Sistema Hotel Descanso Garantido

## 🧪 Como Executar

### **Método Recomendado:**
```bash
cd tests
./executar_testes.sh    # Linux/macOS
executar_testes.bat     # Windows
```

### **Método Manual:**
```bash
# A partir da pasta raiz do projeto
clang++ -std=c++11 -Wall -Wextra -O2 -o testes tests/main_testes.cpp tests/testes.cpp src/*.cpp -I include/
./testes
```

## 📊 Testes Implementados (15 total)

### **Testes de Arquivo:**
1. **Inicialização de Arquivos** - Criação dos arquivos .dat
2. **Integridade de Arquivos** - Verificação de consistência

### **Testes de Cadastro:**
3. **Cadastro de Cliente** - Persistência e recuperação
4. **Cadastro de Funcionário** - Persistência e recuperação
5. **Cadastro de Quarto** - Persistência e recuperação
6. **Cadastro de Estadia** - Persistência e recuperação

### **Testes de Validação:**
7. **Validação de Cliente** - Regras de negócio
8. **Validação de Funcionário** - Regras de negócio
9. **Validação de Quarto** - Regras de negócio
10. **Validação de Estadia** - Regras de negócio

### **Testes de Busca:**
11. **Busca de Cliente** - Localização em arquivo
12. **Busca de Quarto** - Localização em arquivo

### **Testes de Operações:**
13. **Atualização de Status** - Modificação de quartos
14. **Cálculo de Diárias** - Algoritmo de datas
15. **Serialização** - Conversão binária

## 📄 Relatórios

- **Localização:** `tests/relatorios/relatorio-testes.md`
- **Formato:** Markdown com tabelas
- **Conteúdo:** Resumo, detalhes e conclusões
- **Métricas:** Taxa de sucesso e tempo de execução

## ⚠️ Observações Importantes

- **Limpeza de dados:** Os testes removem arquivos existentes
- **Execução:** Deve ser feita a partir da pasta `tests/`
- **Dependências:** Requer compilador C++11
- **Plataforma:** Funciona em Windows, macOS e Linux

## 🔧 Solução de Problemas

**Erro de compilação:**
```bash
# Verificar se está na pasta tests/
pwd
ls -la

# Verificar estrutura do projeto
ls -la ../src/
ls -la ../include/
```

**Arquivos não encontrados:**
```bash
# Executar a partir da pasta tests/
cd tests
./executar_testes.sh
```