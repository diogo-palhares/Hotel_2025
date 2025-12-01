# Arquitetura do Sistema

## Estrutura

```
┌─────────────────┐
│   Interface     │  main.cpp, utils.cpp
├─────────────────┤
│ Lógica Negócio  │  cliente.cpp, funcionario.cpp, quarto.cpp, estadia.cpp
├─────────────────┤
│  Persistência   │  Serialização binária
├─────────────────┤
│  Armazenamento  │  Arquivos .dat
└─────────────────┘
```

## Organização

```
src/
├── main.cpp          # Menu principal
├── cliente.cpp       # CRUD clientes
├── funcionario.cpp   # CRUD funcionários
├── quarto.cpp        # CRUD quartos + status
├── estadia.cpp       # CRUD estadias + cálculos
└── utils.cpp         # Validações e interface

include/
├── *.h              # Headers correspondentes

data/
├── clientes.dat     # Dados binários
├── funcionarios.dat
├── quartos.dat
└── estadias.dat
```

## Dependências

- **main.cpp** → todos os módulos
- **estadia.cpp** → cliente.cpp + quarto.cpp
- **todos** → utils.cpp

## Acesso Direto

- **Registros fixos**: `sizeof(struct)`
- **Posicionamento**: `seekp(pos * sizeof(struct))`
- **Serialização**: `write()/read()` binário
- **Atualização**: Modificação in-place
