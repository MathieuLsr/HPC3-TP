#include <stdio.h>
#include <omp. h>

void loop(int num_thread) {
    omp_set_num_threads(num_thread) ;
    printf ("\nAvec %d tâches:\n", num_thread) ; 
    #pragma omp parallel for
    
    for(int i = 1; i <= 50; i++) {
        int tid = omp get thread num();
        printf ("Tâche %d: %d\n", tid,i);
    }
}



int main() {
    int i, num_thread;

    printf ("Boucle avec une seule tâche:\n");
    for(i = 1; i < 50; i++) printf ("%d\n", i) ;
    
    num_thread = 2 ;
    loop(num_thread) ;

    num_thread = 3 ;
    loop(num_thread) ;
    
    num_thread = 4 ;
    loop(num_thread) ;

}