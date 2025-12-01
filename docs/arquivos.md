# Formato dos Arquivos

## Arquivos Binários

| Arquivo | Struct | Tamanho | Campos Principais |
|---------|--------|---------|-------------------|
| `clientes.dat` | Cliente | 324 bytes | codigo, nome[100], endereco[200], telefone[20] |
| `funcionarios.dat` | Funcionario | 178 bytes | codigo, nome[100], telefone[20], cargo[50], salario |
| `quartos.dat` | Quarto | 16 bytes | numero, maxHospedes, valorDiaria, status |
| `estadias.dat` | Estadia | 52 bytes | codigos, datas, quantidades, valores |

## Estruturas

### Cliente (324 bytes)
```cpp
struct Cliente {
    int codigo;          // 4 bytes
    char nome[100];      // 100 bytes
    char endereco[200];  // 200 bytes
    char telefone[20];   // 20 bytes
};
```

### Quarto (16 bytes)
```cpp
struct Quarto {
    int numero;           // 4 bytes
    int maxHospedes;      // 4 bytes
    float valorDiaria;    // 4 bytes
    StatusQuarto status;  // 4 bytes (0=livre, 1=ocupado)
};
```

### Estadia (52 bytes)
```cpp
struct Estadia {
    int codigoEstadia;      // 4 bytes
    int codigoCliente;      // 4 bytes (FK)
    int numeroQuarto;       // 4 bytes (FK)
    int quantidadeHospedes; // 4 bytes
    Data dataEntrada;       // 12 bytes (dia, mes, ano)
    Data dataSaida;         // 12 bytes
    int quantidadeDiarias;  // 4 bytes (calculado)
    float valorTotal;       // 4 bytes (calculado)
};
```

## Acesso Direto

### Posicionamento
```cpp
// Acessar registro N:
streampos pos = N * sizeof(Struct);
arquivo.seekp(pos);  // escrita
arquivo.seekg(pos);  // leitura
```

### Serialização
```cpp
// Salvar
arquivo.write(reinterpret_cast<const char*>(&objeto), sizeof(objeto));

// Carregar
arquivo.read(reinterpret_cast<char*>(&objeto), sizeof(objeto));
```

## Características

### Vantagens
- Acesso O(1) por posição
- Atualização in-place
- Simplicidade

### Limitações
- Campos de tamanho fixo
- Busca sequencial por conteúdo
- Sem compressão
