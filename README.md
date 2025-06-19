# 🧩 TP4 - Busca Aproximada em Arquivos Não Comprimidos

Este projeto implementa dois algoritmos de casamento aproximado de padrões em arquivos de texto:

- **Programação Dinâmica**
- **Shift-And Aproximado**

O sistema busca padrões com até `k` erros (`k = 0, 1, 2, 3`) e exibe os resultados tanto no terminal quanto em um arquivo de saída.

## 📂 Estrutura do Projeto

```
tp4_parte1/
├── main.c            # Função principal
├── busca.c/.h        # Implementação dos algoritmos
├── util.c/.h         # Leitura de arquivos e utilitários
├── Makefile          # Compilação automatizada
└── saida.txt         # Gerado automaticamente com os resultados
```

## ⚙️ Compilação

Requisitos: compilador C (`gcc`) e `make`

```bash
make
```

Isso gera o executável:

```
./tp4_parte1
```

## ▶️ Execução

```bash
./tp4_parte1 <algoritmo> <arquivo_texto> <arquivo_padroes>
```

**Parâmetros:**
- `<algoritmo>`:  
  `1` → Programação Dinâmica  
  `2` → Shift-And Aproximado
- `<arquivo_texto>`: arquivo `.txt` com o texto completo
- `<arquivo_padroes>`: arquivo com um padrão por linha

### 📄 Exemplo

#### texto.txt
```
Texto exemplo, texto tem palavras, palavras exercem fascínio.
```

#### padroes.txt
```
palavras
exemplo
```

#### Execução
```bash
./tp4_parte1 1 texto.txt padroes.txt
```

#### Saída no terminal
```
palavras (k=0) 26 36 [comparações: 1500 | tempo: 0.000130s]
...
```

#### Conteúdo de saida.txt
```
palavras (k=0) 26 36
...
```

## 📌 Observações

- O **Shift-And** só suporta padrões com até **31 caracteres**.
- O tempo e número de comparações **são exibidos apenas no terminal**.
- O arquivo `saida.txt` é **gerado automaticamente** no diretório do projeto.
- Testes foram feitos com até `k=3`, conforme solicitado no enunciado.

## 👨‍💻 Autor

Breno Esteves  
Curso de Ciência da Computação - UFSJ  
Trabalho Prático 4 – Processamento de Cadeias de Caracteres
