package program;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by douglas.leite on 19/05/2017.
 */
public class BacktrackA {
    public static class QueensProblem {
        int size;
        // Utilizando vetor para representar a matriz resultado:
        // Podemos fazer isso já que a regra de posicionamento das rainhas
        //impede que haja mais de uma na mesma linha ou coluna.

        // VETOR[i] = j --> MATRIZ[i][j]
        int[] res;

        // Contador de resultados localizados
        int results = 0;
        // Lista de resultados
        //Frescura, só para salvar em um arquivo as matrizes.
        List<int[]> resultsList = new ArrayList<>();

        QueensProblem(int s) {
            this.size = s;
            res = new int[s];
            //Começo da execução
            long startTime = System.currentTimeMillis();

            resolve(0);

            //Fim da execução
            long stopTime = System.currentTimeMillis();
            long elapsedTime = stopTime - startTime;

            System.out.println("\nTamanho:" + s + " -> Tempo de execução: " + elapsedTime + "ms\n");
        }

        boolean check(int x, int y) {
            // Verifica se:
            //Não esta na mesma coluna de uma rainha existente (x = i)
            for (int i = 0; i < x; i++) {
                //Não está na mesma linha que uma rainha existente (y = j)
                if (res[i] == y) return false;
                //if (Math.abs(i - x) == Math.abs(res[i] - y)) return false;
                //Não está na mesma diagonal que uma rainha existente (|i - x| = |j - y|)
                if ((res[i] - y) == (x - i)) return false;
                //Não está na mesma diagonal que uma rainha existente (|i - x| = |j - y|)
                if ((y - res[i]) == (x - i)) return false;
            }
            return true;
        }

        boolean resolve(int i) {
            //Só verifica se não achou x resultados.
            if (results < 1) {
                for (int j = 0; j < this.size; j++) {
                    //Verifica se pode inserir uma rainha nessa posição (ij).
                    if (check(i, j)) {
                        //Se sim, insere ela.
                        res[i] = j;
                        //Se ela foi inserida na ultima coluna, então é uma solução completa.
                        if (i == size - 1) {
                            //aumenta a quantidade de resultados
                            results++;
                            //adiciona o resultado a lista
                            resultsList.add(res.clone());
                            //e exibe ele na tela (para acompanhar a demora entre cada resultado)
                            System.out.print("\n" + Arrays.toString(res));
                        }
                        //Chama a solução para a próxima coluna.
                        resolve(i + 1);
                    }
                }
            } else {
                return false;
            }
            return true;
        }
    }

    public static void main(String args[]) {

        int[] sizes = {4, 8, 16, 32, 64};

        for (int size : sizes) {
            QueensProblem p = new QueensProblem(size);

            try {
                PrintWriter writer = new PrintWriter(size + ".txt", "UTF-8");
                for (int[] result : p.resultsList) {
                    for (int i = 0; i < size; i++) {
                        StringBuilder line = new StringBuilder();
                        for (int j = 0; j < size; j++) {
                            if (result[i] == j) {
                                line.append("X ");
                            } else {
                                line.append("0 ");
                            }
                        }
                        writer.println(line);
                    }
                    writer.println("\n");
                }
                writer.close();
            } catch (IOException e) {
                // do something
            }
        }
    }
}