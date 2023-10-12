#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "operators.h"

#include "initialization.h"

int main() {


    //变量current_result用于存储当前这一层得到的h值，即当前层的输出
    double current_result[seq_len][hidden_size];


    //使用变长数组来创建C_t和ht，注意：variable-sized object may not be initialized
    //注意：C_t和ht这两个是即时计算，即时更新的，所以各设定一个就够了
    double C_t[hidden_size] , ht[hidden_size] ;
    //按照一般的做法，将两个数组都初始化为全0
    for(int i = 0;i < hidden_size;i++){
        C_t[i] = 0;
        ht[i] = 0;
    }
    double C0[hidden_size] , h0[hidden_size] ;
    for(int i = 0;i < hidden_size;i++){
        C0[i] = 0;
        h0[i] = 0;
    }

    //用来存每一层的ht输出组成的矩阵
    double output_matrix[seq_len][hidden_size];



    //正式开始计算！
    double ft[hidden_size],it[hidden_size],C_t1[hidden_size],ot[hidden_size];
    for(int layer_idx=0;layer_idx<num_layers;layer_idx++) {

        for (int seq_idx = 0; seq_idx < seq_len; seq_idx++) {
            //calculate and update


            if (layer_idx == 0) {
                //先拼接前一个cell的输出和这个cell对应的输入
                double cat_res[input_size + hidden_size];

//                    printf("%lf",input_matrix[0][1]);
                if (seq_idx == 0) {
                    cat_vector(input_matrix[0], input_size, h0, hidden_size, cat_res);
//                    printf("--------%d---------:",seq_idx);
//                    for (int k = 0; k < input_size + hidden_size; k++) {
//                        printf("catted %lf\n", cat_res[k]);
//
//                    }
//                            for(int k = 0;k<input_size+hidden_size;k++)  printf("%lf\n",cat_res[k]);
                }
                else {

                    cat_vector(input_matrix[seq_idx], input_size, ht, hidden_size, cat_res);
//                    for (int m=0;m<seq_len;m++) printf("%lf\n",input_matrix[seq_idx][m]);
//                    printf("--------%d---------:",seq_idx);
//                    for (int k = 0; k < input_size + hidden_size; k++) {
//                        printf("catted %lf\n", cat_res[k]);
//
//                    }

                }

//                    printf("%lf",cat_res[0]);


            //遗忘门
            double tmp[hidden_size];
            matrix_mul(Wf0, cat_res, hidden_size, input_size + hidden_size, input_size + hidden_size, 1, tmp);
//            printf("-------------------------");
//            for(int n = 0 ;n<hidden_size;n++){
//                printf("tmp:%lf\n", tmp[n]);
//            }
            vector_add(tmp, bf[layer_idx], hidden_size, ft);

//            for (int i = 0; i < hidden_size; i++) {
//                printf("seq_idx%d\n", seq_idx);
//                printf("ft%d:%lf\n", i, ft[i]);
//                ft[i] = sigmoid(ft[i]);
//                printf("tmp:%lf\n", tmp[i]);
//                printf("ft_after:%lf\n", ft[i]);
//            }

            //输入门
            matrix_mul(Wi0, cat_res, hidden_size, input_size + hidden_size, input_size + hidden_size, 1, tmp);
            vector_add(tmp, bf[layer_idx], hidden_size, it);
            for (int i = 0; i < hidden_size; i++) {
                it[i] = sigmoid(it[i]);
            }

            matrix_mul(Wc0, cat_res, hidden_size, input_size + hidden_size, input_size + hidden_size, 1, tmp);
            vector_add(tmp, bf[layer_idx], hidden_size, C_t1);
            for (int i = 0; i < hidden_size; i++) {
                C_t1[i] = tanh(C_t1[i]);
            }

            //Cell State
            double c1[hidden_size], c2[hidden_size];
            hadamard_pro(ft, C_t, hidden_size, c1);
            hadamard_pro(it, C_t1, hidden_size, c2);
            vector_add(c1, c2, hidden_size, C_t);

            //Output
            matrix_mul(Wo0, cat_res, hidden_size, input_size + hidden_size, input_size + hidden_size, 1, tmp);
            vector_add(tmp, bf[layer_idx], hidden_size, ot);
            for (int i = 0; i < hidden_size; i++) {
                ot[i] = sigmoid(ot[i]);
            }

            //derive ht
            for (int i = 0; i < hidden_size; i++) {
                ht[i] = tanh(C_t[i]) * ot[i];
                output_matrix[seq_idx][i] = ht[i];
            }

        }


            if (layer_idx > 0) {
                //先拼接前一个cell的输出和这个cell对应的输入
                double cat_res[2 * hidden_size];

                if (seq_idx == 0) cat_vector(output_matrix[0], hidden_size, h0, hidden_size, cat_res);
                else cat_vector(output_matrix[seq_idx], hidden_size, ht, hidden_size, cat_res);


                //遗忘门
                double tmp[hidden_size];
                matrix_mul(&Wf[(layer_idx - 1) * ((hidden_size) * (2 * hidden_size))], cat_res, hidden_size,
                           input_size + hidden_size, input_size + hidden_size, 1, tmp);
                vector_add(tmp, bf[layer_idx], hidden_size, ft);
                for (int i = 0; i < hidden_size; i++) {
                    ft[i] = sigmoid(ft[i]);
                }

                //输入门
                matrix_mul(&Wi[(layer_idx - 1) * ((hidden_size) * (2 * hidden_size))], cat_res, hidden_size,
                           input_size + hidden_size, input_size + hidden_size, 1, tmp);
                vector_add(tmp, bf[layer_idx], hidden_size, it);
                for (int i = 0; i < hidden_size; i++) {
                    it[i] = sigmoid(it[i]);
                }

                matrix_mul(&Wc[(layer_idx - 1) * ((hidden_size) * (2 * hidden_size))], cat_res, hidden_size,
                           input_size + hidden_size, input_size + hidden_size, 1, tmp);
                vector_add(tmp, bf[layer_idx], hidden_size, C_t1);
                for (int i = 0; i < hidden_size; i++) {
                    C_t1[i] = tanh(C_t1[i]);
                }

                //Cell State
                double c1[hidden_size], c2[hidden_size];
                hadamard_pro(ft, C_t, hidden_size, c1);
                hadamard_pro(it, C_t1, hidden_size, c2);
                vector_add(c1, c2, hidden_size, C_t);

                //Output
                matrix_mul(&Wo[(layer_idx - 1) * ((hidden_size) * (2 * hidden_size))], cat_res, hidden_size,
                           input_size + hidden_size, input_size + hidden_size, 1, tmp);
                vector_add(tmp, bf[layer_idx], hidden_size, ot);
                for (int i = 0; i < hidden_size; i++) {
                    ot[i] = sigmoid(ot[i]);
                }

                //derive ht
                for (int i = 0; i < hidden_size; i++) {
                    ht[i] = tanh(C_t[i]) * ot[i];
                    output_matrix[seq_idx][i] = ht[i];
                }

            }

        }
    }


    for(int i = 0;i <seq_len;i ++){
        printf("\noutput %d:\n",i);
        for(int j = 0;j < hidden_size;j ++){
            printf("%lf  ",output_matrix[i][j]);
        }
    }


    return 0;
}

