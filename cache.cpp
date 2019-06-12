#include<iostream>
#include<fstream>
#include"cstdio"
using namespace std;

int main()
{
    int cache, block, asso, policy;
    string address;
    ifstream infile("trace1.txt", ios::in); //file open
    if(!infile)
    {
	cerr<<"Fail opening"<<endl;
	exit(1);
    }
    ofstream outfile("trace1.out", ios::out);

    //get trace1.txt 4 line data
    infile>>cache;
    infile>>block;
    infile>>asso;
    infile>>policy;
    //calculate
    printf("%d %d %d %d", cache, block, asso, policy);

    infile.close();
    outfile.close();
    return 0;
}
