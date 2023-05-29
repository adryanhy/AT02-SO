#include <stdio.h>
#include <stdlib.h>

void lru(int *referencias, int num_referencias, int num_paginas, int *paginas, int *faltas_pagina) {
    int i, j, k;
    int *temp = (int *)malloc(num_paginas * sizeof(int));

    for (i = 0; i < num_paginas; i++)
        paginas[i] = -1;

    for (i = 0; i < num_referencias; i++) {
        int pagina_referenciada = referencias[i];
        int pagina_presente = 0;

        // Verificar se a página já está na memória
        for (j = 0; j < num_paginas; j++) {
            if (paginas[j] == pagina_referenciada) {
                pagina_presente = 1;
                break;
            }
        }

        // Se a página não estiver na memória, substituir a página menos recentemente usada
        if (!pagina_presente) {
            (*faltas_pagina)++;

            // Encontrar a página menos recentemente usada
            for (j = 0; j < num_paginas; j++)
                temp[j] = 0;

            for (j = i - 1, k = 1; k < num_paginas; k++) {
                if (j < 0)
                    j = num_referencias - 1;

                for (; j >= 0 && referencias[j] != paginas[k]; j--)
                    temp[k]++;
            }

            // Encontrar a página com o maior valor em temp[]
            int pagina_substituir = 0;
            for (j = 1; j < num_paginas; j++) {
                if (temp[j] > temp[pagina_substituir])
                    pagina_substituir = j;
            }

            // Substituir a página
            paginas[pagina_substituir] = pagina_referenciada;
        }
    }

    free(temp);
}

int main() {
    int num_paginas, num_referencias;

    printf("Digite a quantidade de paginas para simular o algoritmo: ");
    scanf("%d", &num_paginas);

    printf("Digite o numero de referencias: ");
    scanf("%d", &num_referencias);

    int *referencias = (int *)malloc(num_referencias * sizeof(int));
    printf("Digite os valores das referencias: ");
    for (int i = 0; i < num_referencias; i++) {
        scanf("%d", &referencias[i]);
    }

    int *paginas = (int *)malloc(num_paginas * sizeof(int));
    int faltas_pagina = 0;

    lru(referencias, num_referencias, num_paginas, paginas, &faltas_pagina);

    printf("\nConteudo final das paginas de memoria:\n");
    for (int i = 0; i < num_paginas; i++) {
        if (paginas[i] == -1)
            printf("Vazia, ");
        else
            printf("[%d], ", paginas[i]);
    }

    printf("\nQuantidade de faltas de pagina: %d\n", faltas_pagina);

    free(referencias);
    free(paginas);

    return 0;
}
