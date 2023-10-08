////测试初始值是否正确赋值的程序
//for(int j = 0;j<hidden_size;j++){
//printf("%f \n",C_t[j]);
//}
//for(int i = 0;i<hidden_size;i++){
//for(int j = 0;j < input_size+hidden_size;j++){
//// 输出 i、j 和相应的元素
//printf("i: %d, j: %d, element: %f\n", i, j, Wf[i][j]);
//}
//}
////
//// Created by Yuan on 2023/10/8.
////
//
//
////    generate_random_matrix(hidden_size,input_size+hidden_size,Wf);
////    generate_random_matrix(hidden_size,input_size+hidden_size,Wi);
////    generate_random_matrix(hidden_size,input_size+hidden_size,Wc);
////    generate_random_matrix(hidden_size,input_size+hidden_size,Wo);
//
//
//

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
