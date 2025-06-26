# Pseudocódigos dos Algoritmos - Trabalho Prático 3

## Processamento de Caracteres e Compressão de Arquivos

**Aluno:** Bernardo Detomi  
**Data:** 26 de Junho de 2025  
**Disciplina:** Projeto e Análise de Algoritmos

---

## 1. Algoritmos da Parte 1: Busca Aproximada

### 1.1 Algoritmo de Programação Dinâmica

```
ALGORITMO BuscaProgramacaoDinamica
ENTRADA: texto T[1..n], padrão P[1..m], k (número máximo de erros)
SAÍDA: posições das ocorrências com até k erros

INÍCIO
    // Inicialização da matriz de distância de edição
    CRIAR matriz D[0..m][0..n]
    
    // Primeira linha: inserções gratuitas
    PARA j ← 0 ATÉ n FAÇA
        D[0][j] ← 0
    FIM PARA
    
    // Primeira coluna: custo de deleções
    PARA i ← 1 ATÉ m FAÇA
        D[i][0] ← i
    FIM PARA
    
    // Preenchimento da matriz
    PARA j ← 1 ATÉ n FAÇA
        PARA i ← 1 ATÉ m FAÇA
            // Custo de substituição
            SE P[i] = T[j] ENTÃO
                custo ← 0
            SENÃO
                custo ← 1
            FIM SE
            
            // Cálculo do mínimo entre operações
            inserção ← D[i][j-1] + 1
            deleção ← D[i-1][j] + 1
            substituição ← D[i-1][j-1] + custo
            
            D[i][j] ← MÍNIMO(inserção, deleção, substituição)
        FIM PARA
        
        // Verificação de ocorrência
        SE D[m][j] ≤ k ENTÃO
            posição ← j - m + 1
            IMPRIMIR posição
        FIM SE
    FIM PARA
FIM
```

**Complexidade:**
- Tempo: O(n × m)
- Espaço: O(n × m)

---

### 1.2 Algoritmo Shift-And

```
ALGORITMO BuscaShiftAnd
ENTRADA: texto T[1..n], padrão P[1..m], k (número máximo de erros)
SAÍDA: posições das ocorrências com até k erros

INÍCIO
    // Verificação de limitação do tamanho do padrão
    SE m > 31 ENTÃO
        RETORNAR "Padrão muito longo"
    FIM SE
    
    // Pré-processamento: criação das máscaras de bits
    CRIAR array B[0..255] ← 0
    PARA i ← 0 ATÉ m-1 FAÇA
        c ← P[i]
        B[c] ← B[c] OU (1 << i)
    FIM PARA
    
    // Inicialização dos registradores para cada nível de erro
    CRIAR array R[0..k] ← 0
    
    // Processamento do texto
    PARA j ← 0 ATÉ n-1 FAÇA
        c ← T[j]
        oldR ← R[0]
        
        // Atualização do registrador para busca exata
        R[0] ← ((R[0] << 1) OU 1) E B[c]
        
        // Atualização dos registradores para busca aproximada
        PARA e ← 1 ATÉ k FAÇA
            temp ← R[e]
            R[e] ← ((R[e] << 1) OU 1) E B[c]
            R[e] ← R[e] OU (oldR << 1) OU oldR OU R[e-1]
            oldR ← temp
        FIM PARA
        
        // Verificação de ocorrência
        SE R[k] E (1 << (m-1)) ≠ 0 ENTÃO
            posição ← j - m + 2
            IMPRIMIR posição
        FIM SE
    FIM PARA
FIM
```

**Complexidade:**
- Tempo: O(n × k)
- Espaço: O(σ + k), onde σ = 256 (tamanho do alfabeto)

---

## 2. Algoritmos da Parte 2: Busca Exata

### 2.1 Algoritmo Boyer-Moore-Horspool (BMH)

