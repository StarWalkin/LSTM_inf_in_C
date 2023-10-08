//
// Created by Yuan on 2023/10/7.
//

#ifndef LSTM_INF_IN_C_OPERATORS_H
#define LSTM_INF_IN_C_OPERATORS_H
//矩阵乘法函数。res是结果矩阵，需要预先指定好size
void *matrix_mul(double *m1,double *m2,int row1,int col1,int row2,int col2, double res[]);
//此函数用于拼接向量，写在前面的在前
void cat_vector(double v1[],int n1,double v2[],int n2,double res[]);
void print_mat(double *mat,int row,int col);
double sigmoid(double x);
double tanh(double x);
double dot_product(double arr1[],double arr2[],int size);
void vector_add(double v1[],double v2[],int n,double res[]);
void hadamard_pro(double v1[],double v2[],int n,double res[]);
#endif //LSTM_INF_IN_C_OPERATORS_H
