# Sudoku em C++
> Código para resolver um sudoku em C++

## Como funciona

Coloque um arquivo com nome `sudoku-facil.txt` e execute o arquivo `sudoku-solver` através do seguinte comando no terminal:

```sh
./sudoku-solver
```

## Arquivos personalizados

Para colocar o arquivo com o nome que quiser basta abrir o código do arquivo `sudoku-solver.cpp` e localizar a variável `writefile` e substitui-la pela string que você quiser. Feito isso é necessário compilar com o seguinte comando:

```sh
g++ sudoku-solver.cpp -o sudoku-solver
```

Você pode rodar o novo código também com:

```sh
./sudoku-solver
```

## Notas

Embora haja uma variável chamada `writefile`, ela não é responsável pela criação de nenhum arquivo. Em outras palavras, ela é obsoleta.

O código é incapaz de resolver sudokus muito complexos.