```
ALGORITMO BoyerMooreHorspool
ENTRADA: texto T[1..n], padrão P[1..m]
SAÍDA: posições das ocorrências exatas

INÍCIO
    // Pré-processamento: criação da tabela de deslocamento
    CRIAR array tabela[0..255]
    
    // Inicializar tabela com o comprimento do padrão
    PARA i ← 0 ATÉ 255 FAÇA
        tabela[i] ← m
    FIM PARA
    
    // Preencher tabela com deslocamentos específicos
    PARA i ← 0 ATÉ m-2 FAÇA
        c ← P[i]
        tabela[c] ← m - 1 - i
    FIM PARA
    
    // Busca no texto
    i ← 0
    ENQUANTO i ≤ n - m FAÇA
        // Comparação da direita para esquerda
        j ← m - 1
        ENQUANTO j ≥ 0 E P[j] = T[i + j] FAÇA
            j ← j - 1
        FIM ENQUANTO
        
        SE j < 0 ENTÃO
            // Ocorrência encontrada
            IMPRIMIR (i + 1)  // posição baseada em 1
            i ← i + 1
        SENÃO
            // Deslocamento baseado no caractere ruim
            i ← i + tabela[T[i + m - 1]]
        FIM SE
    FIM ENQUANTO
FIM
```

**Complexidade:**
- Tempo: O(n × m) no pior caso, O(n/m) no melhor caso
- Espaço: O(σ), onde σ = 256 (tamanho do alfabeto)

---

### 2.2 Algoritmo de Compressão Simplificada (Simulando Huffman)

```
ALGORITMO CompressaoSimplificada
ENTRADA: arquivo de entrada
SAÍDA: arquivo comprimido

INÍCIO
    ABRIR arquivo de entrada para leitura
    ABRIR arquivo de saída para escrita binária
    
    anterior ← -1
    contador ← 1
    
    ENQUANTO NÃO fim do arquivo FAÇA
        c ← LER próximo caractere
        
        SE c = anterior E contador < 255 ENTÃO
            contador ← contador + 1
        SENÃO
            SE anterior ≠ -1 ENTÃO
                // Aplicar transformação XOR (simulando compressão)
                char_comprimido ← anterior XOR 0x55
                ESCREVER char_comprimido
                
                // Run-Length Encoding para caracteres repetidos
                SE contador > 1 ENTÃO
                    ESCREVER 0xFF  // marcador RLE
                    ESCREVER contador
                FIM SE
            FIM SE
            
            anterior ← c
            contador ← 1
        FIM SE
    FIM ENQUANTO
    
    // Processar último caractere
    SE anterior ≠ -1 ENTÃO
        char_comprimido ← anterior XOR 0x55
        ESCREVER char_comprimido
        SE contador > 1 ENTÃO
            ESCREVER 0xFF
            ESCREVER contador
        FIM SE
    FIM SE
    
    FECHAR arquivos
FIM
```

**Complexidade:**
- Tempo: O(n)
- Espaço: O(1) (processamento em streaming)

---

### 2.3 Algoritmo de Compressão de Padrão

```
ALGORITMO ComprimirPadrao
ENTRADA: padrão P[1..m]
SAÍDA: padrão comprimido

INÍCIO
    CRIAR buffer dinâmico para saída
    tamanho ← 0
    
    PARA i ← 0 ATÉ m-1 FAÇA
        // Aplicar mesma transformação XOR usada no arquivo
        char_comprimido ← P[i] XOR 0x55
        
        // Adicionar ao buffer de saída
        ADICIONAR char_comprimido ao buffer
        tamanho ← tamanho + 1
    FIM PARA
    
    RETORNAR (buffer, tamanho)
FIM
```

**Complexidade:**
- Tempo: O(m)
- Espaço: O(m)

---

## 3. Algoritmo Principal de Controle

### 3.1 Controle Principal - Parte 1

```
ALGORITMO ControlePrincipalParte1
ENTRADA: algoritmo (1=PD, 2=ShiftAnd), arquivo_texto, arquivo_padrões
SAÍDA: resultados da busca para k=0,1,2,3

INÍCIO
    algoritmo ← LER parâmetro
    texto ← LER arquivo de texto
    padrões ← LER arquivo de padrões
    
    ABRIR arquivo "saida.txt" para escrita
    
    PARA cada padrão nos padrões FAÇA
        PARA k ← 0 ATÉ 3 FAÇA
            SE algoritmo = 1 ENTÃO
                BuscaProgramacaoDinamica(texto, padrão, k, arquivo_saida)
            SENÃO SE algoritmo = 2 ENTÃO
                BuscaShiftAnd(texto, padrão, k, arquivo_saida)
            FIM SE
        FIM PARA
    FIM PARA
    
    FECHAR arquivo de saída
FIM
```

