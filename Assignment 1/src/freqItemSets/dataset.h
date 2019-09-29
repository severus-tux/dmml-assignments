#ifndef DATASET_H
#define DATASET_H

#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace  std;

class dataSet
{
public:
    long numberOfDocs, numberOfWords, rowCount;
    vector <set<long>> docWordVector;
    vector <string> vocabVector;
    string Docword,Vocab;

    dataSet(string Docword, string Vocab); // initialize vocabVec with the data from vocab file;
    void initlizeVocabector();
    vector< vector <long>> apriori(long k, long f);
    void candidateGenerate(vector< vector <long>> &C_k_plus_1, vector< vector <long>> &F_k, long k);
    set<long> setIntersect(vector<set<long>> x);
    void displayFk(vector<vector<long>> Fk,long k);

};

#endif // DATASET_H
