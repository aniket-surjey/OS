
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
#include<iostream>
 
using namespace std;
 
int main()
{
	int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j;
 
	for(i = 0; i < 10; i++)
	{
		flags[i] = 0;
		allocation[i] = -1;
	}
	
	cout<<"Enter no. of blocks: ";
	cin>>bno;
	
	cout<<"\nEnter size of each block: ";
	for(i = 0; i < bno; i++)
		cin>>bsize[i];
 
	cout<<"\nEnter no. of processes: ";
	cin>>pno;
	
	cout<<"\nEnter size of each process: ";
	for(i = 0; i < pno; i++)
		cin>>psize[i];
	for(i = 0; i < pno; i++)         //allocation as per first fit
		for(j = 0; j < bno; j++)
			if(flags[j] == 0 && bsize[j] >= psize[i])
			{
				allocation[j] = i;
				flags[j] = 1;
				break;
			}
	
	//display allocation details
	cout<<"\nBlock no.\tsize\t\tprocess no.\t\tsize";
	for(i = 0; i < bno; i++)
	{
		cout<<"\n"<< i+1<<"\t\t"<<bsize[i]<<"\t\t";
		if(flags[i] == 1)
			cout<<allocation[i]+1<<"\t\t\t"<<psize[allocation[i]];
		else
			cout<<"Not allocated";
	}
	
	return 0;
}
