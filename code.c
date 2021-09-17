#include <stdio.h>
#include <math.h>

#define W_BO 50
#define sigma 10

int findH_min(int C, int T, int T1, int T2, int i, int j){
    int x = i%T;
    int hmin;

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
        hmin = (int) ceil((i-x-T1) - (W_BO)/sigma);
    }else if((i%T)<T1 && (i/T)>1){ //Case 2
        hmin = (int) ceil((i-x-T2) - (W_BO)/sigma);
    }else if((i%T)<T1 && (i/T)<1){ //Case 3
        hmin = (int) ceil((i-x+1) - (W_BO)/sigma);
    }
    
    return hmin;
}

int findH_max(int C, int T, int T1, int T2, int i, int j){
    int x = i%T;
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
        hmax = (int) floor((i-x+1)-(W_BO/sigma));
    }else if((i%T)<T1 && (i/T)>1){ //Case 2
        hmax = (int) floor((i-x+1)-(W_BO/sigma));
    }else if((i%T)<T1 && (i/T)<1){ //Case 3
        hmax = (int) floor((i-x+1)-(W_BO/sigma));
    }
    
    return hmax;
}

float calculate_alpha(int i, int ){
    
}


int main(){

}

