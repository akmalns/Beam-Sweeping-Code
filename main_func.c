#include "code.h"
#include "main_func.h"
#include <stdio.h>
#include <math.h>


void main_func(int Imax, int maxAttempt, int C, int j, int T, int T1, int T2, int R,int m){
    //Allocating memory for UE status information
    int** contendingUE_array = (int**) calloc(Imax+1,sizeof(int*));
    for(int i=0;i<Imax+1;i++){
        contendingUE_array[i]=(int*) calloc(maxAttempt+1,sizeof(int));
    }

    int** successUE_array = (int**) calloc(Imax+1,sizeof(int*));
    for(int i=0;i<Imax+1;i++){
        successUE_array[i]=(int*) calloc(maxAttempt+1,sizeof(int));
    }

    int** collidedUE_array = (int**) calloc(Imax+1,sizeof(int*));
    for(int i=0;i<Imax+1;i++){
        collidedUE_array[i]=(int*) calloc(maxAttempt+1,sizeof(int));
    }

    //Initializing the first attempt of the m UE
    contendingUE_array[1][1] = m;
    contendingUE_array[1][2] = 0;
    contendingUE_array[1][3] = 0;
    calculate_success_UE(contendingUE_array[1],successUE_array[1],maxAttempt,total_contending_UE(contendingUE_array[1],maxAttempt),R);
    calculate_collided_UE(contendingUE_array[1],successUE_array[1],maxAttempt,total_contending_UE(contendingUE_array[1],maxAttempt),R);

    //Iterating through all UE array
    for(int i=2;i<=Imax;i++){
        calculate_contending_UE(i,contendingUE_array[i],maxAttempt,collidedUE_array,C,j,T,T1,T2);
        calculate_success_UE(contendingUE_array[1],successUE_array[1],maxAttempt,total_contending_UE(contendingUE_array[1],maxAttempt),R);
        calculate_collided_UE(contendingUE_array[1],successUE_array[1],maxAttempt,total_contending_UE(contendingUE_array[1],maxAttempt),R);
    }

    

    //Deallocating Memory
    for(int i=0;i<Imax+1;i++){
        free(contendingUE_array[i]);
    }
    free(contendingUE_array);

    for(int i=0;i<Imax+1;i++){
        free(successUE_array[i]);
    }
    free(successUE_array);

    for(int i=0;i<Imax+1;i++){
        free(collidedUE_array[i]);
    }
    free(collidedUE_array);
}