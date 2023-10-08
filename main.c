#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//// 随机初始化矩阵的函数
//void generate_random_matrix(int rows, int cols, float matrix[rows][cols]) {
//    // 使用时间作为随机数种子
//    srand(time(NULL));
//    // 填充矩阵的每个元素为随机浮点数（范围在0到1之间）
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            matrix[i][j] = (double)rand() / RAND_MAX;  // 生成0到1之间的随机浮点数
//        }
//    }
//}
//
//

int main() {
    //依次表示：输入的特征数量；输出的特征数量；hidden_layer的神经元个数
    int input_size, hidden_size, num_layers, seq_len;

    // 接收这些输入值
    printf("Please input the input_size, the hidden_size, the seq_len and num_layers in a row: \n");
    // 接收用户输入并将其分别赋值给变量
    scanf("%d %d %d %d", &input_size, &hidden_size, &seq_len, &num_layers);
    printf("successfully input\ninputsize: %d\nhidden_size: %d\nseq_len: %d\nnum_layers: %d\n",input_size,hidden_size,seq_len,num_layers);
    printf("Now please input the weight matrices:\n");

    //变量current_result用于存储当前这一层得到的h值，即当前层的输出
    double current_result[seq_len][hidden_size];


    //下面定义第一层需要的权重矩阵变量
    //Wf权重矩阵用于遗忘门，行数为hidden_size,列数为input_size+hidden_size,因为要和输入+上一个输出拼接成的向量相乘
    double Wf[hidden_size][input_size+hidden_size] ;
    //遗忘门计算时的bias
    double bf[hidden_size][1];
    //下面四个分别为记忆门对应的weight和bias
    double Wi[hidden_size][input_size+hidden_size] ;
    double bi[hidden_size][1];
    double Wc[hidden_size][input_size+hidden_size] ;
    double bc[hidden_size][1];
    //下面两个分别为输出门对应的weight和bias
    double Wo[hidden_size][input_size+hidden_size] ;
    double bo[hidden_size][1];

   //输入所有权重矩阵
    for (int layer_idx = 1;layer_idx <= num_layers;layer_idx++){

    }

    double input[seq_len][input_size];

    //使用变长数组来创建C_t和ht，注意：variable-sized object may not be initialized
    //注意：C_t和ht这两个是即时计算，即时更新的，所以各设定一个就够了
    double C_t[hidden_size] , ht[hidden_size] ;
    //按照一般的做法，将两个数组都初始化为全0
    for(int i = 0;i < hidden_size;i++){
        C_t[i] = 0;
        ht[i] = 0;
    }


    printf("Please input initial C_0");
    for(int i = 0;i < hidden_size;i++){
        scanf("%f",&C_t[i]);
    }
    for(int i = 0;i < hidden_size;i++){
        scanf("%f",&ht[i]);
    }



//    generate_random_matrix(hidden_size,input_size+hidden_size,Wf);
//    generate_random_matrix(hidden_size,input_size+hidden_size,Wi);
//    generate_random_matrix(hidden_size,input_size+hidden_size,Wc);
//    generate_random_matrix(hidden_size,input_size+hidden_size,Wo);

    //测试初始值是否正确赋值的程序
    for(int j = 0;j<hidden_size;j++){
        printf("%f \n",C_t[j]);
    }
    for(int i = 0;i<hidden_size;i++){
        for(int j = 0;j < input_size+hidden_size;j++){
            // 输出 i、j 和相应的元素
            printf("i: %d, j: %d, element: %f\n", i, j, Wf[i][j]);
        }
    }



    //正式开始计算！
    for(int layer_idx=1;layer_idx<num_layers;layer_idx++){

        for(int seq_idx=0;seq_idx<seq_len;seq_idx++){
            //calculate and update
        }
    }



    return 0;
}

