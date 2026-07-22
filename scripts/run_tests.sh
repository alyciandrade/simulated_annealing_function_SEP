
PROGRAMA="../main.exe"
SAIDA="../results/resultados.csv"
REPETICOES=20

echo "seed; temp_inicial; temp_final; alpha; iteracoes_por_temp; operador; final_losses; visited; total_iteracoes; tempo_execucao" > "$SAIDA"

for TEMP_INICIAL in 500 1000 2500; do
    for TEMP_FINAL in 0.001; do
        for ALPHA in 0.95 0.975 0.99; do
            for ITERACOES in 1 10; do
                for OPERADOR in 1 2; do
                    for i in $(seq 1 $REPETICOES); do
                        SEED=$(( $(date +%s%N) % 2147483647 ))
                        echo "T0=$TEMP_INICIAL Tf=$TEMP_FINAL alpha=$ALPHA it=$ITERACOES op=$OPERADOR seed=$SEED..."
                        RESULTADO=$("$PROGRAMA" $TEMP_INICIAL $TEMP_FINAL $ALPHA $SEED $ITERACOES 1 $OPERADOR 0 | tail -n 1)
                        echo "$RESULTADO" >> "$SAIDA"
                    done
                done
            done
        done
    done
done

echo "Pronto! Resultados em $SAIDA"