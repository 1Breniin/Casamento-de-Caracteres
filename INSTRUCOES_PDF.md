# Como Converter a Documentação para PDF

## Opção 1: Usando Pandoc (Recomendado)

### Instalação do Pandoc no Ubuntu/Debian:
```bash
sudo apt update
sudo apt install pandoc texlive-latex-base texlive-fonts-recommended texlive-latex-extra
```

### Conversão para PDF:
```bash
cd /home/bernardomd/TrabalhoPAA/Trabalho3/Casamento-de-Caracteres/
pandoc DOCUMENTACAO.md -o DOCUMENTACAO.pdf --pdf-engine=pdflatex
```

### Para um PDF mais formatado:
```bash
pandoc DOCUMENTACAO.md -o DOCUMENTACAO.pdf \
  --pdf-engine=pdflatex \
  --variable geometry:margin=2cm \
  --variable fontsize=11pt \
  --variable documentclass=article \
  --table-of-contents \
  --number-sections
```

## Opção 2: Usando Markdown Preview Enhanced (VS Code)

1. Instale a extensão "Markdown Preview Enhanced" no VS Code
2. Abra o arquivo DOCUMENTACAO.md
3. Pressione Ctrl+Shift+P
4. Digite "Markdown Preview Enhanced: Export (PDF)"
5. Selecione as opções desejadas e exporte

## Opção 3: Online (Mais Simples)

1. Copie o conteúdo do arquivo DOCUMENTACAO.md
2. Acesse: https://www.markdowntopdf.com/
3. Cole o conteúdo e faça o download do PDF

## Opção 4: Usando Typora

1. Instale o Typora (editor Markdown)
2. Abra o arquivo DOCUMENTACAO.md
3. Vá em File → Export → PDF

## Verificação do Resultado

Após a conversão, verifique se:
- Todas as seções estão presentes
- As tabelas estão formatadas corretamente
- O código está bem apresentado
- As equações matemáticas estão renderizadas
- O documento não excede 12 páginas (conforme especificação)

## Estrutura Final da Entrega

```
Trabalho3/
├── Parte-1/
│   ├── src/
│   │   ├── main.c
│   │   ├── busca.c
│   │   ├── busca.h
│   │   ├── util.c
│   │   ├── util.h
│   │   ├── Makefile
│   │   ├── texto.txt
│   │   └── padroes.txt
│   └── README.md
├── Parte-2/
│   ├── src/
│   │   ├── main.c
│   │   ├── bmh.c
│   │   ├── bmh.h
│   │   ├── huffman.c
│   │   ├── huffman.h
│   │   ├── util.c
│   │   ├── util.h
│   │   ├── Makefile
│   │   ├── texto.txt
│   │   └── padroes.txt
│   └── README.md
├── DOCUMENTACAO.md
├── DOCUMENTACAO.pdf
└── INSTRUCOES_PDF.md
```
