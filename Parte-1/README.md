# Parte 1: Busca Aproximada em Arquivos Não Comprimidos

## Compilação

```bash
make clean
make
```

## Execução

```bash
./tp3_parte1 <algoritmo> <arquivo_texto> <arquivo_padroes>
```

**Parâmetros:**
- `algoritmo`: 1 para Programação Dinâmica, 2 para Shift-And
- `arquivo_texto`: arquivo contendo o texto onde buscar
- `arquivo_padroes`: arquivo contendo os padrões (um por linha)

**Comportamento:**
O programa executa automaticamente a busca para k = 0, 1, 2, 3 e exibe os resultados para cada valor.

## Exemplos

### Programação Dinâmica
```bash
./tp3_parte1 1 texto.txt padroes.txt
```

### Shift-And
```bash
./tp3_parte1 2 texto.txt padroes.txt
```

## Arquivos de Teste

- `texto.txt`: "Texto exemplo, texto tem palavras, palavras exercem fascínio."
- `padroes.txt`: contém "palavras" e "exemplo"

## Saída Esperada

Para cada padrão, o programa exibe os resultados para k=0,1,2,3:
```
palavras 26 36                    (k=0)
palavras 25 26 27 35 36 37        (k=1)
palavras 24 25 26 27 28 34 35 36 37 38    (k=2)
palavras 23 24 25 26 27 28 29 33 34 35 36 37 38 39  (k=3)
exemplo 7                         (k=0)
exemplo 6 7 8                     (k=1)
exemplo 5 6 7 8 9                 (k=2)
exemplo 4 5 6 7 8 9 10            (k=3)
```

## Estrutura dos Arquivos

- `main.c`: Programa principal
- `busca.c/busca.h`: Implementação dos algoritmos de busca
- `util.c/util.h`: Funções auxiliares para leitura de arquivos
- `Makefile`: Script de compilação

## Observações

- O algoritmo Shift-And está limitado a padrões de até 31 caracteres
- As métricas de desempenho são exibidas no stderr
- As posições são mostradas com indexação baseada em 1

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
./tp3_parte1 <algoritmo> <arquivo_texto> <arquivo_padroes>
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
./tp3_parte1 1 texto.txt padroes.txt
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

Breno Esteves dos Santos e Bernardo Maia Detomi
Curso de Ciência da Computação - UFSJ  
Trabalho Prático 3 – Processamento de Cadeias de Caracteres
