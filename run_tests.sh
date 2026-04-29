
PROGRAMA="./main.exe"
SAIDA="resultados.csv"
REPETICOES=2

echo "seed; temp_inicial; temp_final; alpha; iteracoes_por_temp; operador; final_losses; visited; total_iteracoes; tempo_execucao" > "$SAIDA"

for TEMP_INICIAL in 1000 5000 10000; do
    for TEMP_FINAL in 0.1 0.01 0.001; do
        for ALPHA in 0.90 0.95 0.99; do
            for ITERACOES in 1 10 100; do
                for OPERADOR in 0 1 2; do
                    for i in $(seq 1 $REPETICOES); do
                        SEED=$(date +%H%M%S)
                        echo "T0=$TEMP_INICIAL Tf=$TEMP_FINAL alpha=$ALPHA it=$ITERACOES op=$OPERADOR seed=$SEED..."
                        RESULTADO=$("$PROGRAMA" $TEMP_INICIAL $TEMP_FINAL $ALPHA $SEED $ITERACOES 1 $OPERADOR | tail -n 1)
                        echo "$RESULTADO" >> "$SAIDA"
                    done
                done
            done
        done
    done
done

echo "Pronto! Resultados em $SAIDA"