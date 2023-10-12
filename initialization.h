#ifndef INIT
#define INIT
extern int input_size;
extern int hidden_size;
extern int num_layers;
extern int seq_len;
extern double input_matrix[3][3];
extern double Wf0[4288];
extern double Wi0[4288];
extern double Wc0[4288];
extern double Wo0[4288];
extern double Wf[0];
extern double Wi[0];
extern double Wc[0];
extern double Wo[0];
extern double bf[1][64];
extern double bi[1][64];
extern double bc[1][64];
extern double bo[1][64];

#endif
