# Sistema Hotel Descanso Garantido

## Descrição
Sistema de gerenciamento de hotel com 4 funcionalidades principais:
1. Cadastro de Clientes
2. Cadastro de Funcionários  
3. Cadastro de Quartos
4. Cadastro de Estadias

## Estrutura do Projeto
```
projeto-hotel/
├── src/                    # Código fonte (.cpp)
├── include/               # Headers (.h)
├── data/                  # Arquivos de dados binários
├── docs/                  # Documentação
├── planejamento/          # Backlog e sprints
└── README.md             # Este arquivo
```

## Instalação e Configuração por Sistema Operacional

### 🍎 **macOS**

**Ferramentas necessárias:**
```bash
# Instalar Xcode Command Line Tools
xcode-select --install

# Verificar instalação
clang++ --version
```

**Compilação:**
```bash
clang++ -std=c++11 -Wall -Wextra -g -o hotel src/*.cpp -I include/
```

**Execução:**
```bash
./hotel
```

---

### 🪟 **Windows**

**Opção 1: MinGW-w64 (Recomendado)**
1. Baixar e instalar MinGW-w64: https://www.mingw-w64.org/downloads/
2. Ou instalar via MSYS2: https://www.msys2.org/
3. Adicionar ao PATH do sistema

**Verificar instalação:**
```cmd
g++ --version
```

**Compilação:**
```cmd
g++ -std=c++11 -Wall -Wextra -g -o hotel.exe src/*.cpp -I include/
```

**Execução:**
```cmd
hotel.exe
```

**Opção 2: Visual Studio Community (Alternativa)**
1. Instalar Visual Studio Community (gratuito)
2. Incluir "Desktop development with C++"
3. Usar Developer Command Prompt

**Compilação (Visual Studio):**
```cmd
cl /EHsc /std:c++11 /I include src/*.cpp /Fe:hotel.exe
```

---

### 🐧 **Linux (Ubuntu/Debian)**

**Ferramentas necessárias:**
```bash
# Instalar build essentials
sudo apt update
sudo apt install build-essential

# Verificar instalação
g++ --version
```

**Compilação:**
```bash
g++ -std=c++11 -Wall -Wextra -g -o hotel src/*.cpp -I include/
```

**Execução:**
```bash
./hotel
```

---

## Comandos Resumidos por Sistema

| Sistema | Compilador | Comando de Compilação | Execução |
|---------|------------|----------------------|----------|
| **macOS** | clang++ | `clang++ -std=c++11 -Wall -Wextra -g -o hotel src/*.cpp -I include/` | `./hotel` |
| **Windows** | g++ (MinGW) | `g++ -std=c++11 -Wall -Wextra -g -o hotel.exe src/*.cpp -I include/` | `hotel.exe` |
| **Linux** | g++ | `g++ -std=c++11 -Wall -Wextra -g -o hotel src/*.cpp -I include/` | `./hotel` |

## Flags de Compilação Explicadas

- `-std=c++11`: Usa padrão C++11
- `-Wall`: Ativa avisos importantes
- `-Wextra`: Ativa avisos extras
- `-g`: Inclui informações de debug
- `-o hotel`: Nome do executável de saída
- `-I include/`: Inclui diretório de headers


**macOS:**
```bash
clang++ -std=c++11 -Wall -Wextra -O2 -o hotel src/*.cpp -I include/
```

**Windows:**
```cmd
g++ -std=c++11 -Wall -Wextra -O2 -o hotel.exe src/*.cpp -I include/
```

**Linux:**
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o hotel src/*.cpp -I include/
```

## Solução de Problemas Comuns

### Windows - "g++ não é reconhecido"
```cmd
# Verificar se MinGW está no PATH
echo %PATH%

# Adicionar ao PATH (exemplo):
set PATH=%PATH%;C:\mingw64\bin
```

### macOS - "clang++ não encontrado"
```bash
# Instalar Xcode Command Line Tools
xcode-select --install
```

### Linux - "g++ não encontrado"
```bash
sudo apt install build-essential
```

### Erro de permissão (macOS/Linux)
```bash
# Dar permissão de execução
chmod +x hotel
```

## Estrutura de Desenvolvimento

1. **Headers (.h)** → `include/`
2. **Implementações (.cpp)** → `src/`
3. **Dados binários** → `data/`
4. **Documentação** → `docs/`
5. **Planejamento** → `planejamento/`