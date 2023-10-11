import torch

path = '/Users/yuan/Desktop/cprint_test2.c'

def print_first_layer(input_size, hidden_size, wf, wi, wg, wo, bi, bf, bg, bo):
    strings = []
    wf = wf.flatten().tolist()
    wi = wi.flatten().tolist()
    wg = wg.flatten().tolist()
    wo = wo.flatten().tolist()
    # 使用字符串格式化来替换参数的值
    for i in range(0, hidden_size * (input_size + hidden_size)):
        strings.append("Wf0[{}] = {};".format(i,wf[i]))
        strings.append("Wi0[{}] = {};".format(i,wi[i]))
        strings.append("Wc0[{}] = {};".format(i,wg[i]))
        strings.append("Wo0[{}] = {};".format(i,wo[i]))


    for i in range(0,hidden_size):
        strings.append("bf[0][{}] = {};".format(i,bf[i]))
        strings.append("bi[0][{}] = {};".format(i, bi[i]))
        strings.append("bc[0][{}] = {};".format(i, bg[i]))
        strings.append("bo[0][{}] = {};".format(i, bo[i]))


    with open(path, 'w') as file:
        for i in range(0, len(strings)):
            print(strings[i], file=file)
    print("Successfully printed the first layer!")
    return



def print_other_layers(layer_idx,input_size,hidden_size,wi,wf,wg,wo,bi,bf,bg,bo):
    strings = []
    wf = wf.flatten().tolist()
    wi = wi.flatten().tolist()
    wg = wg.flatten().tolist()
    wo = wo.flatten().tolist()
    with open(path,"a") as file:
        for i in range ((hidden_size) * (2 * hidden_size)):
            strings.append("Wf[{}] = {};".format((layer_idx-1)*((hidden_size)*(2*hidden_size))+i,wf[i]))
            strings.append("Wi[{}] = {};".format((layer_idx-1) * ((hidden_size) * (2 * hidden_size)) + i, wi[i]))
            strings.append("Wc[{}] = {};".format((layer_idx-1) * ((hidden_size) * (2 * hidden_size)) + i, wg[i]))
            strings.append("Wo[{}] = {};".format((layer_idx-1) * ((hidden_size) * (2 * hidden_size)) + i, wo[i]))

        for i in range(hidden_size):
            strings.append("bf[{}][{}] = {};".format(layer_idx, i, bf[i]))
            strings.append("bi[{}][{}] = {};".format(layer_idx, i, bi[i]))
            strings.append("bc[{}][{}] = {};".format(layer_idx, i, bg[i]))
            strings.append("bo[{}][{}] = {};".format(layer_idx, i, bo[i]))

        for i in range(0, len(strings)):
            print(strings[i], file=file)

    print("Successfully printed all the other layers!!")
    return



# print_parameters(3,2,3)

# input_size = 1
# hidden_size = 2
# print_first_layer(1,2,[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,1],[2,2],[3,3],[4,4])






