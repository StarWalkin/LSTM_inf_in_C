import torch

path_h = '/Users/yuan/Desktop/科研竞赛/ANL-瑞萨项目/LSTM_inf_in_C/initialization.h'
path_c = '/Users/yuan/Desktop/科研竞赛/ANL-瑞萨项目/LSTM_inf_in_C/initialization.c'


def print_first_layer(input_size, hidden_size, wf, wi, wg, wo, bi, bf, bg, bo):
    str = ""
    wf = wf.flatten().tolist()
    wi = wi.flatten().tolist()
    wg = wg.flatten().tolist()
    wo = wo.flatten().tolist()

    str_bf, str_bi, str_bg, str_bo = '{', '{', '{', '{'

    size1 = hidden_size * (input_size + hidden_size)
    str += f"double Wf0[{size1}] = {{"
    for i in range(size1):
        str += f"{wf[i]},"
    str += "};\n"

    str += f"double Wi0[{size1}] = {{"
    for i in range(size1):
        str += f"{wi[i]},"
    str += "};\n"

    str += f"double Wc0[{size1}] = {{"
    for i in range(size1):
        str += f"{wg[i]},"
    str += "};\n"

    str += f"double Wo0[{size1}] = {{"
    for i in range(size1):
        str += f"{wo[i]},"
    str += "};\n"

    # str += f"double bf[0] = {{"

    for idx in range(hidden_size):
        str_bf += f"{bf[idx]},"
        str_bi += f"{bi[idx]},"
        str_bg += f"{bg[idx]},"
        str_bo += f"{bo[idx]},"

    str_bf += '},\n'
    str_bi += '},\n'
    str_bg += '},\n'
    str_bo += '},\n'


    with open(path_c,"a") as file:
        print(str,file = file)

    print("Successfully printed the first layer!")

    return str_bf,str_bi,str_bg,str_bo


def print_other_layers(layer_idx,input_size,hidden_size,wi,wf,wg,wo,bi,bf,bg,bo):

    wf = wf.flatten().tolist()
    # print("len",len(wf))
    wi = wi.flatten().tolist()
    wg = wg.flatten().tolist()
    wo = wo.flatten().tolist()

    # str_b = ""
    str_wf, str_wi, str_wg, str_wo = '', '', '', ''
    single_layer_size = (hidden_size) * (2 * hidden_size)
    # print( single_layer_size)
    # str += f"double Wf[{size2}] = {{"
    for i in range(single_layer_size):
        # print("wf,",i,wf[i])
        str_wf += f"{wf[i]},"
        # print("str_wf_after_add",str_wf)
        str_wi += f"{wi[i]},"
        str_wg += f"{wg[i]},"
        str_wo += f"{wo[i]},"

        str_bf, str_bi, str_bg, str_bo = '{', '{', '{', '{'

    for idx in range(hidden_size):
        str_bf += f"{bf[idx]},"
        str_bi += f"{bi[idx]},"
        str_bg += f"{bg[idx]},"
        str_bo += f"{bo[idx]},"

    str_bf += '},\n'
    str_bi += '},\n'
    str_bg += '},\n'
    str_bo += '},\n'


        # str_b += f"double bf[{layer_idx-1}] = {{"
        # for i in range(hidden_size):
        #     str_b += f"{bf[i]},"
        # str_b += "};\n"
        #
        # str_b += f"double bi[{layer_idx-1}] = {{"
        # for i in range(hidden_size):
        #     str_b += f"{bi[i]},"
        # str_b += "};\n"
        #
        # str_b += f"double bc[{layer_idx-1}] = {{"
        # for i in range(hidden_size):
        #     str_b += f"{bg[i]},"
        # str_b += "};\n"
        #
        # str_b += f"double bo[{layer_idx}] = {{"
        # for i in range(hidden_size):
        #     str_b += f"{bo[i]},"
        # str_b += "};\n"
        #
        # with open(path_c,'a') as file:
        #     print(str_b,file=file)
    #
    # print("str_wf:",str_wf)
    return str_wf,str_wi,str_wg,str_wo,str_bf,str_bi,str_bg,str_bo

    # str += "};\n"

    # str += f"double Wi[{size2}] = {{"
    # for i in range(size2):
    #     str += f"{wi[i]},"
    # str += "};\n"
    #
    # str += f"double Wc[{size2}] = {{"
    # for i in range(size2):
    #     str += f"{wg[i]},"
    # str += "};\n"
    #
    # str += f"double Wo[{size2}] = {{"
    # for i in range(size2):
    #     str += f"{wo[i]},"
    # str += "};\n"
    #
    # for layer_idx in range(1,num_layers):
    #     str += f"double bf[0] = {{"
    #     for i in range(hidden_size):
    #         str += f"{bf[i]},"
    #     str += "};\n"
# print_parameters(3,2,3)

# input_size = 1
# hidden_size = 2
# print_first_layer(1,2,[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,2,3,4,5,6],[1,1],[2,2],[3,3],[4,4])






