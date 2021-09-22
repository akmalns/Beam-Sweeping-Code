#include <stdio.h>
#include <math.h>

#define W_BO_per_sigma 240

int minimum(int a, int b){
    int returnValue;
    if(a<=b){
        returnValue = a;
    }else{
        returnValue = b;
    }

    return returnValue;
}

int maximum(int a, int b){
    int returnValue;
    if(a>=b){
        returnValue = a;
    }else{
        returnValue = b;
    }

    return returnValue;
}

int findH_min(int i,int C,int j, int T, int P1, int P2){
    int x;
    int hmin;

    if(P2==0){
        P2=P1;
    }

    /*
    Case 1 : h will backoff in the 2nd up to Nth frame in a multiframe
    Note : The non-RA time slot will be T1
    This case will happen if i located in the 2nd up to nth frame in a multiframe

    Case 2 : h will backoff in the 1st frame in the subsequent multiframe starting from 2nd multiframe
    Note : The non-RA time slot will be T2
    This case will happen if i located in the first frame of the 2nd and the following multiframe

    Case 3 : h will backoff in the very first frame in the very first multiframe
    Note : the minimum value of h will be right before h+Wbo equal to i
    */
    if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 1
        printf("This is case 1\n");
        x=i%T%(j+P1);
        hmin = (int) ceil((i-x-P1) - W_BO_per_sigma);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 2
        printf("This is case 2\n");
        x=i%T%(j+P2);
        hmin = (int) ceil((i-x-P2) - W_BO_per_sigma);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 3
        printf("This is case 3\n");
        hmin = (int) ceil((i-x+1) - W_BO_per_sigma);
    }else{
        printf("Out of Case");
        hmin=-1;
    }
    
    return hmin;
}

int findH_max(int C, int T, int T1, int T2, int i){
    int x;
    int hmax;

    /*
    Case 1 : h will backoff in the 2nd up to Nth frame in a multiframe
    Note : The non-RA time slot will be T1
    This case will happen if i located in the 2nd up to nth frame in a multiframe

    Case 2 : h will backoff in the 1st frame in the subsequent multiframe starting from 2nd multiframe
    Note : The non-RA time slot will be T2
    This case will happen if i located in the first frame of the 2nd and the following multiframe

    Case 3 : h will backoff in the very first frame in the very first multiframe
    Note : the minimum value of h will be right before h+Wbo equal to i
    */
    if((i%T)>T1 && (i%T)<(T-T2)){ //Case 1
        x=i%T%T1;
        hmax = (int) floor((i-x+1)-(W_BO_per_sigma));
    }else if((i%T)<T1 && (i/T)>1){ //Case 2
        x=i%T%T2;
        hmax = (int) floor((i-x+1)-(W_BO_per_sigma));
    }else if((i%T)<T1 && (i/T)<1){ //Case 3
        x=i%T%T1;
        hmax = (int) floor((i-x+1)-(W_BO_per_sigma));
    }else{
        hmax=-1;
    }
    
    return hmax;
}


int main(){
    //Testing hmin function

    int i=0;
    while(i!=-999){
        printf("Insert i : ");
        scanf("%d",&i);

        printf("%d\n",findH_min(i,1,6,60,54,0));
    }
    
}

