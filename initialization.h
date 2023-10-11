#ifndef INIT
#define INIT
int input_size = 3;
int hidden_size = 64;
int num_layers = 3;
int seq_len = 3;
double input_matrix[3][3] ;double Wf0[4288];
double Wi0[4288];
double Wc0[4288];
double Wo0[4288];
double Wf[16384];
double Wi[16384];
double Wc[16384];
double Wo[16384];
double bf[3][64];
double bi[3][64];
double bc[3][64];
double bo[3][64];

#endif
