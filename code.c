#include "code.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define W_BO_per_sigma 120

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

    if(C==1){
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
    if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 1
        // condition 1 to make sure the i is greater than T1 (located on the 2nd - nth frame)
        // condition 2 to make sure the i is still in the RA Slot
        // condition 3 to make sure the i is not the multiplication of T1 (the last element of T1 should not be RA Slot)
        // condition 4 to make sure the i is not in the Non-RA slot of T2
        // printf("This is case 1\n");
        x=i%T%(j+P1);
        hmin = (int) ceil((i-x-P1) - W_BO_per_sigma);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 2
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is not the first multiframe (one multiframe length is T, so i/T must be more than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        // printf("This is case 2\n");
        x=i%T%(j+P2);
        hmin = (int) ceil((i-x-P2) - W_BO_per_sigma);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 3
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is in the first multiframe (one multiframe length is T, so i/T must be less than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        // printf("This is case 3\n");
        x=i%T%(j+P2);
        hmin = (int) ceil((i-x+1) - W_BO_per_sigma);
    }else{
        // printf("Out of Case");
        hmin=-1;
    }
    
    return hmin;
}

int findH_max(int i,int C,int j, int T, int P1, int P2){
    int hmax;

    if(C==1){
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
    if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 1
        // condition 1 to make sure the i is greater than T1 (located on the 2nd - nth frame)
        // condition 2 to make sure the i is still in the RA Slot
        // condition 3 to make sure the i is not the multiplication of T1 (the last element of T1 should not be RA Slot)
        // condition 4 to make sure the i is not in the Non-RA slot of T2
        // printf("This is case 1\n");
        hmax = (int) floor(i-1);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 2
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is not the first multiframe (one multiframe length is T, so i/T must be more than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        // printf("This is case 2\n");
        hmax = (int) floor(i-1);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 3
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is in the first multiframe (one multiframe length is T, so i/T must be less than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        // printf("This is case 3\n");
        hmax = (int) floor(i-1);
    }else{
        // printf("Out of Case\n");
        hmax=-1;
    }
    
    return hmax;
}

float calculate_Alpha(int h, int hmin, int hmax, int i, int C, int j, int T, int T1, int T2){
    float alpha=0;
    int P1 = T1-j;
    int P2 = C==1 ? P1 : T2-j;
    int x;

    /*
    Case 1 : h will backoff in the 2nd until Nth frame in a multiframe
    Note : The non-RA time slot will be P1
    This case will happen if i located in the 2nd up to nth frame in a multiframe
    Alpha will be calculated from h

    Case 2 : h will backoff in the 1st frame in the subsequent multiframe starting from 2nd multiframe
    Note : The non-RA time slot will be P2
    This case will happen if i located in the first frame of the 2nd and the following multiframe

    Case 3 : h will backoff in the very first frame in the very first multiframe
    Note : the minimum value of h will be right before h+Wbo equal to i
    */

    if(hmin<0 && hmax<0){   //Check the value of h
        // printf("hmin and hmax < 0\n");
        alpha=0;
    }else if(h<0){
        // printf("h < 0\n");
        alpha=0;
    }else{
        if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 1
            // condition 1 to make sure the i is greater than T1 (located on the 2nd - nth frame)
            // condition 2 to make sure the i is still in the RA Slot
            // condition 3 to make sure the i is not the multiplication of T1 (the last element of T1 should not be RA Slot)
            // condition 4 to make sure the i is not in the Non-RA slot of T2
            // printf("Case 1\n");
            x = i%T%T1;
            if(i-x-P1-W_BO_per_sigma<h && h<i-x-P1){ // Make Sure h still in the range given by the equation
                // printf("entered conditional\n");
                alpha = (float) (1/j)*(minimum(h + W_BO_per_sigma,i-x+1)-maximum(i-x-P1,h))/W_BO_per_sigma;
                // printf("alpha = %f\n",alpha);
            }            //otherwise, alpha remain unchanged (0 value from the initialization)

        }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 2
            // condition 1 to make sure the i is located in the first frame (i%T<T1)
            // condition 2 to make sure the i is not the first multiframe (one multiframe length is T, so i/T must be more than 1)
            // condition 3 to make sure the i is still in the RA Slot
            // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
            // condition 5 to make sure i is not in the Non-RA slot of T2
            // printf("Case 2\n");
            x = i%T%T1;
            if(i-x-P2-W_BO_per_sigma<h && h<i-x-P2){ // Make Sure h still in the range given by the equation
                // printf("entered conditional\n");
                alpha = ((float) 1/j)*(minimum(h + W_BO_per_sigma,i-x+1)-maximum(i-x-P2,h))/W_BO_per_sigma;
                // printf("alpha = %f\n",alpha);
            }            //otherwise, alpha remain unchanged (0 value from the initialization)

        }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 3
            // condition 1 to make sure the i is located in the first frame (i%T<T1)
            // condition 2 to make sure the i is in the first multiframe (one multiframe length is T, so i/T must be less than 1)
            // condition 3 to make sure the i is still in the RA Slot
            // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
            // condition 5 to make sure i is not in the Non-RA slot of T2
            // printf("entered conditional\n");
            // printf("Case 3\n");
            alpha = 0; //No non-RA Slot before the first slot
            // printf("alpha = %f\n",alpha);

        }else{
            // printf("Other Case\n");
            alpha = 0;

        }
    }
        

    return alpha;
}

