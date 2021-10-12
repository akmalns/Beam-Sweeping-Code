#ifndef CODE_DOT_H
#define CODE_DOT_H

//Function Definition
int minimum(int a, int b);
int maximum(int a, int b);
int findH_min(int i,int C,int j, int T, int P1, int P2);
int findH_max(int i,int C,int j, int T, int P1, int P2);
float calculate_Alpha(int h, int hmin, int hmax, int i, int C, int j, int T, int T1, int T2);
float calculate_Beta(int h, int hmin, int hmax, int i, int C, int j, int T, int T1, int T2);
float total_contending_UE(float* slot, int maxAttempt);
void calculate_success_UE(float* contendingSlot, float* successSlot, int maxAttempt, float totalContendingUE, int channelNum);
void calculate_collided_UE(float* contendingSlot, float* collidedSlot, int maxAttempt, float totalContendingUE, int channelNum);
void calculate_contending_UE(int iPos, float* contendingSlot, int maxAttempt , float** collided_UE_array, int C, int j, int T, int T1, int T2);
void writeToCSV(float** contending, float** success, float** collided,int length,int maxAttempt);

#endif