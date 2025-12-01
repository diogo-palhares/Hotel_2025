# Sistema Hotel Descanso Garantido

Sistema de gerenciamento de hotel desenvolvido em C++ com persistência em arquivos binários e acesso direto aos dados.

## 🚀 Funcionalidades

### Cadastros:
- ✅ Clientes (código automático)
- ✅ Funcionários (controle salarial)  
- ✅ Quartos (gestão de ocupação)
- ✅ Estadias (cálculo automático de diárias)

### Consultas:
- ✅ Listagem com estatísticas em tempo real
- ✅ Formatação tabular e indicadores visuais
- ✅ Relatórios de ocupação e faturamento

## 🔧 Compilação e Execução

### Compilar:
```bash
# macOS/Linux
clang++ -std=c++11 -Wall -Wextra -O2 -o hotel src/*.cpp -I include/

# Windows (MinGW)
g++ -std=c++11 -Wall -Wextra -O2 -o hotel.exe src/*.cpp -I include/
```

### Executar:
```bash
./hotel        # macOS/Linux
hotel.exe      # Windows
```

## 🧪 Testes Automatizados

```bash
cd tests
./executar_testes.sh    # Linux/macOS
executar_testes.bat     # Windows
```

**15 testes** cobrindo todas as funcionalidades principais.

## 📚 Documentação

- [Manual do Usuário](docs/manual.md) - Como usar o sistema
- [Arquitetura](docs/arquitetura.md) - Estrutura técnica
- [Funções](docs/funcoes.md) - Referência das funções
- [Arquivos](docs/arquivos.md) - Formato dos dados
- [Testes](docs/testes.md) - Casos de teste

## 📋 Pré-requisitos

| Sistema | Ferramenta | Instalação |
|---------|------------|------------|
| **macOS** | Xcode Command Line Tools | `xcode-select --install` |
| **Windows** | MinGW-w64 | [Download](https://www.mingw-w64.org/downloads/) |
| **Linux** | build-essential | `sudo apt install build-essential` |

## 🏗️ Estrutura

```
projeto-hotel/
├── src/           # Código fonte (.cpp)
├── include/       # Headers (.h)
├── data/          # Arquivos binários
├── tests/         # Testes automatizados
├── docs/          # Documentação técnica
└── README.md      # Este arquivo
```

## 🎯 Características Técnicas

- **Acesso direto** a arquivos binários
- **Registros de tamanho fixo** com `seekp()/seekg()`
- **Validações robustas** de entrada
- **Interface moderna** com menu organizado
- **Multiplataforma** (Windows/macOS/Linux)

## 🐛 Problemas Comuns

**Compilador não encontrado:**
```bash
# macOS: xcode-select --install
# Linux: sudo apt install build-essential
# Windows: Adicionar MinGW ao PATH
```

**Erro de permissão:**
```bash
chmod +x hotel
```