float calculate_Beta(int h, int hmin, int hmax, int i, int C, int j, int T, int T1, int T2){
    float beta=0;
    int P1 = T1-j;
    int P2 = C==1 ? P1 : T2-j;
    int x;

    /*
    Case 1 : h will backoff in the 2nd until Nth frame in a multiframe
    Note : The non-RA time slot will be P1
    This case will happen if i located in the 2nd up to nth frame in a multiframe
    Alpha will be calculated from h

    Case 2 : h will backoff in the 1st frame in the subsequent multiframe starting from 2nd multiframe
    Note : The non-RA time slot will be P2
    This case will happen if i located in the first frame of the 2nd and the following multiframe

    Case 3 : h will backoff in the very first frame in the very first multiframe
    Note : the minimum value of h will be right before h+Wbo equal to i
    */

    if(hmin<0 && hmax<0){   //Check the value of h
        // printf("hmin and hmax < 0\n");
        beta=0;
    }else if(h<0){
        // printf("h < 0\n");
        beta=0;
    }else if(h<hmin || h>hmax){
        // printf("h out of range\n");
        beta=0;
    }else{
        if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 1
            // condition 1 to make sure the i is greater than T1 (located on the 2nd - nth frame)
            // condition 2 to make sure the i is still in the RA Slot
            // condition 3 to make sure the i is not the multiplication of T1 (the last element of T1 should not be RA Slot)
            // condition 4 to make sure the i is not in the Non-RA slot of T2
            // printf("Case 1\n");
            x = i%T%T1;
            if(i-x+1-W_BO_per_sigma<h && h<=i-x-P1){ // Make Sure h still in the range given by the equation
                for(int p=maximum(0,h-i+x-1);p<minimum(x-1,h+W_BO_per_sigma-i+x-1);p++){
                    beta+=((float)1/(j-p-1));
                }
                beta = beta/W_BO_per_sigma;
            }else if(i-x+1<=h && h<=i-1){
                for(int p=maximum(0,h-i+x-1);p<minimum(x-1,h+W_BO_per_sigma-i+x-1);p++){
                    beta+=((float)1/(j-p-1));
                }
                beta = beta/W_BO_per_sigma;
            }   //otherwise, beta remain unchanged (0 value from the initialization)

        }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 2
            // condition 1 to make sure the i is located in the first frame (i%T<T1)
            // condition 2 to make sure the i is not the first multiframe (one multiframe length is T, so i/T must be more than 1)
            // condition 3 to make sure the i is still in the RA Slot
            // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
            // condition 5 to make sure i is not in the Non-RA slot of T2
            // printf("Case 2\n");
            x = i%T%T1;
            if(i-x+1-W_BO_per_sigma<h && h<i-1){ // Make Sure h still in the range given by the equation
                for(int p=maximum(0,h-i+x-1);p<minimum(x-1,h+W_BO_per_sigma-i+x-1);p++){
                    beta+=((float)1/(j-p-1));
                }
                beta = beta/W_BO_per_sigma;
            }else if(i-x+1<=h && h<=i-1){
                for(int p=maximum(0,h-i+x-1);p<minimum(x-1,h+W_BO_per_sigma-i+x-1);p++){
                    beta+=((float)1/(j-p-1));
                }
                beta = beta/W_BO_per_sigma;
            }   //otherwise, beta remain unchanged (0 value from the initialization)

        }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 3
            // condition 1 to make sure the i is located in the first frame (i%T<T1)
            // condition 2 to make sure the i is in the first multiframe (one multiframe length is T, so i/T must be less than 1)
            // condition 3 to make sure the i is still in the RA Slot
            // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
            // condition 5 to make sure i is not in the Non-RA slot of T2
            // printf("Case 3\n");
            x = i%T%T1;
            if(i-x+1-W_BO_per_sigma<h && h<i-1){ // Make Sure h still in the range given by the equation
                for(int p=maximum(0,h-i+x-1);p<minimum(x-1,h+W_BO_per_sigma-i+x-1);p++){
                    beta+=((float)1/(j-p-1));
                }
                beta = beta/W_BO_per_sigma;
            }else if(i-x+1<=h && h<=i-1){
                for(int p=maximum(0,h-i+x-1);p<minimum(x-1,h+W_BO_per_sigma-i+x-1);p++){
                    beta+=((float)1/(j-p-1));
                }
                beta = beta/W_BO_per_sigma;
            }   //otherwise, beta remain unchanged (0 value from the initialization)

        }else{
            // printf("Other Case\n");
            beta = 0;
        }
    }
        

    return beta;

}

