import torch
import torch.nn as nn
from print_into_c import *
import math

path_h = '/Users/yuan/Desktop/科研竞赛/ANL-瑞萨项目/LSTM_inf_in_C/initialization.h'
path_c = '/Users/yuan/Desktop/科研竞赛/ANL-瑞萨项目/LSTM_inf_in_C/initialization.c'


# 创建一个简单的LSTM模型（目的是用于后续比对、验证）
class LSTMModel(nn.Module):
    def __init__(self, input_size, hidden_size, num_layers):
        super(LSTMModel, self).__init__()
        self.hidden_size = hidden_size
        self.num_layers = num_layers

        # LSTM层
        self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)

    def forward(self, x):
        # 初始化LSTM的隐藏状态和记忆单元
        h0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size).to(x.device)
        c0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size).to(x.device)

        # 前向传播
        out, _ = self.lstm(x, (h0, c0))
        return out


# 定义模型参数
input_size = 3  # 输入特征维度
hidden_size = 64  # LSTM隐藏层大小
num_layers = 1  # LSTM层数

# 创建LSTM模型实例
model = LSTMModel(input_size, hidden_size, num_layers)

# 随机初始化模型权重
def init_weights(m):
    if isinstance(m, nn.Linear):
        nn.init.xavier_uniform_(m.weight)
        nn.init.zeros_(m.bias)
    elif isinstance(m, nn.LSTM):
        for name, param in m.named_parameters():
            if 'weight' in name:
                nn.init.xavier_uniform_(param)
            elif 'bias' in name:
                nn.init.zeros_(param)

model.apply(init_weights)

# 设置模型为推理模式
model.eval()

# 构造一个输入序列（示例输入）
sequence = torch.tensor([[0.1, 0.2, 0.3], [0.2, 0.3, 0.4], [0.3, 0.4, 0.5]]).unsqueeze(0).float()  # 添加batch维度

# 进行推理
with torch.no_grad():
    output = model(sequence)

# 打印推理结果
print("预测结果:", output)

#基本参量在头文件中声明

string_h = ''
string_h += f"extern int input_size;\n"
string_h += f"extern int hidden_size;\n"
string_h += f"extern int num_layers;\n"
string_h += f"extern int seq_len;\n"

seq_len = 3
string_h += f"extern double input_matrix[{seq_len}][{input_size}];\n"

size1 = hidden_size*(input_size+hidden_size)
string_h += f"extern double Wf0[{size1}];\n"
string_h += f"extern double Wi0[{size1}];\n"
string_h += f"extern double Wc0[{size1}];\n"
string_h += f"extern double Wo0[{size1}];\n"

size2 = (num_layers-1)*((hidden_size)*(2*hidden_size))
string_h += f"extern double Wf[{size2}];\n"
string_h += f"extern double Wi[{size2}];\n"
string_h += f"extern double Wc[{size2}];\n"
string_h += f"extern double Wo[{size2}];\n"

string_h += f"extern double bf[{num_layers}][{hidden_size}];\n"
string_h += f"extern double bi[{num_layers}][{hidden_size}];\n"
string_h += f"extern double bc[{num_layers}][{hidden_size}];\n"
string_h += f"extern double bo[{num_layers}][{hidden_size}];\n"


with open(path_h, 'w') as file:
    print("#ifndef INIT\n#define INIT", file=file)
    print(string_h, file=file)
    print("#endif", file=file)
    print("Successfully printed into the header file!")


#头文件写好了，接下来写initialization.c文件
string_init = ''

#基本参量的初始化
string_init += '#include "initialization.h"\n'
string_init += f"int input_size = {input_size};\n"
string_init += f"int hidden_size = {hidden_size};\n"
string_init += f"int num_layers = {num_layers};\n"
string_init += f"int seq_len = {sequence.size(1)};\n"

# 获取 sequence 张量的形状
batch_size, seq_len, input_size = sequence.size()
string_init += f"double input_matrix[{seq_len}][{input_size}] = {{\n"
# 使用嵌套循环遍历每个元素,从而定义了input_matrix
for i in range(batch_size):
    for j in range(seq_len):
        string_init += "{"
        for k in range(input_size):
            string_init += f"{sequence[i,j,k]},"
        string_init += "},\n"
string_init += "};\n"

with open(path_c, 'w') as file:
    print(string_init, file=file)
print("Basic variables initialized!")


# size = hidden_size*(input_size+hidden_size)
# string_init += f"extern double Wf0[{size1}];\n"
# string_init += f"double Wi0[{size1}];\n"
# string_init += f"double Wc0[{size1}];\n"
# string_init += f"double Wo0[{size1}];\n"
#
# size2 = (num_layers-1)*((hidden_size)*(2*hidden_size))
# string_init += f"double Wf[{size2}];\n"
# string_init += f"double Wi[{size2}];\n"
# string_init += f"double Wc[{size2}];\n"
# string_init += f"double Wo[{size2}];\n"
#
# string_init += f"double bf[{num_layers}][{hidden_size}];\n"
# string_init += f"double bi[{num_layers}][{hidden_size}];\n"
# string_init += f"double bc[{num_layers}][{hidden_size}];\n"
# string_init += f"double bo[{num_layers}][{hidden_size}];\n"

# with open(path_h, 'w') as file:
#     print("#ifndef INIT\n#define INIT", file=file)
#     print(string_init, file=file)
#     print("#endif", file=file)

