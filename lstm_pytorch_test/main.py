import torch
import torch.nn as nn
from print_into_c import *
import math

# 创建一个简单的LSTM模型
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
num_layers = 3  # LSTM层数

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

# 获取所有参数
params = list(model.named_parameters())

# 遍历参数并打印它们的形状
for i, (name, param) in enumerate(params):
    if 'weight' in name:
       print(f"begin:权重矩阵 {i + 1} ({name}) 的形状: {param.shape}")
       if i%2 == 0:
            w_i_1 = param[:hidden_size, :]
            # print("w_ii_1:",w_ii_1)
            w_f_1 = param[hidden_size:2*hidden_size, :]
            # print("w_if_1:", w_if_1)
            w_g_1 = param[2*hidden_size:3*hidden_size, :]
            # print("w_ig_1:", w_ig_1)
            w_o_1 = param[3*hidden_size:4*hidden_size, :]
            # print("w_io_1:", w_io_1)
       elif i%2 == 1:
           w_i_2 = param[:hidden_size, :]
           w_f_2 = param[hidden_size:2*hidden_size, :]
           w_g_2 = param[2*hidden_size:3*hidden_size, :]
           w_o_2 = param[3*hidden_size:4*hidden_size, :]
           wi = torch.cat((w_i_1, w_i_2), dim=1)
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
                print_first_layer(input_size, hidden_size, wf, wi, wg, wo, bi, bf, bg, bo)
            elif i > 3:
                print_other_layers(math.floor(i//2),input_size, hidden_size, wf, wi, wg, wo, bi, bf, bg, bo)


        # print(f"偏置矩阵 {i + 1} ({name}) 的形状: {param.shape}")

print("wi.shape",wi.shape)