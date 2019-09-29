#include "dataset.h"

dataSet::dataSet(string Docword, string Vocab)
{
    long docID, wordID, wordCount;

    this->Docword = Docword;
    this->Vocab = Vocab;
    ifstream infile;
    infile.open(Docword, ios::in);

    infile >> numberOfDocs;
    infile >> numberOfWords;
    infile >> rowCount;
    set <long> emptyset;

    //initilizing empty sets for all words
    docWordVector.push_back(emptyset); // 0 -> {}
    for (long i = 1; i<=numberOfWords;i++)
            docWordVector.push_back(emptyset); // wordID -> {}

    for(long i=0;i < rowCount; i++)
    {
        infile >> docID >> wordID >> wordCount;
        docWordVector[wordID].insert(docID); // for each wordID, update its set;

    }
    initlizeVocabector();
    infile.close();
}

void dataSet::initlizeVocabector()
{
    string word;
    ifstream ifile;
    ifile.open(Vocab, ios::in);

    vocabVector.push_back("");
    while(ifile >> word)
        vocabVector.push_back(word);
    ifile.close();
}

vector< vector<long>> dataSet::apriori(long k, long f)
{
    vector <vector< vector<long>>> F(k+1); // create a vector of size k. each element of this vector is a list of list. i.e, F1, F2, ... Fk
    vector <vector< vector<long>>> C(k+1); // similar
    long r = 0;
    for(long i=1;i<=numberOfWords;i++)
    {
        if(docWordVector[i].size() >= f)
        {
            F[1].resize(1+F[1].size());
            F[1][r].push_back(i);
            r++;
        }
    }

    for (long i=2;i<=k;i++)
    {
        candidateGenerate(C[i],F[i-1], i-1);
        //computing F[i] from C[i]

        for(long q=0; q<C[i].size();q++)
        {
            //now creating a vector of sets (of docs) curresponding to each word in C[i][q]
            vector <set<long>> x;
            for(long t=0;t<i;t++)
                x.push_back(docWordVector[C[i][q][t]]);

            if(setIntersect(x).size() >= f) // the intersected set is of cardinality >= f , so include it in F
                F[i].push_back(C[i][q]);
        }
        C[i].clear();
        F[i-1].clear(); // memory cleaning
    }

    displayFk(F[k],k);
    return F[k];
}


void dataSet::candidateGenerate(vector< vector <long>> &C_k_plus_1, vector< vector <long>> &F_k, long k)
{
    long length = F_k.size();

    if(length <=1) // C_k_plus_1 will be empty , leave it be.
    {
        return;
    }

    long idx = 0;
    for(long i=0;i<length;i++)
        for(long j=i+1;j<length;j++)
        {
            if (!(equal( F_k[i].begin(),F_k[i].end()-1,F_k[j].begin() )))
            {
                break;
            }

            vector<long> temp(k+1);
            temp = F_k[i];
            temp.push_back(F_k[j][k-1]);

            C_k_plus_1.resize( 1 + C_k_plus_1.size() );
            C_k_plus_1[idx] = temp;
            idx++;
        }
}

set<long> dataSet::setIntersect (vector<set<long>> x) // takes a vector of
{
    set<long> is = x[0];
    set<long> is_j;     //maintaining two temporary sets to loop through the vecter , intersecting each

    for(long i=0;i<x.size();i++)
    {
        set<long> intersect;
        set_intersection(x[i].begin(),x[i].end(),is.begin(),is.end(),inserter(is_j,is_j.begin()) );
        is.clear();
        is=is_j;
        is_j.clear();
    }

    return is;
}

void dataSet::displayFk(vector<vector<long>> Fk, long k)
{
    long len = Fk.size();
    for(long i=0;i<len;i++)
    {
        cout<<"\n";
        cout << "{ ";
        for(long j=0;j<Fk[i].size();j++)
            cout << vocabVector[Fk[i][j]] << ", ";
        cout<<"\b\b }";
    }
    cout<<endl;
    cout << "Size of F"<<k << "  : "  << len << endl;
}