---

### 3.2 Controle Principal - Parte 2

```
ALGORITMO ControlePrincipalParte2
ENTRADA: arquivo_texto, arquivo_padrões
SAÍDA: comparação de desempenho entre texto original e comprimido

INÍCIO
    // Compressão do arquivo
    CompressaoSimplificada(arquivo_texto, "texto.huff")
    
    // Carregamento dos dados
    texto_original ← LER arquivo_texto
    texto_comprimido ← LER "texto.huff"
    padrões ← LER arquivo_padrões
    
    ABRIR arquivo "saida.txt" para escrita
    
    PARA cada padrão nos padrões FAÇA
        IMPRIMIR nome do padrão
        
        // Busca no texto original
        IMPRIMIR "📄 Texto original:"
        CRONOMETRAR início
        ocorrências1 ← BoyerMooreHorspool(texto_original, padrão, arquivo_saida)
        CRONOMETRAR fim
        IMPRIMIR métricas (comparações, tempo)
        
        // Busca no texto comprimido
        padrão_comprimido ← ComprimirPadrao(padrão)
        IMPRIMIR "💾 Texto comprimido:"
        CRONOMETRAR início
        ocorrências2 ← BoyerMooreHorspool(texto_comprimido, padrão_comprimido, NULL)
        CRONOMETRAR fim
        IMPRIMIR métricas (comparações, tempo)
    FIM PARA
    
    FECHAR arquivo de saída
FIM
```

---

## 4. Estruturas de Dados Auxiliares

### 4.1 Leitura de Arquivo de Texto

```
FUNÇÃO LerArquivo(nome_arquivo)
INÍCIO
    ABRIR arquivo para leitura
    DETERMINAR tamanho do arquivo
    ALOCAR buffer de tamanho adequado
    LER todo o conteúdo para o buffer
    ADICIONAR terminador nulo
    FECHAR arquivo
    RETORNAR buffer
FIM
```

### 4.2 Leitura de Linhas (Padrões)

```
FUNÇÃO LerLinhas(nome_arquivo, número_linhas)
INÍCIO
    ABRIR arquivo para leitura
    CONTAR número de linhas no arquivo
    ALOCAR array de strings
    
    PARA cada linha no arquivo FAÇA
        LER linha
        REMOVER quebra de linha
        ALOCAR espaço para a string
        COPIAR linha para o array
    FIM PARA
    
    FECHAR arquivo
    DEFINIR número_linhas
    RETORNAR array de strings
FIM
```

---

## 5. Observações sobre Implementação

### 5.1 Otimizações Aplicadas

1. **Programação Dinâmica:**
   - Uso de indexação direta para evitar cálculos desnecessários
   - Verificação de ocorrências durante o preenchimento da matriz

2. **Shift-And:**
   - Uso de operações bit-a-bit para máxima eficiência
   - Pré-processamento otimizado das máscaras de bits

3. **Boyer-Moore-Horspool:**
   - Tabela de saltos pré-computada para caracteres ASCII
   - Comparação da direita para esquerda para maximizar saltos

### 5.2 Limitações dos Algoritmos

1. **Shift-And:** Limitado a padrões de até 31 caracteres devido ao uso de `uint32_t`
2. **Compressão Simulada:** Não implementa Huffman real, apenas simulação para demonstração
3. **Programação Dinâmica:** Alto consumo de memória O(n×m) para textos grandes

### 5.3 Complexidades Resumidas

| Algoritmo | Tempo | Espaço | Observações |
|-----------|-------|--------|-------------|
| Programação Dinâmica | O(n×m) | O(n×m) | Flexível para qualquer k |
| Shift-And | O(n×k) | O(σ+k) | Limitado m ≤ 31 |
| Boyer-Moore-Horspool | O(n×m) pior, O(n/m) melhor | O(σ) | Apenas busca exata |
| Compressão Simulada | O(n) | O(1) | Processamento streaming |

---

**Nota:** Estes pseudocódigos representam a lógica central dos algoritmos implementados, abstraindo detalhes específicos de implementação em C como gerenciamento de memória e tratamento de arquivos.
