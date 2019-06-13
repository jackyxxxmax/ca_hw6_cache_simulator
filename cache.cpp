#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;

int main()
{
    int cache_size, block_size, asso_type, policy_type;
    int tag_width, index_width, offset_width;
    int i=0;
    //maybe use vector
    //because trace2.txt will lost front bit
    //and trace3.txt will core dumped
    unsigned int address[1000000];
    ifstream infile("trace1.txt", ios::in); //file open
    if(!infile)
    {
        cerr<<"Fail opening"<<endl;
        exit(1);
    }
    ofstream outfile("trace1.out", ios::out);

    //get trace1.txt 4 line data
    infile>>cache_size;
    infile>>block_size;
    infile>>asso_type;
    infile>>policy_type;
    //scanf("%d", &cache_size);
    //scanf("%d", &block_size);
    //scanf("%d", &asso_type);
    //scanf("%d", &policy_type);

    //calculate width
    offset_width = log2(block_size);
    if(asso_type == 0) //direct-mapped
    {
        index_width = log2(cache_size*1024/block_size);
        tag_width = 32-index_width-offset_width;
    }
    else if(asso_type == 1) //4-way
    {
        index_width = log2(cache_size*1024/block_size)-2;
        tag_width = 32-index_width-offset_width;
    }
    else if(asso_type == 2) //fully
    {
        index_width = 0;
        tag_width = 32-index_width-offset_width;
    }
    //debug
    printf("%d %d %d %d\n", cache_size, block_size, asso_type, policy_type);
    printf("%d %d %d\n", tag_width, index_width, offset_width);

    //get trace1.txt address data
    while(infile>>std::hex>>address[i])
    {
        i++;
    }
    //debug
    for(int j=0; j<i; j++)
    {
        printf("%x\n",address[j]);
    }

    //

    infile.close();
    outfile.close();
    return 0;
}
