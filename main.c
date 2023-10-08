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
    printf("Enter input size: ");
    scanf("%d", &input_size);

    printf("Enter hidden size: ");
    scanf("%d", &hidden_size);

    printf("Enter sequence length: ");
    scanf("%d", &seq_len);

    printf("Enter number of layers: ");
    scanf("%d", &num_layers);

    printf("successfully input！Please check as follows\ninputsize: %d\nhidden_size: %d\nseq_len: %d\nnum_layers: %d\n",input_size,hidden_size,seq_len,num_layers);

    printf("Now please input the weight matrices:\n");

    //变量current_result用于存储当前这一层得到的h值，即当前层的输出
    double current_result[seq_len][hidden_size];


    //下面定义第一层需要的权重矩阵变量（因为第一层输入的size跟其他层不一样，故单独处理）
    //Wf权重矩阵用于遗忘门，行数为hidden_size,列数为input_size+hidden_size,因为要和输入+上一个输出拼接成的向量相乘
    double Wf0[hidden_size*(input_size+hidden_size)] ;
    double Wi0[hidden_size*(input_size+hidden_size)] ;
    double Wc0[hidden_size*(input_size+hidden_size)];
    double Wo0[hidden_size*(input_size+hidden_size)] ;
    //然后来写一段读入第一层权重矩阵的程序
    printf("Wf0,size:%d * %d\n",hidden_size,input_size+hidden_size);
    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
        scanf("%f",&Wf0[i]);
    }
    printf("\nWi0,size:%d * %d\n",hidden_size,input_size+hidden_size);
    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
        scanf("%f",&Wi0[i]);
    }
    printf("\nWc0,size:%d * %d\n",hidden_size,input_size+hidden_size);
    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
        scanf("%f",&Wc0[i]);
    }
    printf("\nWo0,size:%d * %d\n",hidden_size,input_size+hidden_size);
    for(int i = 0;i < hidden_size*(input_size+hidden_size);i ++){
        scanf("%f",&Wo0[i]);
    }
    //如果有多层，还需要输入上面几层的权重矩阵
    if(num_layers > 1){
        double Wf[(num_layers-1)*((hidden_size)*(2*hidden_size))];
        double Wi[(num_layers-1)*((hidden_size)*(2*hidden_size))];
        double Wc[(num_layers-1)*((hidden_size)*(2*hidden_size))];
        double Wo[(num_layers-1)*((hidden_size)*(2*hidden_size))];

        for(int layer_idx = 0;layer_idx < num_layers-1;layer_idx++){
            printf("\nThe %dth layer:\n",layer_idx+2);
            printf("Wf,size:%d * %d\n",hidden_size,2*hidden_size);
            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
                scanf("%f",&Wf[layer_idx*((hidden_size)*(2*hidden_size))+i]);
            }
            printf("\nWi,size:%d * %d\n",hidden_size,2*hidden_size);
            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
                scanf("%f",&Wi0[layer_idx*((hidden_size)*(2*hidden_size))+i]);
            }
            printf("\nWc,size:%d * %d\n",hidden_size,2*hidden_size);
            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
                scanf("%f",&Wc0[layer_idx*((hidden_size)*(2*hidden_size))+i]);
            }
            printf("\nWo,size:%d * %d\n",hidden_size,2*hidden_size);
            for(int i = 0;i < ((hidden_size)*(2*hidden_size));i ++){
                scanf("%f",&Wo0[layer_idx*((hidden_size)*(2*hidden_size))+i]);
            }
        }
    }

    //遗忘门计算时的bias
    double bf[num_layers*hidden_size];
    //下面记忆门对应的bias
    double bi[num_layers*hidden_size];
    double bc[num_layers*hidden_size];
    //输出门对应的bias
    double bo[num_layers*hidden_size];

   //输入所有bias
    for (int layer_idx = 1;layer_idx <= num_layers;layer_idx++){
        printf("\nThe %dth layer:\n",layer_idx);
        printf("bf:\n");
        for(int i = 0;i < hidden_size;i ++){
            scanf("%f",&bf[hidden_size*layer_idx+i]);
        }
        printf("bi:\n");
        for(int i = 0;i < hidden_size;i ++){
            scanf("%f",&bi[hidden_size*layer_idx+i]);
        }
        printf("bc:\n");
        for(int i = 0;i < hidden_size;i ++){
            scanf("%f",&bc[hidden_size*layer_idx+i]);
        }
        printf("bo:\n");
        for(int i = 0;i < hidden_size;i ++){
            scanf("%f",&bo[hidden_size*layer_idx+i]);
        }
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
    double C0[hidden_size] , h0[hidden_size] ;
    printf("Please input initial C0\n");
    for(int i = 0;i < hidden_size;i++){
        scanf("%f",&C0[i]);
    }
    printf("Please input initial h0\n");
    for(int i = 0;i < hidden_size;i++){
        scanf("%f",&h0[i]);
    }

    //用来存每一层的ht输出组成的矩阵
    double output_matrix[hidden_size][seq_len];


    //正式开始计算！
    for(int layer_idx=0;layer_idx<num_layers;layer_idx++){

        for(int seq_idx=0;seq_idx<seq_len;seq_idx++){
            //calculate and update


        }
    }



    return 0;
}

