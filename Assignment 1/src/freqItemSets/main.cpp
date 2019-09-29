#include <iostream>
#include <fstream>
#include <vector>
#include <dataset.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cout << "Input error\n";
        return 1;
    }
    long k,f;
    k = stoi(argv[1]);
    f = stoi(argv[2]);
    string datasetName = argv[3];

    if (!(datasetName == "enron" || datasetName == "kos" || datasetName == "nips"))
    {
        cout << "no such dataset exist!\n";
        return 1;
    }

    string datasetDocword = "../../data/docword."  + datasetName + ".txt" ;
    string datasetVocab = "../../data/vocab."  + datasetName + ".txt" ;

    dataSet ds(datasetDocword,datasetVocab);
    cout << "The sets are : \n";
    auto start = high_resolution_clock::now(); // starting timer
    ds.apriori(k,f);
    auto stop = high_resolution_clock::now();  // stoping timer
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "time taken  : "<< duration.count() / 1000000.0<< "seconds "<< endl;
 }
