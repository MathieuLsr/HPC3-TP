#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    
    // Comptage en utilisant une simple boucle
    printf("Comptage avec une seule tâche:\n");
    for(i = 1; i <= 50; i++) {
        printf("%d\n", i);
    }

    // Comptage en utilisant OpenMP avec 2 tâches
    printf("\nComptage avec 2 tâches:\n");
    #pragma omp parallel num_threads(2)
    {
        int j;
        int tid = omp_get_thread_num();
        for(j = 1; j <= 25; j++) {
            printf("Tâche %d: %d\n", tid, (j + tid*25));
        }
    }

    // Comptage en utilisant OpenMP avec 3 tâches
    printf("\nComptage avec 3 tâches:\n");
    #pragma omp parallel num_threads(3)
    {
        int k;
        int tid = omp_get_thread_num();
        for(k = 1; k <= 17; k++) {
            printf("Tâche %d: %d\n", tid, (k + tid*17));
        }
    }

    // Comptage en utilisant OpenMP avec 4 tâches
    printf("\nComptage avec 4 tâches:\n");
    #pragma omp parallel num_threads(4)
    {
        int l;
        int tid = omp_get_thread_num();
        for(l = 1; l <= 13; l++) {
            printf("Tâche %d: %d\n", tid, (l + tid*13));
        }
    }
    
    return 0;
}
