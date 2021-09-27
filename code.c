#include <stdio.h>
#include <math.h>

#define W_BO_per_sigma 240
#define sigma 0.125/6
#define W_BO 5

float minimum(float a, float b){
    float returnValue;
    if(a<=b){
        returnValue = a;
    }else{
        returnValue = b;
    }

    return returnValue;
}

float maximum(float a, float b){
    float returnValue;
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
        printf("This is case 1\n");
        x=i%T%(j+P1);
        hmin = (int) ceil((i-x-P1) - W_BO_per_sigma);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 2
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is not the first multiframe (one multiframe length is T, so i/T must be more than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        printf("This is case 2\n");
        x=i%T%(j+P2);
        hmin = (int) ceil((i-x-P2) - W_BO_per_sigma);
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 3
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is in the first multiframe (one multiframe length is T, so i/T must be less than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        printf("This is case 3\n");
        x=i%T%(j+P2);
        hmin = (int) ceil((i-x+1) - W_BO_per_sigma);
    }else{
        printf("Out of Case");
        hmin=-1;
    }
    
    return hmin;
}

int findH_max(int i,int C,int j, int T, int P1, int P2){
    int x;
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
        printf("This is case 1\n");
        x=i%T%(j+P1);
        hmax = (int) floor((i-x+1)-(W_BO_per_sigma));
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 2
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is not the first multiframe (one multiframe length is T, so i/T must be more than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        printf("This is case 2\n");
        x=i%T%(j+P2);
        hmax = (int) floor((i-x+1)-(W_BO_per_sigma));
    }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0 && (i%T)<(T-P2+1)){ //Case 3
        // condition 1 to make sure the i is located in the first frame (i%T<T1)
        // condition 2 to make sure the i is in the first multiframe (one multiframe length is T, so i/T must be less than 1)
        // condition 3 to make sure the i is still in the RA Slot
        // condition 4 to make sure the i is note the multiplication of T1 (because T,2T,3T is not RA slot but the last slot of Non-RA Slot)
        // condition 5 to make sure i is not in the Non-RA slot of T2
        printf("This is case 3\n");
        x=i%T%(j+P1);
        hmax = (int) floor((i-x+1)-(W_BO_per_sigma));
    }else{
        printf("Out of Case\n");
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
        alpha=0;
    }else if(h<0){
        alpha=0;
    }else{
        if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 1

            x = i%T%T1;
            if(i-x-P1-W_BO_per_sigma<h && h<i-x-P1){ // Make Sure h still in the range given by the equation
                alpha = (float) (1/j)*(minimum(h*sigma + W_BO,(i-x+1)*sigma)-maximum((i-x-P1)*sigma,h*sigma))/W_BO;
            }            //otherwise, alpha remain unchanged (0 value from the initialization)

        }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 2

            x = i%T%T1;
            if(i-x-P2-W_BO_per_sigma<h && h<i-x-P1){ // Make Sure h still in the range given by the equation
                alpha = (float) (1/j)*(minimum(h*sigma + W_BO,(i-x+1)*sigma)-maximum((i-x-P2)*sigma,h*sigma))/W_BO;
            }            //otherwise, alpha remain unchanged (0 value from the initialization)

        }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 3

            alpha = 0; //No non-RA Slot before the first slot

        }else{

            alpha = 0;

        }
    }
        

    return alpha;
}

// float calculate_Beta(int h, int i, int C, int j, int T, int T1, int T2){
//     float beta=0;
//     int P1 = T1-j;
//     int P2 = C==1 ? 0 : T2-j;
//     int hmin = findH_min(i,C,j,T,P1,P2);
//     int hmax = findH_max(i,C,j,T,P1,P2);
//     int x;

//     /*
//     Case 1 : h will backoff in the 2nd until the Nth frame in a multiframe
//     Note : The non-RA time slot will be P1
//     This case will happen if i located in the 2nd up to nth frame in a multiframe
//     Alpha will be calculated from h

//     Case 2 : h will backoff in the 1st frame in the subsequent multiframe starting from 2nd multiframe
//     Note : The non-RA time slot will be P2
//     This case will happen if i located in the first frame of the 2nd and the following multiframe

//     Case 3 : h will backoff in the very first frame in the very first multiframe
//     Note : the minimum value of h will be right before h+Wbo equal to i
//     */

//     if(hmin<0 && hmax<0){   //Check the value of h
//         beta=0;
//     }else if(h<hmin || h>hmax){
//         beta=0;
//     }else{
//         if((i%T)>(j+P1) && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 1

//             x = i%T%T1;

//             if(i-x+1-W_BO_per_sigma<h && h<i-x-P1){
//                 for(int p=1;p<minimum((float)(h+W_BO_per_sigma),(float)(x));p++){
//                     beta+=(float)(1/(j-p))*sigma*1/W_BO;
//                 }
//             }
            
            
//         }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)>1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 2

//             x = i%T%T1;
            
//         }else if((i%T%(j+P1))<(j+P1) && ((float)i/T)<1 && (abs(i%T%(j+P1)-1))<j && i%T%(j+P1)!=0){ //Case 3

            
//         }else{
            
//         }
//     }

//     return beta;

// }

int main(){
    //Testing hmin function

    // int i=0;
    // while(i!=-999){
    //     printf("Insert i : ");
    // scanf("%d",&i);

    // printf("%d\n",findH_min(i,3,1,60,1,55));
    // }
   

    //Testing hmax function
    // printf("%f\n",sigma);
    int i=0;
    while(i!=-999){
        printf("Insert i : ");
    scanf("%d",&i);

    printf("%d\n",findH_max(i,3,1,60,1,55));
    }
}