# # 获取 sequence 张量的形状
# batch_size, seq_len, input_size = sequence.size()
#
# with open(path_c,"w") as file:
#     print("\n",file=file)
#
# # 使用嵌套循环遍历每个元素
# for i in range(batch_size):
#     for j in range(seq_len):
#         for k in range(input_size):
#             with open(path_c,"a") as file:
#                 value = sequence[i, j, k]
#                 print(f"input_matrix[{j}][{k}] = {value};\n",file = file)

# 获取所有参数
params = list(model.named_parameters())

wf_str = f"double Wf[{size2}] = {{"
wi_str = f"double Wi[{size2}] = {{"
wc_str = f"double Wc[{size2}] = {{"
wo_str = f"double Wo[{size2}] = {{"

bf_str = f"double bf[{num_layers}][{hidden_size}] = {{\n"
bi_str = f"double bi[{num_layers}][{hidden_size}] = {{\n"
bc_str = f"double bc[{num_layers}][{hidden_size}] = {{\n"
bo_str = f"double bo[{num_layers}][{hidden_size}] = {{\n"

w_i_1, w_f_1, w_g_1, w_o_1 = None, None, None, None
w_i_2, w_f_2, w_g_2, w_o_2 = None, None, None, None
w_i, w_f, w_g, w_o = None, None, None, None
b_i_1, b_f_1, b_g_1, b_o_1 = None, None, None, None
b_i_2, b_f_2, b_g_2, b_o_2 = None, None, None, None
b_i, b_f, b_g, b_o = None, None, None, None

# 遍历参数并打印它们的形状
for i, (name, param) in enumerate(params):
    if 'weight' in name:
        print(f"begin:权重矩阵 {i + 1} ({name}) 的形状: {param.shape}")
       # print(param)
        if i % 2 == 0:
            w_i_1 = param[:hidden_size, :]
            # print("w_i_1:",w_i_1)
            w_f_1 = param[hidden_size:2*hidden_size, :]
            # print("w_if_1:", w_if_1)
            w_g_1 = param[2*hidden_size:3*hidden_size, :]
            # print("w_ig_1:", w_ig_1)
            w_o_1 = param[3*hidden_size:4*hidden_size, :]
            # print("w_io_1:", w_io_1)
        elif i % 2 == 1:
            w_i_2 = param[:hidden_size, :]
            w_f_2 = param[hidden_size:2*hidden_size, :]
            w_g_2 = param[2*hidden_size:3*hidden_size, :]
            w_o_2 = param[3*hidden_size:4*hidden_size, :]
            # print("w_i_1:",w_i_1)
            # print("w_i_2:", w_i_2)
            wi = torch.cat((w_i_1, w_i_2), dim=1)
            # print("after_cat:",wi)
            wf = torch.cat((w_f_1, w_f_2), dim=1)
            wg = torch.cat((w_g_1, w_g_2), dim=1)
            wo = torch.cat((w_o_1, w_o_2), dim=1)
       # print(f"权重矩阵 {i + 1} ({name}) 的形状: {param.shape}")

    elif 'bias' in name:
        print(f"begin:偏置矩阵 {i + 1} ({name}) 的形状: {param.shape}")
        if i % 2 == 0:
            b_i_1 = param[:hidden_size]
            # print("w_ii_1:",w_ii_1)
            b_f_1 = param[hidden_size:2*hidden_size]
            # print("w_if_1:", w_if_1)
            b_g_1 = param[2*hidden_size:3*hidden_size]
            # print("w_ig_1:", w_ig_1)
            b_o_1 = param[3*hidden_size:4*hidden_size]
            # print("w_io_1:", w_io_1)
        elif i % 2 == 1:
            b_i_2 = param[:hidden_size]
            b_f_2 = param[hidden_size:2*hidden_size]
            b_g_2 = param[2*hidden_size:3*hidden_size]
            b_o_2 = param[3*hidden_size:4*hidden_size]
            # 使用 torch.add 逐个元素相加
            bi = torch.add(b_i_1, b_i_2)
            bf = torch.add(b_f_1, b_f_2)
            bg = torch.add(b_g_1, b_g_2)
            bo = torch.add(b_o_1, b_o_2)

            if i == 3:
                bf_tmp, bi_tmp, bc_tmp, bo_tmp = print_first_layer(input_size, hidden_size, wf, wi, wg, wo, bi, bf, bg, bo)
                bf_str += bf_tmp
                bi_str += bi_tmp
                bc_str += bc_tmp
                bo_str += bo_tmp

            elif i > 3:
                wf_tmp,wi_tmp,wc_tmp,wo_tmp,bf_tmp,bi_tmp,bc_tmp,bo_tmp = print_other_layers(math.floor(i//4),input_size, hidden_size, wf, wi, wg, wo, bi, bf, bg, bo)

                wf_str += wf_tmp
                wi_str += wi_tmp
                wc_str += wc_tmp
                wo_str += wo_tmp

                bf_str += bf_tmp
                bi_str += bi_tmp
                bc_str += bc_tmp
                bo_str += bo_tmp


wf_str += "};\n"
wi_str += "};\n"
wc_str += "};\n"
wo_str += "};\n"

bf_str += "};\n"
bi_str += "};\n"
bc_str += "};\n"
bo_str += "};\n"

with open(path_c,'a') as file:
    print(wf_str, file=file)
    print(wi_str, file=file)
    print(wc_str, file=file)
    print(wo_str, file=file)
    print(bf_str, file=file)
    print(bi_str, file=file)
    print(bc_str, file=file)
    print(bo_str, file=file)



        # print(f"偏置矩阵 {i + 1} ({name}) 的形状: {param.shape}")

print("wi.shape",wi.shape)