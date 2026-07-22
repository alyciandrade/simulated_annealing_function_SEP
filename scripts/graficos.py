import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results/log_iteracoes.csv', sep=';', skipinitialspace=True)

fig, axs = plt.subplots(2, 2, figsize=(14, 10))

# Gráfico 1 - Custo atual
axs[0, 0].plot(df['iteracao'], df['current_cost'], color='steelblue', linewidth=0.5)
axs[0, 0].set_xlabel('Iteração')
axs[0, 0].set_ylabel('Custo Atual (MW)')
axs[0, 0].set_title('Custo Atual por Iteração')
axs[0, 0].set_ylim(600, 700)

# Gráfico 2 - Melhor custo
axs[0, 1].plot(df['iteracao'], df['best_cost'], color='green', linewidth=0.5)
axs[0, 1].set_xlabel('Iteração')
axs[0, 1].set_ylabel('Melhor Custo (MW)')
axs[0, 1].set_title('Melhor Custo por Iteração')
axs[0, 1].set_ylim(600, 700)

# Gráfico 3 - Temperatura
axs[1, 0].plot(df['iteracao'], df['temperatura'], color='red', linewidth=0.5)
axs[1, 0].set_xlabel('Iteração')
axs[1, 0].set_ylabel('Temperatura')
axs[1, 0].set_title('Temperatura por Iteração')

# Gráfico 4 - Melhor custo por estados visitados
axs[1, 1].plot(df['visited_states'], df['best_cost'], color='purple', linewidth=0.5)
axs[1, 1].set_xlabel('Estados Visitados')
axs[1, 1].set_ylabel('Melhor Custo (MW)')
axs[1, 1].set_title('Melhor Custo por Estados Visitados')
axs[1, 1].set_ylim(600, 700)

plt.tight_layout()
plt.savefig('results/graficos.png', dpi=150)
plt.show()

print("Salvo em results/graficos.png")