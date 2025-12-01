# Funções Principais

## 👤 Cliente

### `int cadastrarCliente()`
- **Função**: Cadastra novo cliente
- **Entrada**: Dados via interface
- **Saída**: Código gerado ou -1 (erro)
- **Validações**: Nome, endereço, telefone obrigatórios

### `bool clienteExiste(int codigo)`
- **Função**: Verifica existência
- **Entrada**: Código do cliente
- **Saída**: true/false

### `Cliente buscarCliente(int codigo)`
- **Função**: Busca cliente por código
- **Entrada**: Código do cliente
- **Saída**: Struct Cliente ou vazio

---

## 👷 Funcionário

### `int cadastrarFuncionario()`
- **Função**: Cadastra novo funcionário
- **Validações**: Salário > 0, campos obrigatórios

### `bool funcionarioExiste(int codigo)`
### `Funcionario buscarFuncionario(int codigo)`
- Mesma lógica do cliente

---

## 🏨 Quarto

### `int cadastrarQuarto()`
- **Função**: Cadastra novo quarto
- **Validações**: Número único, capacidade > 0, valor > 0
- **Status inicial**: DESOCUPADO

### `Quarto buscarQuartoDisponivel(int minHospedes)`
- **Função**: Busca quarto livre com capacidade
- **Entrada**: Mínimo de hóspedes
- **Saída**: Primeiro quarto disponível

### `bool atualizarStatusQuarto(int numero, StatusQuarto status)`
- **Função**: Atualiza status via acesso direto
- **Entrada**: Número e novo status
- **Saída**: true/false

---

## 🛏️ Estadia

### `int cadastrarEstadia()`
- **Função**: Cadastra reserva completa
- **Processo**:
  1. Valida cliente existente
  2. Busca quarto disponível
  3. Calcula diárias e valor
  4. Salva estadia
  5. Atualiza status do quarto

### `int calcularDiarias(const Data& entrada, const Data& saida)`
- **Função**: Calcula número de diárias
- **Entrada**: Datas de entrada e saída
- **Saída**: Número de diárias (mínimo 1)

---

## 🛠️ Utilitários

### `int lerInteiroPositivo(const string& prompt)`
- **Função**: Lê número positivo com validação
- **Tratamento**: Repete até entrada válida

### `string lerStringNaoVazia(const string& prompt, int max)`
- **Função**: Lê string obrigatória
- **Validações**: Não vazia, tamanho máximo

### `void inicializarArquivos()`
- **Função**: Cria diretório data/ e arquivos .dat

---

## 📊 Validações

### `bool Struct::validar() const`
Cada struct tem validação própria:
- **Cliente**: Código > 0, campos não vazios
- **Funcionario**: Código > 0, salário > 0, campos não vazios
- **Quarto**: Número > 0, capacidade > 0, valor > 0
- **Estadia**: Códigos válidos, datas válidas, quantidades > 0