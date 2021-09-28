#ifndef CODE_DOT_H
#define CODE_DOT_H

//Function Definition
int minimum(int a, int b);
int maximum(int a, int b);
int findH_min(int i,int C,int j, int T, int P1, int P2);
int findH_max(int i,int C,int j, int T, int P1, int P2);
float calculate_Alpha(int h, int hmin, int hmax, int i, int C, int j, int T, int T1, int T2);
float calculate_Beta(int h, int hmin, int hmax, int i, int C, int j, int T, int T1, int T2);

#endif