#!/bin/bash

# Step 1: Run "main.py" in the folder "lstm_pytorch_test"
cd lstm_pytorch_test
python main.py

# You can customize parameters here, e.g., input_size, hidden_size, num_layers
# python main.py --input_size 64 --hidden_size 128 --num_layers 2

# Step 2: Run the following commands in the terminal
cd ..
rm -rf build1
cmake -B build1
cd build1
cmake --build .
./LSTM_inf_in_C

#Then comes the reusults!