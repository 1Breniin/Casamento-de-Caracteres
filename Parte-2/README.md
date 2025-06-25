# Parte 2: Busca Exata em Arquivos Comprimidos

## Compilação

```bash
make clean
make
```

## Execução

```bash
./tp3_parte2 <arquivo_texto> <arquivo_padroes>
```

**Parâmetros:**
- `arquivo_texto`: arquivo contendo o texto onde buscar
- `arquivo_padroes`: arquivo contendo os padrões (um por linha)

## Exemplos

```bash
./tp3_parte2 texto.txt padroes.txt
```

## Arquivos de Teste

- `texto.txt`: arquivo de teste com múltiplas repetições
- `padroes.txt`: contém "palavras", "exemplo", "desempenho", etc.

## Saída Esperada

```
Comprimindo arquivo...
Tamanho original: X bytes
Tamanho comprimido: Y bytes
Taxa de compressão: Z%

palavras
📄 Texto original:
   Posições: 26 36 ...
   Métricas: X comparações, Y.ZZZZZZs
💾 Texto comprimido:
   Posições: 26 36 ...
   Métricas: X comparações, Y.ZZZZZZs
```

## Funcionalidades

- **Compressão Huffman simulada**: Comprime o arquivo de texto
- **Boyer-Moore-Horspool**: Busca eficiente de padrões
- **Comparação de desempenho**: Entre arquivo original e comprimido
- **Métricas detalhadas**: Número de comparações e tempo de execução

## Estrutura dos Arquivos

- `main.c`: Programa principal e controle de experimentos
- `bmh.c/bmh.h`: Implementação do algoritmo Boyer-Moore-Horspool
- `huffman.c/huffman.h`: Simulação de compressão Huffman
- `util.c/util.h`: Funções auxiliares para leitura de arquivos
- `Makefile`: Script de compilação

## Observações

- A compressão é uma simulação usando XOR + RLE
- As posições são mostradas com indexação baseada em 1
- O programa gera automaticamente o arquivo comprimido `texto.huff`
- Taxa de compressão pode ser 0% para textos sem padrões repetitivos 🧩 TP3 (Parte 2) - Busca Exata em Arquivos Comprimidos

Este projeto implementa o algoritmo de **Boyer-Moore-Horspool (BMH)** para busca exata de padrões em:

- Arquivos **não comprimidos**
- Arquivos **comprimidos com Huffman com marcação** (fictício: XOR com 0xAA)

---

## 📂 Estrutura do Projeto

```
tp3_parte2/src
├── main.c             # Executável principal
├── bmh.c/.h           # Algoritmo BMH
├── huffman.c/.h       # Compressão fictícia estilo Huffman
├── util.c/.h          # Leitura de padrões e utilitários
├── Makefile
└── saida.txt          # Gerado automaticamente com os padrões
```

---

## ⚙️ Compilação

Requisitos: compilador C (`gcc`) e `make`

```bash
make
```

Isso gera o executável:

```
./tp3_parte2
```

---

## ▶️ Execução

```bash
./tp3_parte2 <arquivo_texto> <arquivo_padroes>
```

- `<arquivo_texto>`: arquivo `.txt` contendo o texto completo
- `<arquivo_padroes>`: arquivo com um padrão por linha

---

## 🧪 O que o programa faz

1. Comprime o texto com uma versão fictícia de Huffman (`texto.huff`)
2. Aplica o algoritmo BMH:
   - No texto original
   - No texto comprimido (com padrão comprimido também)
3. Mostra no terminal:
   - Número de comparações
   - Tempo de execução
4. Salva os padrões testados em `saida.txt`

---

## 📄 Exemplo

### texto.txt
```
Texto exemplo, texto tem palavras, palavras exercem fascínio.
```

### padroes.txt
```
palavras
exemplo
```

### Execução
```bash
./tp3_parte2 texto.txt padroes.txt
```

### Saída no terminal
```
Original: 2 ocorrências | comparações: 120 | tempo: 0.000058s
Comprimido: 2 ocorrências | comparações: 124 | tempo: 0.000062s
```

### saida.txt
```
palavras
exemplo
```

---

## 📌 Observações

- A compressão usada é **fictícia** (XOR com 0xAA) apenas para simular a lógica de Huffman com marcação.
- O arquivo `texto.huff` é gerado automaticamente e usado na busca comprimida.
- O arquivo `saida.txt` contém os padrões processados.

---

## 👨‍💻 Autor

Breno Esteves dos Santos e Bernardo Maia Detomi 
Curso de Ciência da Computação – UFSJ  
Trabalho Prático 3 – Parte 2 – Processamento de Cadeias de Caracteres
