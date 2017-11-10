# Projeto

Projeto em C que tem a funcao de multiplicar matrizes e coletar os tempos gastos utilizando threads e forks

### Prerequisitos

Apenas o compilador padrao do c

```
sudo apt install build-essential
```

### Installing

Para rodar os testes e necessario apenas executar o script start_test.sh

```
./start_test
```

caso o e script nao tenha permissao de execucao,

```
chmod +x start_test.sh
```

Este script ira criar matrizes exemplos e executar a multiplicacao utilizando
diferentes numeros de threads e processos

### Removendo

Para remover as matrizes e os resultados gerados

```
./clean.sh
```

### INFORMACOES IMPORTANTES

- Todos os scripts devem ser executados no diretorio raiz do Projeto;

- Os resultados obtidos estarao no diretorio result/<metodo>

- dentro do diretorio de cada metodo sera criado os arquivos com os resultados

- cada arquivo possui o padrao <Numero de linhas da matriz> _ <Numero de processos>.out

- exemplo matrix 500 x 500 com 4 threads, estara em results/thread/500_4.out

- o tempo nos arquivos esta em segundos

- as funcoes de printf das matrizes e informacoes estao comentadas, para a realizao
dos testes.

## Author

* **Jonatan Souza** - *IME*
