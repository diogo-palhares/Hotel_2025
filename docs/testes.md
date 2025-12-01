# Testes

## 🧪 Executar Testes

```bash
cd tests
./executar_testes.sh    # Linux/macOS
executar_testes.bat     # Windows
```

## 📊 Testes Automatizados (15 total)

### Arquivos
- **Inicialização**: Criação dos arquivos .dat
- **Integridade**: Consistência após operações

### Cadastros
- **Cliente**: Persistência e recuperação
- **Funcionário**: Persistência e recuperação  
- **Quarto**: Persistência e status inicial
- **Estadia**: Fluxo completo com cálculos

### Validações
- **Dados válidos**: Structs corretas passam
- **Dados inválidos**: Structs incorretas falham

### Operações
- **Busca**: Localização por código
- **Status**: Atualização de quartos
- **Cálculos**: Diárias entre datas
- **Serialização**: Conversão binária

## 📋 Casos de Teste Manuais

### CT1: Fluxo Completo
1. Cadastrar cliente "João Silva"
2. Cadastrar quarto 101 (2 hóspedes, R$ 150)
3. Fazer reserva (2 hóspedes, 2 dias)
4. Verificar: valor = R$ 300, quarto ocupado

### CT2: Validações
1. Tentar quarto com número duplicado
2. Tentar reserva para cliente inexistente
3. Tentar datas inválidas
4. Verificar mensagens de erro

### CT3: Listagens
1. Cadastrar múltiplos registros
2. Verificar cálculos nas listagens
3. Confirmar formatação e estatísticas

## ✅ Critérios de Sucesso

- Taxa de sucesso ≥ 95%
- Todos os casos de uso funcionando
- Mensagens de erro claras
- Cálculos corretos
- Dados persistidos corretamente