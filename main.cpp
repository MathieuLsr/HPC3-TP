#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include "utils.hpp"


using namespace std;
using namespace std::chrono;

#define SIDE 1000

//#define DEBUG
//#define D1
#define D2


int main() {

    int size = 0 ;


#ifdef D1

    size = SIDE ;

    // matrix allocation
    float * mat = (float *) calloc (SIDE,sizeof(float));
    float * mat_dt = (float *) calloc (SIDE,sizeof(float));

    // Application du point de chaleur en plein milieu de la matrice
    // mat[SIDE/2] = 255;

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("data.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    
    
    int size = 0 ; 
    while ((read = getline(&line, &len, fp)) != -1 && size != SIDE) {
        //printf("%d : %s\n", size, line) ;
        mat[size] = atof(line) ;
        size++ ;
        //printf("%s", line);
    }
    
    
    printf("size : %d\n", size) ;
    

    fclose(fp);

#endif

#ifdef D2
    // matrix allocation
    //float* mat = (float *) calloc (SIDE*SIDE,sizeof(float));

    string filename = "img.jpg" ;
	const int rows = 2160;
	const int cols = 3840;
    size = rows * cols ;

    float* mat = (float *) calloc (size,sizeof(float));
    float* mat_dt = (float *) calloc (size,sizeof(float));

    vector<unsigned char> imageBytes = convertImageToBlackAndWhite(filename, cols, rows);
    cout << "Convert image to vector<char>" << endl ;
    vector<float> imageFloats = convertUnsignedCharToFloat(mat, imageBytes) ;
    cout << "Convert image to vector<float>" << endl ;
    

#endif
    

    float nn,sn,en,wn, cp;
    float d2x, d2y;
    float h = 1;
    float dt = 0.1;
    float t = 0.1; // nb de secondes
    float F;

    int N = (int) (t/dt); // here we compute the number of iterations

    //time_t start = time(NULL) ;
    auto start = std::chrono::system_clock::now();

    
    for (int k = 0; k<N; k++){ // Boucle du temps & génère les équations simulées

    #ifdef D1

        for(int j = 0 ; j < SIDE ; j++){

            
            sn = mat[j];
        
            if (j == 0) wn = mat[j];
            else wn = mat[(j-1)];

            if (j == (SIDE-1)) en = mat[j];
            else en = mat[(j+1)];

            cp = mat [j];

            // Dérivées
            d2x = (en - 2*cp + wn)/(h*h); 

            F = d2x ;

            // Intégration dans le temps
            mat_dt[j] = mat [j] + dt*F;

        }

        memcpy (mat, mat_dt, sizeof(float)*SIDE*SIDE);
        // Mettre la nouvelle mat à la place de l'ancienne 

    #endif
    
    #ifdef D2
        for (int i = 0; i < rows ; i++){ 
            for (int j = 0; j < cols ; j++){

                if (i == 0) nn = mat[j + i*rows];
                else nn = mat[j + (i-1)*rows];

                if (i == (rows-1)) sn = mat[j + i*rows];
                else sn = mat[j + (i+1)*rows];
            
                if (j == 0) wn = mat[j + i*rows];
                else wn = mat[(j-1) + i*rows];

                if (j == (cols-1)) en = mat[j + i*rows];
                else en = mat[(j+1) + i*rows];

                cp = mat [j + i*rows];

                // Dérivées
                d2x = (en - 2*cp + wn)/(h*h); 
                d2y = (nn - 2*cp + sn)/(h*h);

                F = d2x + d2y;

                // Intégration dans le temps
                mat_dt[j + i*rows] = mat [j + i*rows] + dt*F;

            }
        }

        memcpy (mat, mat_dt, sizeof(float)*size);

    #endif
    
        
        
        // Potentiellement, faire uniquement un changement de pointeur (&mat = &mat_dt)
    }


    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "Time total : " << elapsed_seconds.count() << "s" << std::endl;

    cout << "Exemple des 10 premières valeurs : " << endl ;

    int i = 0 ; 
    for(float f : imageFloats){
        cout << f << "      ==>      " << mat[i] << endl ;
        i++; 
        if(i == 10) break ;
    }

    

    writeArrayToFile(mat_dt, size, "bytes_array_output.txt") ;

    

#ifdef DEBUG
#ifdef D1

    for (int i = 0; i < SIDE ; i++)
        printf("%.2f ", mat[i]);
    printf("\n") ;


#elif D2
    // print de test de valeurs - only for small images
    for (int i = 0; i < SIDE ; i++){ 
        for (int j = 0; j < SIDE ; j++) 
            printf("%.2f ", mat[j + i*SIDE]);
        printf("\n"); 
    }
  
#endif
#endif

  return (0);
}


/*

Parraleliser equation de dérivés partielles


*/