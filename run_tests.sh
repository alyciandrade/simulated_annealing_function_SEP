
PROGRAMA="./main.exe"
SAIDA="resultados.csv"
REPETICOES=5

echo "seed; temp_inicial; temp_final; alpha; iteracoes_por_temp; final_losses; visited; total_iteracoes; tempo_execucao" > "$SAIDA"

for TEMP_INICIAL in 1000 5000 8000; do
    for TEMP_FINAL in 0.1 0.01 0.001; do
        for ALPHA in 0.90 0.95 0.99; do
            for i in $(seq 1 $REPETICOES); do
                SEED=$i
                echo "T0=$TEMP_INICIAL Tf=$TEMP_FINAL alpha=$ALPHA seed=$SEED..."
                RESULTADO=$("$PROGRAMA" $TEMP_INICIAL $TEMP_FINAL $ALPHA $SEED 100 1 | tail -n 1)
                echo "$RESULTADO" >> "$SAIDA"
            done
        done
    done
done

echo "Pronto! Resultados em $SAIDA"