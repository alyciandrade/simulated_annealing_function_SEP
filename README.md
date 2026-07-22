# Simulated Annealing para Otimização de Sistemas Elétricos de Potência (SEP)

Projeto de pesquisa (PIBIC) que aplica o algoritmo **Simulated Annealing** para minimizar perdas de potência ativa em sistemas elétricos, utilizando a biblioteca `libeps`.

## Estrutura do Projeto

```
├── src/                     # Código-fonte C
│   ├── main.c               # Ponto de entrada do programa
│   ├── sa_power.c/h         # Implementação do Simulated Annealing
│   └── power_system_functions.c/h  # Funções do sistema de potência
├── scripts/                 # Scripts auxiliares
│   ├── run_tests.sh         # Script para executar bateria de testes
│   ├── analise.py           # Análise estatística dos resultados
│   └── graficos.py          # Geração de gráficos de convergência
├── results/                 # Resultados de simulação (CSVs e imagens)
├── notebooks/               # Jupyter notebooks de análise
├── Makefile                 # Regras de compilação
└── README.md
```

## Compilação

Requer `gcc` e a biblioteca `libeps` instalada em `/usr/local/`.

```bash
make          # compila main.exe
make clean    # remove objetos e executável
```

## Execução

```bash
./main.exe <temp_inicial> <temp_final> <alpha> <seed> <iteracoes_por_temp> <contar> <operador> <log_ativo>
```

### Parâmetros

| Parâmetro           | Descrição                                              |
|---------------------|--------------------------------------------------------|
| `temp_inicial`      | Temperatura inicial do SA                              |
| `temp_final`        | Temperatura final (critério de parada)                 |
| `alpha`             | Fator de resfriamento (ex: 0.975)                      |
| `seed`              | Semente para o gerador de números aleatórios           |
| `iteracoes_por_temp`| Número de iterações por nível de temperatura           |
| `contar`            | 1 = contar estados visitados, 0 = não contar           |
| `operador`          | 0 = swap, 1 = insert, 2 = aleatório                   |
| `log_ativo`         | 1 = gerar `results/log_iteracoes.csv`, 0 = desativado |

### Exemplo

```bash
./main.exe 1000 0.001 0.975 42 10 1 2 1
```

## Bateria de Testes

```bash
cd scripts
bash run_tests.sh
```

## Análise de Resultados

```bash
cd scripts
python analise.py      # gera media_desvio_total.csv em results/
python graficos.py     # gera graficos.png em results/
```

## Sistema de Teste

- **IEEE 30 barras** (`ARQ_IEEE_30_BUS`)
