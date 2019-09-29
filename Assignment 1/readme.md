# Assignment 1
### Implementing 'Apriori' algorithm to find K-frequent sets

The algorithm is implemented in C++


### Running the code

To compile the code, run the make
`/usr/bin/qmake -o Makefile ../freqItemSets/freqItemSets.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug`

To run the executable, you could run the already compiled executable file located in [Github link](https://github.com/severus-tux/dmml-assignments/blob/master/Assignment%201/src/build-freqItemSets-Desktop-Debug/freqItemSets)

#### Example :
`./freqItemSets 4 1000 enron`

`./freqItemSets <k> <f> <dataset name>` 

### Output
Some sample output for various values of k,f and datasets are available at : [github link](https://github.com/severus-tux/dmml-assignments/tree/master/Assignment%201/output)
