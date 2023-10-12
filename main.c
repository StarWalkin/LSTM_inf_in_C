#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "operators.h"

#include "initialization.h"

int main() {
//    //依次表示：输入的特征数量；输出的特征数量；hidden_layer的神经元个数
//    int input_size, hidden_size, num_layers, seq_len, output_size;
//
//    // 接收这些输入值
//    printf("Please input the input_size, the hidden_size, the seq_len and num_layers in a row: \n");
//
//    // 接收用户输入并将其分别赋值给变量
//    printf("Enter input size: ");
//    scanf("%d", &input_size);
//
//    printf("Enter hidden size: ");
//    scanf("%d", &hidden_size);
//
//    printf("Enter sequence length: ");
//    scanf("%d", &seq_len);
//
//    printf("Enter number of layers: ");
//    scanf("%d", &num_layers);
//
//    printf("successfully input！Please check as follows\ninputsize: %d\nhidden_size: %d\nseq_len: %d\nnum_layers: %d\n",input_size,hidden_size,seq_len,num_layers);
//
//    printf("Now please input the weight matrices:\n");

//    printf("%lf\n",Wf0[0]);
//    printf("%lf\n",Wf[100]);

//    printf("%lf\n",input_matrix[0][1]);

    //变量current_result用于存储当前这一层得到的h值，即当前层的输出
    double current_result[seq_len][hidden_size];


    //下面定义第一层需要的权重矩阵变量（因为第一层输入的size跟其他层不一样，故单独处理）
    //Wf权重矩阵用于遗忘门，行数为hidden_size,列数为input_size+hidden_size,因为要和输入+上一个输出拼接成的向量相乘
//    double Wf0[hidden_size*(input_size+hidden_size)] ;
//    double Wi0[hidden_size*(input_size+hidden_size)] ;
//    double Wc0[hidden_size*(input_size+hidden_size)];
//    double Wo0[hidden_size*(input_size+hidden_size)] ;
//    //然后来写一段读入第一层权重矩阵的程序
//    printf("Wf0,size:%d * %d\n",hidden_size,input_size+hidden_size);
//    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
//        scanf("%lf",&Wf0[i]);
//    }
//    printf("\nWi0,size:%d * %d\n",hidden_size,input_size+hidden_size);
//    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
//        scanf("%lf",&Wi0[i]);
//    }
//    printf("\nWc0,size:%d * %d\n",hidden_size,input_size+hidden_size);
//    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
//        scanf("%lf",&Wc0[i]);
//    }
//    printf("\nWo0,size:%d * %d\n",hidden_size,input_size+hidden_size);
//    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
//        scanf("%lf",&Wo0[i]);
//    }
//    //如果有多层，还需要输入上面几层的权重矩阵
//    double Wf[(num_layers-1)*((hidden_size)*(2*hidden_size))];
//    double Wi[(num_layers-1)*((hidden_size)*(2*hidden_size))];
//    double Wc[(num_layers-1)*((hidden_size)*(2*hidden_size))];
//    double Wo[(num_layers-1)*((hidden_size)*(2*hidden_size))];

    if(num_layers > 1){
//        double Wf[(num_layers-1)*((hidden_size)*(2*hidden_size))];
//        double Wi[(num_layers-1)*((hidden_size)*(2*hidden_size))];
//        double Wc[(num_layers-1)*((hidden_size)*(2*hidden_size))];
//        double Wo[(num_layers-1)*((hidden_size)*(2*hidden_size))];

//        for(int layer_idx = 0;layer_idx < num_layers-1;layer_idx++){
//            printf("\nThe %dth layer:\n",layer_idx+2);
//            printf("Wf,size:%d * %d\n",hidden_size,2*hidden_size);
//            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
//                scanf("%lf",&Wf[layer_idx*((hidden_size)*(2*hidden_size))+i]);
//            }
//            printf("\nWi,size:%d * %d\n",hidden_size,2*hidden_size);
//            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
//                scanf("%lf",&Wi0[layer_idx*((hidden_size)*(2*hidden_size))+i]);
//            }
//            printf("\nWc,size:%d * %d\n",hidden_size,2*hidden_size);
//            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
//                scanf("%lf",&Wc0[layer_idx*((hidden_size)*(2*hidden_size))+i]);
//            }
//            printf("\nWo,size:%d * %d\n",hidden_size,2*hidden_size);
//            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
//                scanf("%lf",&Wo0[layer_idx*((hidden_size)*(2*hidden_size))+i]);
//            }
//        }
    }

//    //遗忘门计算时的bias
//    double bf[num_layers][hidden_size];
//    //下面记忆门对应的bias
//    double bi[num_layers][hidden_size];
//    double bc[num_layers][hidden_size];
//    //输出门对应的bias
//    double bo[num_layers][hidden_size];

   //输入所有bias
//    for (int layer_idx = 1;layer_idx <= num_layers;layer_idx++){
//        printf("\nThe %dth layer:\n",layer_idx);
//        printf("bf:\n");
//        for(int i = 0;i < hidden_size;i ++){
//            scanf("%lf",&bf[hidden_size*layer_idx+i]);
//        }
//        printf("bi:\n");
//        for(int i = 0;i < hidden_size;i ++){
//            scanf("%lf",&bi[hidden_size*layer_idx+i]);
//        }
//        printf("bc:\n");
//        for(int i = 0;i < hidden_size;i ++){
//            scanf("%lf",&bc[hidden_size*layer_idx+i]);
//        }
//        printf("bo:\n");
//        for(int i = 0;i < hidden_size;i ++){
//            scanf("%lf",&bo[hidden_size*layer_idx+i]);
//        }
//    }

//    double input[seq_len][input_size];

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
//    printf("Please input initial C0\n");
//    for(int i = 0;i < hidden_size;i++){
//        scanf("%lf",&C0[i]);
//    }
//    printf("Please input initial h0\n");
//    for(int i = 0;i < hidden_size;i++){
//        scanf("%lf",&h0[i]);
//    }

    //输入序列
//    double input_matrix[seq_len][input_size] = {{0.1, 0.2, 0.3}, {0.2, 0.3, 0.4}, {0.3, 0.4, 0.5}};
//    double input_matrix[seq_len][input_size];
//    printf("input the input matrix:");
//    for(int i = 0;i < seq_len;i ++){
//        printf("%d th vector:\n",i+1);
//        for(int j = 0;j < input_size;j ++){
//            scanf("%lf",&input_matrix[i][j]);
//        }
//    }

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
                    printf("--------%d---------:",seq_idx);
                    for (int k = 0; k < input_size + hidden_size; k++) {
                        printf("catted %lf\n", cat_res[k]);

                    }
//                            for(int k = 0;k<input_size+hidden_size;k++)  printf("%lf\n",cat_res[k]);
                }
                else {

                    cat_vector(input_matrix[seq_idx], input_size, ht, hidden_size, cat_res);
                    for (int m=0;m<seq_len;m++) printf("%lf\n",input_matrix[seq_idx][m]);
                    printf("--------%d---------:",seq_idx);
                    for (int k = 0; k < input_size + hidden_size; k++) {
                        printf("catted %lf\n", cat_res[k]);

                    }

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

