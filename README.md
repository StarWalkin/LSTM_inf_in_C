# LSTM_inf_in_C
LSTM in C without using dynamic array！

## Quick Start
open terminal at the project directory
### Step1: Add permission for shell script
```
chmod +x run_test.sh
```
### Step2: Run the shell script
```
./run_test.sh
```


## Customize your inference procedure
### Step1: Run "main.py" in the folder "lstm_pytorch_test"
This can randomly craeate a dataset and print it to the c_project.
You can customize some of the parameters, currently including input_size, hidden_size and num_layers 


### Step2: Run following commands in the terminal:
(You are expected to firstly cd to the project directory)
```
cmake -B build1
cd build1
cmake --build .
./LSTM_inf_in_C
```
        
Then the prediction result will be on the console!

You can compare it with the pytorch output from main.py.They will be exactly the same(So far I haven't encountered any discrepancies）.
