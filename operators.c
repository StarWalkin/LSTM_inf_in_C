#include <stdio.h>
#include <math.h>


void *matrix_mul(double *m1,double *m2,int row1,int col1,int row2,int col2, double res[]){
    if (col1 != row2) printf("Illegal size!");
    for(int idx1=0;idx1<row1;idx1++){
        for(int idx2=0;idx2<col2;idx2++){
            for(int i=0;i<col1;i++){
                res[col2*idx1+idx2] += m1[idx1*col1+i]*m2[i*col2+idx2];
            }

        }
    }
}

void cat_vector(double v1[],int n1,double v2[],int n2,double res[]){
    for(int i = 0;i< n1;i ++){
        res[i] = v1[i];
    }
    for(int i = n1;i < n1+n2;i ++){
        res[i] = v2[i-n1];
    }
}

void print_mat(double *mat,int row,int col){
    for (int i = 0;i < row;i ++){
        for(int j = 0;j < col;j ++){
            printf("%.2f\n",mat[i*col+j]);
        }
    }
}

// Sigmoid函数
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Tanh函数
double tanh(double x) {
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

//计算两向量点积
double dot_product(double arr1[],double arr2[],int size){
    double res = 0;
    for (int i = 0;i < size;i += 1){
        res += arr1[i]*arr2[i];
    }
    return res;
}


