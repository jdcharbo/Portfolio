#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

int Generator2(int p)
	{
		if(p==1||p==2)
			return p;
		int cover[2][p];
		cover[0][0] = 1;
		int e = (int) round(sqrt(p)/3);
		for(int i=1; i<e; i++)
		{
			cover[0][i] = 1;
			cover[0][p-i] = 1;
			cover[1][i] = 1;
			cover[1][p-i] = 1;
		}
		for(int i=e; i<p-(e-1); i++)
		{
			cover[0][i] = 0;
			cover[1][i] = 0;
		}
		for(int i=0; i<p-1; i++)
			for(int j=i+1; j<p; j++)
			{
				if(cover[0][i]==1 && cover[0][j]==1)
				{
					cover[1][(j-i+p)%p] == 1;
					cover[1][(i-j+p)%p] == 1;
				}
			}
		int sum=0;
		int sum2 = 3;
		int best[2];
		best[0] = best[1] = 0;
		int diff = 0;
		int i = e;
		bool found = false;
		int d=0;
		while(sum2<p)
		{
			if(found)
			{
				cover[0][best[0]] = 1;
				for(int j=0; j<p; j++)
				{
					if(cover[0][j]==1)
					{
						cover[1][(j-best[0]+p)%p]=1;
						cover[1][(best[0]-j+p)%p]=1;
					}
				}
				found = false;
				best[0] = 0;
				best[1] = 0;
				i = e;
			}
			else if(i>=p)
			{
				found = true;
			}
			else
			{
				diff=0;
				sum = 0;
				if(cover[0][i]==0)
				{
					
					for(int j=0; j<p; j++)
						sum = sum+cover[0][j];
					for(int j=0; j<p; j++)
					{
						if(cover[0][j]==1)
						{
							if(cover[1][(j-i+p)%p]==0)
							{
								diff++;
							}
							if(cover[1][(i-j+p)%p]==0)
							{
								diff++;
							}
						}
					}
					if(diff==2*sum)
					{
						best[0] = i;
						found = true;
					}
					else if(diff>best[1])
					{
						best[0] = i;
						best[1] = diff;
					}
					
				}
				i++;
			}
			sum2 = 0;
			for(int j=0; j<p; j++)
				sum2 = sum2+cover[1][j];
			
		}
		for(int j=0; j<p; j++)
			if(cover[0][j]==1)
				d++;
		return d;
	}
//int argc, char *argv[] in main to get inputs. Inputs stored as *argv[].

int main()
{
	//cout << "Hi" << endl;
	//int p = atoi(argv[1]);
//	cout << "Hi" << endl;
	for(int p = 1; p<=123; p++)
	{
	int d = Generator2(p);
	//cout << "Hi" << endl;
	ofstream solutions;
	solutions.open("SolutionsB2.txt", ios::out | ios::app);
	solutions << p << " " << d << "\n";
	solutions.close();
	cout << "Solutions for size " << p << " added to SolutionsB2." << endl;
	}

}