float total_contending_UE(float* slot, int maxAttempt){
    float temp=0;
    for(int i=1;i<=maxAttempt+1;i++){
        temp+=slot[i];
    }

    return temp;
}

void calculate_success_UE(float* contendingSlot, float* successSlot, int maxAttempt, float totalContendingUE, int channelNum){
    for(int i=1;i<=maxAttempt+1;i++){
        successSlot[i]=contendingSlot[i]*exp(-1*totalContendingUE/channelNum);
    }
}

void calculate_collided_UE(float* contendingSlot, float* collidedSlot, int maxAttempt, float totalContendingUE, int channelNum){
    for(int i=1;i<=maxAttempt+1;i++){
        collidedSlot[i]=contendingSlot[i]*(1-exp(-1*totalContendingUE/channelNum));
    }
}

void calculate_contending_UE(int iPos, float* contendingSlot, int maxAttempt , float** collided_UE_array, int C, int j, int T, int T1, int T2){
    float alpha;
    float beta;
    int P1 = T1-j;
    int P2 = C==1 ? P1 : T2-j;
    int hmin;
    int hmax;
    float temp=0;

    // printf("iPos = %d\n",iPos);
    // printf("collided UE = %f\n",collided_UE_array[2]);
    // printf("enter hmin hmax calculation\n");
    hmin = findH_min(iPos,C,j,T,P1,P2);
    hmax = findH_max(iPos,C,j,T,P1,P2);
    for(int i=1;i<=maxAttempt;i++){
        if(i==1){
            // printf("check point 1\n");
            contendingSlot[i]=0;
        }else{
            // printf("check point 2\n");
            for(int h=maximum(1,hmin);h<=hmax;h++){
                // printf("print h value : %d\n",h);
                alpha=calculate_Alpha(h,hmin,hmax,iPos,C,j,T,T1,T2);
                // printf("print alpha value : %f\n",alpha);
                beta=calculate_Beta(h,hmin,hmax,iPos,C,j,T,T1,T2);
                // printf("print beta value : %f\n",beta);
                if(alpha>=0 && beta>=0){
                    // printf("conditional passed\n");
                    // printf("collided UE value = %f\n",collided_UE_array[h][i-1]);
                    temp+=(alpha+beta)*collided_UE_array[h][i-1];
                    // printf("collided UE value = %f\n",collided_UE_array[h][i-1]);
                    // printf("temp value = %f\n",temp);
                }
            }
            // printf("check point 3\n");
            // printf("temp value = %f\n",temp);
            contendingSlot[i]=temp;
            temp=0;
        }

    }
}

void writeToCSV(float** contending, float** success, float** collided,int length,int reattempt){
    FILE *fp;
    
    /*=======Saving Contending UE Data=======*/
    fp=fopen("contending.csv","w+");
    fprintf(fp,",");
    for(int j=1;j<length+1;j++){ //Printing Index
        fprintf(fp,"%d,",j);
    }
    fprintf(fp,"\n");
    for(int i=1;i<reattempt+2;i++){
        fprintf(fp,"%d,",i);
        for(int j=1;j<length+1;j++){
            fprintf(fp,"%f,",contending[j][i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);


    
    /*=======Saving Success UE Data=======*/
    fp=fopen("success.csv","w+");
    fprintf(fp,",");
    for(int j=1;j<length+1;j++){ //Printing Index
        fprintf(fp,"%d,",j);
    }
    fprintf(fp,"\n");
    for(int i=1;i<reattempt+2;i++){
        fprintf(fp,"%d,",i);
        for(int j=1;j<length+1;j++){
            fprintf(fp,"%f,",success[j][i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);


    
    /*=======Saving Collided UE Data=======*/
    fp=fopen("collided.csv","w+");
    fprintf(fp,",");
    for(int j=1;j<length+1;j++){ //Printing Index
        fprintf(fp,"%d,",j);
    }
    fprintf(fp,"\n");
    for(int i=1;i<reattempt+2;i++){
        fprintf(fp,"%d,",i);
        for(int j=1;j<length+1;j++){
            fprintf(fp,"%f,",collided[j][i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}