# 🧩 TP3 (Parte 2) - Busca Exata em Arquivos Comprimidos

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
