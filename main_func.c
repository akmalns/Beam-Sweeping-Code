#include "code.h"
#include "main_func.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void main_func(int length, int maxAttempt, int m, int C, int j, int T, int T1, int T2, int R){
    float totalContending;
    int raDuration = j;


    //Allocating memory for UE status information
    float** contendingUE_array = (float**) calloc(length+1,sizeof(float*));
    for(int i=0;i<length+1;i++){
        contendingUE_array[i]=(float*) calloc(maxAttempt+1,sizeof(float));
    }

    float** successUE_array = (float**) calloc(length+1,sizeof(float*));
    for(int i=0;i<length+1;i++){
        successUE_array[i]=(float*) calloc(maxAttempt+1,sizeof(float));
    }

    float** collidedUE_array = (float**) calloc(length+1,sizeof(float*));
    for(int i=0;i<length+1;i++){
        collidedUE_array[i]=(float*) calloc(maxAttempt+1,sizeof(float));
    }

    //Main Testing Program
    //Initialize contending UE with m on the first attempt (one-shot arrival)
    for(int i=0;i<length+1;i++){
            for(int j=0;j<maxAttempt+1;j++){
                if(i>=1 && i<=raDuration && j==1){
                    contendingUE_array[i][j]=(float)1000/raDuration;
                    successUE_array[i][j]=0;
                    collidedUE_array[i][j]=0;
                }else{
                    contendingUE_array[i][j]=0;
                    successUE_array[i][j]=0;
                    collidedUE_array[i][j]=0;
                }
            }
    }


    //Calculating Mi, Mis, Mif for all i value
    for(int i=0;i<length+1;i++){
       if(i>1){
            calculate_contending_UE(i,contendingUE_array[i],maxAttempt,collidedUE_array,C,j,T,T1,T2); //Calculate contending UE if i>1 (the first slot is the initial transmission of one-shot arrival process)
        }
        totalContending=total_contending_UE(contendingUE_array[i],maxAttempt);
        calculate_success_UE(contendingUE_array[i],successUE_array[i],maxAttempt,totalContending,R); //calculate success UE in a particular slot
        calculate_collided_UE(contendingUE_array[i],collidedUE_array[i],maxAttempt,totalContending,R); //calculate collided UE in a particular slot
        contendingUE_array[i][0]=totalContending;
    }

    printf("======This is contending UE======\n\n");
    
    for(int i=1;i<length+1;i++){
        for(int j=1;j<maxAttempt+1;j++){
            printf("%f",contendingUE_array[i][j]);
            printf("\t");
        }
        printf("\n");
    }

    printf("======This is Success UE======\n\n");
    
    for(int i=1;i<length+1;i++){
        for(int j=1;j<maxAttempt+1;j++){
            printf("%f",successUE_array[i][j]);
            printf("\t");
        }
        printf("\n");
    }

    printf("======This is Collided UE======\n\n");
    
    for(int i=1;i<length+1;i++){
        for(int j=1;j<maxAttempt+1;j++){
            printf("%f",collidedUE_array[i][j]);
            printf("\t");
        }
        printf("\n");
    }  

    writeToCSV(contendingUE_array,successUE_array,collidedUE_array,length,maxAttempt);
    //Deallocating Memory
    for(int i=0;i<length+1;i++){
        free(contendingUE_array[i]);
    }
    free(contendingUE_array);

    for(int i=0;i<length+1;i++){
        free(successUE_array[i]);
    }
    free(successUE_array);

    for(int i=0;i<length+1;i++){
        free(collidedUE_array[i]);
    }
    free(collidedUE_array);   
}

int main(){
    main_func(180,2,1000,1,6,60,60,0,112);
}