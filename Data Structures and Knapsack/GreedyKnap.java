import java.io.*;
import java.util.*;
import java.lang.Math;

class GreedyKnap
{
	public static void main(String [] args){
		item [] list = new item[4];
		list[0] = new item(1, 2, 40); list[1] = new item(2, 5, 30); list[2] = new item(3, 10, 50); list[3] = new item(4, 5, 10);
		item [] knapsack = new item[4];
		int W = 16;
		for(int i=0; i<4; i++)
			knapsack[i] = null;
		knapsack = greedio(knapsack, list, W);
		int Value = 0;
		for(int i=0; i<4; i++)
		{
			if(knapsack[i]!=null)
			{
				Value+=knapsack[i].getValue();
				knapsack[i] = null;
			}
		}
		System.out.println("Total value from greedy io = "+Value);
		System.out.println("Total value from Dynamic Program IO = "+DPIO(list, W));
		knapsack = greedfrac(knapsack, list, W);
		Value = 0;
		for(int i=0; i<4; i++)
		{
			if(knapsack[i]!=null)
			{
				Value+=knapsack[i].getValue();
				knapsack[i] = null;
			}
		}
		System.out.println("Total value from greedy frac = "+Value);
		
	}
	
	public static item [] greedio(item [] knap, item [] list, int W)
	{
		Sorts.merge(list);
		int w = 0;
		int i=knap.length-1;
		int j = 0;
		while(w<W)
		{
			knap[j]=list[i];
			w+=list[i].getWeight();
			if(w>W)
			{
				w+=-list[i].getWeight();
				knap[j]=null;
			}
			j++;
			i--;
			if(i<0 || j>knap.length)
				break;
		}
		return knap;
		
	}
	public static item [] greedfrac(item [] knap, item [] list, int W)
	{
		Sorts.merge(list);
		int w = 0;
		int i=knap.length-1;
		int j = 0;
		while(w<W)
		{
			knap[j]=list[i];
			w+=list[i].getWeight();
			if(w>W)
			{
				w+=-list[i].getWeight();
				knap[j]=null;
				list[i].frac((W-w)/list[i].getWeight());
				w+=list[i].getWeight();
				knap[j]=list[i];
				break;
			}
			j++;
			i--;
			if(i<0 || j>knap.length)
				break;
		}
		return knap;
		
	}
	
	public static int DPIO(item [] list, int W)
	{
		int [][] P = new int[list.length+1][W+1];
		for(int i=0; i<list.length+1; i++)
			P[i][0]=0;
		for(int i=0; i<W+1; i++)
			P[0][i]=0;
		for(int i=1; i<list.length+1; i++)
			for(int j=1; j<W+1; j++)
			{
				if(j>=list[i-1].getWeight())
				{
					if(list[i-1].getValue()+P[i-1][(int)(j-list[i-1].getWeight())]>P[i-1][j])
						P[i][j] = (int)(list[i-1].getValue())+P[i-1][(int)(j-list[i-1].getWeight())];
					else
						P[i][j] = P[i-1][j];
				}
				else
					P[i][j] = P[i-1][j];
			}
		return P[list.length][W];
	}


}