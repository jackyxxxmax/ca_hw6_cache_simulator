#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;

int main(int argc, char*argv[])
{
    int cache_size, block_size, asso_type, policy_type;
    int tag_width, index_width, offset_width;
    //test
    //ifstream infile("trace2.txt", ios::in); //file open
    //ofstream outfile("trace2.out", ios::out);
    //test
    ifstream infile(argv[1], ios::in); //file open
    if(!infile)
    {
        cerr<<"Fail opening"<<endl;
        exit(1);
    }
    ofstream outfile(argv[2], ios::out);

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
    //printf("%d %d %d %d\n", cache_size, block_size, asso_type, policy_type);
    //printf("%d %d %d\n", tag_width, index_width, offset_width);

    //maybe use vector
    //because trace2.txt will lost front bit
    //and trace3.txt will core dumped
    
    //create cache using 2D-array
	int start_index = 0;
	int time_order = 0; //the time read in
	int block_num = (cache_size*1024)/block_size;
    unsigned int cache[block_num][2];
    //initialize
    for(int i=0; i<block_num; i++)
	{
    	cache[i][0] = 0; //address
    	cache[i][1] = 0; //time_order
	}

    //get trace1.txt address data
    unsigned int temp = 0;
	unsigned int temp1 = 0, temp2 = 0; //for target
	unsigned int temp3 = 0; //for match data
    unsigned int victag = 0;
    unsigned int target = 0;
    
	if(policy_type == 0) //FIFO
	{
		while(infile>>std::hex>>target)
    	{
    		temp = target / (int)pow(2, offset_width); //discard offset bits
    		temp1 = temp % (int)pow(2, index_width); //get index bits
    		temp2 = temp / (int)pow(2, index_width); //get tag bits
    		temp = cache[temp1][0] / (int)pow(2, offset_width); //discard offset bits
    		temp3 = temp / (int)pow(2, index_width); //get tag bits
    		if(asso_type == 0) //direct-mapped
			{
				if(cache[temp1][0] != target) //different address data
				{
					if(temp2 == temp3) //same index and same tag, Hit
					{
						outfile << "-1" << endl;
						cache[temp1][0] = target; //update address data
						time_order = time_order + 1;
						cache[temp1][1] = time_order; //update time_order
						continue;
					}
					else //same index and different tag, Miss, select victim
					{
						if(temp3 == 0)
						{
							outfile << "-1" << endl;
						}
						else
						{
							outfile << temp3 << endl;
						}
						cache[temp1][0] = target; //update address data
						time_order = time_order + 1;
						cache[temp1][1] = time_order; //update time_order
						continue;
					}
				}
				else //same address data, Hit
				{
					outfile << "-1" << endl;
					time_order = time_order + 1;
					cache[temp1][1] = time_order; //update time_order
					continue;
				}
			}
			else if(asso_type == 1) //4-way
			{
			}
			else if(asso_type == 2) //fully
			{
			}
    	}
	}
	else if(policy_type == 1) //LRU
	{
		while(infile>>std::hex>>target)
    	{
    		temp = target / (int)pow(2, offset_width); //discard offset bits
    		temp1 = temp % (int)pow(2, index_width); //get index bits
    		temp2 = temp / (int)pow(2, index_width); //get tag bits
    		temp = cache[temp1][0] / (int)pow(2, offset_width); //discard offset bits
    		temp3 = temp / (int)pow(2, index_width); //get tag bits
    		if(asso_type == 0) //direct-mapped
			{
				if(cache[temp1][0] != target) //different address data
				{
					if(temp2 == temp3) //same index and same tag, Hit
					{
						outfile << "-1" << endl;
						cache[temp1][0] = target; //update address data
						time_order = time_order + 1;
						cache[temp1][1] = time_order; //update time_order
						continue;
					}
					else //same index and different tag, Miss, select victim
					{
						if(temp3 == 0)
						{
							outfile << "-1" << endl;
						}
						else
						{
							outfile << temp3 << endl;
						}
						cache[temp1][0] = target; //update address data
						time_order = time_order + 1;
						cache[temp1][1] = time_order; //update time_order
						continue;
					}
				}
				else //same address data, Hit
				{
					outfile << "-1" << endl;
					time_order = time_order + 1;
					cache[temp1][1] = time_order; //update time_order
					continue;
				}
			}
			else if(asso_type == 1) //4-way
			{
			}
			else if(asso_type == 2) //fully
			{
			}
    	}
	}
	else if(policy_type == 2) //my policy RANDOM
	{
		while(infile>>std::hex>>target)
    	{
    		temp = target / (int)pow(2, offset_width); //discard offset bits
    		temp1 = temp % (int)pow(2, index_width); //get index bits
    		temp2 = temp / (int)pow(2, index_width); //get tag bits
    		temp = cache[temp1][0] / (int)pow(2, offset_width); //discard offset bits
    		temp3 = temp / (int)pow(2, index_width); //get tag bits
    		if(asso_type == 0) //direct-mapped
			{
				if(cache[temp1][0] != target) //different address data
				{
					if(temp2 == temp3) //same index and same tag, Hit
					{
						outfile << "-1" << endl;
						cache[temp1][0] = target; //update address data
						time_order = time_order + 1;
						cache[temp1][1] = time_order; //update time_order
						continue;
					}
					else //same index and different tag, Miss, select victim
					{
						if(temp3 == 0)
						{
							outfile << "-1" << endl;
						}
						else
						{
							outfile << temp3 << endl;
						}
						cache[temp1][0] = target; //update address data
						time_order = time_order + 1;
						cache[temp1][1] = time_order; //update time_order
						continue;
					}
				}
				else //same address data, Hit
				{
					outfile << "-1" << endl;
					time_order = time_order + 1;
					cache[temp1][1] = time_order; //update time_order
					continue;
				}
			}
			else if(asso_type == 1) //4-way
			{
			}
			else if(asso_type == 2) //fully
			{
			}
    	}
	}

    infile.close();
    outfile.close();
    return 0;
}
