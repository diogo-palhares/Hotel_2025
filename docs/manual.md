# Manual do Usuário

## 🚀 Como Usar

### Executar
```bash
./hotel        # Linux/macOS
hotel.exe      # Windows
```

### Menu Principal
```
1. Cadastrar Cliente
2. Cadastrar Funcionário
3. Cadastrar Quarto
4. Cadastrar Estadia
5. Listar Clientes
6. Listar Funcionários
7. Listar Quartos
8. Listar Estadias
9. Sair
```

## 📋 Fluxo Recomendado

### 1. Primeiro Uso
1. **Cadastrar Quartos** (ex: 101, 102, 201)
2. **Cadastrar Clientes** 
3. **Fazer Reservas** (Cadastrar Estadias)

### 2. Cadastrar Cliente
- Sistema gera código automaticamente
- Informar: Nome, Endereço, Telefone
- Todos os campos são obrigatórios

### 3. Cadastrar Quarto
- Informar: Número (único), Capacidade, Valor da diária
- Status inicial: sempre "Desocupado"

### 4. Cadastrar Estadia
- Informar código do cliente (deve existir)
- Informar quantidade de hóspedes
- Informar datas (saída > entrada)
- Sistema busca quarto disponível automaticamente
- Calcula diárias e valor total automaticamente

## 📊 Listagens

### Clientes
- Tabela com todos os clientes
- Total de clientes cadastrados

### Funcionários  
- Tabela com dados e salários
- Folha de pagamento total
- Salário médio

### Quartos
- Status visual: 🟢 Livre / 🔴 Ocupado
- Taxa de ocupação
- Valor médio das diárias

### Estadias
- Dados da reserva + nome do cliente
- Faturamento total
- Estatísticas de ocupação

## ⚠️ Validações

### Mensagens de Erro Comuns
- "Já existe um quarto com este número"
- "Cliente não encontrado"
- "Não há quartos disponíveis"
- "Data de saída deve ser posterior à entrada"

### Dicas
- ✅ Cadastre quartos antes de fazer reservas
- ✅ Use números sequenciais para quartos
- ✅ Verifique códigos de clientes nas listagens
- ✅ Datas no formato DD/MM/AAAA