import pandas as pd

df = pd.read_csv('resultados_total.csv', sep=';', skipinitialspace=True)

colunas_resultado = ['final_losses', 'visited', 'total_iteracoes', 'tempo_execucao']

grupos = df.groupby(['temp_inicial', 'temp_final', 'alpha' ,'iteracoes_por_temp', 'operador'])

resultado = grupos[colunas_resultado].agg(['mean', 'std'])

resultado.columns = ['_'.join(c) for c in resultado.columns]

resultado = resultado.sort_values('final_losses_mean')

resultado.to_csv('media_desvio_total.csv', sep=';')

print("Salvo em media_desvio_total.csv")