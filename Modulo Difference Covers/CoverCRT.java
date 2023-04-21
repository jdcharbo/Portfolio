import java.io.*;
import java.util.*;
import java.lang.Math;
class CoverCRT
{
	static boolean Checker(int [] cover, int p, int size)//function to check whether a set is a modulo difference cover of Z_p.
	{
		boolean t = true;
		if(size==p-1 || size==p)
		{
			//System.out.println("This set p is guaranteed to be a cover.");
			return true;
		}
		if((size)*(size-1)+1<p || size>p)
		{
			//System.out.println("This set p is guaranteed to not be a cover.");
			return false;
		}
		boolean [] check = new boolean[p];
		for(int i=0; i<p; i++)
		{
			check[i]=false;
		}
		check[0]=true;
		for(int i=0; i<size-1; i++)
			for(int j=i+1; j<size; j++)
			{
				check[(cover[i]-cover[j]+p)%p]=true;
				check[(cover[j]-cover[i]+p)%p]=true;
			}
		for(int i=0; i<p; i++)
			if(!check[i])
			{
				t = false;
				break;
			}
		return t;
	}
	
	static int [][] factors(int p) //A function that generates a modified sieve of Eratosthenes, with sieve[x][0] being the part that is the sieve of Erastosthenes, and for a particular m, sieve[m][n] (n>0) gives a prime power factor of m, such that sieve[m] contains all of its prime powers.
	{
		int [][] sieve = new int[p+1][(int)(Math.round(Math.sqrt(p)))];
		int j = 0;
		int k = 1;
		for(int i=0; i<=p; i++)
		{
			sieve[i][0] = 1;
			for(int l=1; l<Math.round(Math.sqrt(p)); l++)
				sieve[i][l]=0;
		}
		for(int i=2; i<=p; i++)
			if(sieve[i][0]==1) // if i is prime
			{
				j = i*i;
				for(int l=i+1; l<=p; l++)
				{
					if(l%i==0) // l is not prime
					{
						sieve[l][0]=0;
						while(sieve[l][k]!=0) // looking for the first 'unnocupied' cell to put this factor in
							k++;
						sieve[l][k] = i;
						while(l%j==0) // looking for the highest prime power that divides l.
						{
							sieve[l][k]=j;
							j*=i;
						}
						j = i*i;
						k = 1;
					}
				}
			}
		return sieve;
	}
	//int argc, char *argv[] in main to get inputs. Inputs stored as *argv[].
	
	static int inver(int x, int y) // function that looks for the multiplicative inverse to x mod y. returns the inverse if it exists, otherwise returns 0.
	{
		boolean found = false;
		int k = 1;
		while(!found)
		{
			//cout << "looking for an inverse to " << x << " mod "<< y << endl;
			if((k*x)%y==1)
				return k;
			k++;
		}
		return 0;
	}

	static int CRT(int [][] y, int bigmod, int size) // the size of y is y[size][2]. 
	{
		int x = size;
		int [] l = new int[x];
		int [] k = new int[x];
		int z = 0;
		for(int i=0; i<x; i++)
		{
			l[i] = (bigmod/y[i][1]);
			k[i]=(y[i][0]*inver(l[i], y[i][1]))%y[i][1];
			z+=k[i]*l[i];
		}
		z = z%bigmod;
		return z;
	}
	
	static int [] coverC(int p, int [][] sieve) throws IOException
	{
		int [] size = csize(p, sieve);
		int [] t = new int[1];
		t[0]=0;
		if(size.length==1)
			return t;
		int [] cover = new int[size[0]];
		int [] f1 = pull(size[1]);
		int [] f2 = pull(size[2]);
		int [][] y = new int[2][2];
		y[0][1] = size[1]; y[1][1] = size[2];
		int k=0;
		for(int i=0; i<f1.length; i++)
			for(int j=0; j<f2.length;j++)
			{
				y[0][0] = f1[i]; y[1][0] = f2[j];
				cover[k] = CRT(y, size[1]*size[2], 2);
				k++;
			}
		return cover;
	}
	
	static int [] pull(int p) throws IOException
	{
		if(p>88)
			return null;
		Scanner file = new Scanner(new FileReader("masterListOfCovers.txt"));
		String it;
		int scan;
		for(int i=0; i<p; i++)
			it = file.nextLine();
		scan = file.nextInt();
		scan = file.nextInt();
		int [] cover = new int[scan];
		int n = scan;
		for(int i=0; i<n; i++)
		{
			scan = file.nextInt();
			cover[i]=scan;
		}
		file.close();
		return cover;
	}
	
	static int [] csize(int p, int [][] sieve) throws IOException// returns the minimum size of the CRT cover and the factors for it.
	{
		int [] t = new int[1];
		t[0]=0;
		if(sieve[p][2]==0)
		{
			System.out.println(p+" is a prime power, so its cover cannot be computed with this method.");
			return t;
		}
		int primes = 0;
		int f1=1;
		int f2=1;
		int k=1;
		int flip;
		int [] best = new int[3];
		for(int i=1; i<sieve[p].length; i++)
			if(sieve[p][i]==0)
				break;
			else
				primes++;
		f1 = sieve[p][1];
		int isolate = primes;
		for(int i=2; i<primes+1; i++)
		{
			f2*=sieve[p][i];
		}
		best[1]=f1; best[2]=f2; best[0] = ScanSize(f1)*ScanSize(f2);
		while(k<Math.pow(2, primes-1)-1)
		{
			for(int i=1; i<=primes; i++)
				if(i!=isolate&&f2%sieve[p][i]==0)
				{
					f1*=sieve[p][i]; f2/=sieve[p][i]; k++;
					if(ScanSize(f1)*ScanSize(f2)<best[0])
					{
						best[0] = ScanSize(f1)*ScanSize(f2); best[1] = f1; best[2]=f2;
					}
				}
			flip = f1;
			f1 = f2;
			f2 = flip;
			isolate--;
		}
		return best;
	}
	
	// static boolean min(
	
	static int ScanSize(int p) throws IOException
	{
		if(p>88)
			return p;
		Scanner file = new Scanner(new FileReader("masterListOfCovers.txt"));
		String it;
		int scan;
		for(int i=0; i<p; i++)
			it = file.nextLine();
		scan = file.nextInt();
		scan = file.nextInt();
		file.close();
		return scan;
	}
	
	public static void printc(int size, int p, int [][] sieve) throws IOException
	{
		int [] cover = coverC(p, sieve);
		// int prin = 0;
		// int [] ncover;
		// int [] removed = {0};
		// if(cover.length!=1)
		// {
			// ncover = min(cover, p, removed);
			// if(ncover!=cover)
			// {
				// System.out.println("The CRT cover is not minimal. "+removed[0]+" elements have been removed. This is for size "+p);
			// }
			// else
				// System.out.println("The CRT cover is minimal. This is for size "+p);
			
			for(int i=0; i<cover.length-1; i++)
				System.out.print(cover[i]+" ");
			System.out.println(cover[cover.length-1]);
		//}
	}
	
	public static int [] min(int [] cover, int p, int [] removed)
	{
		int [] holder = new int[2];
		int [] ncover = new int[cover.length-1];
		boolean m = false;
		for(int i = 0; i<cover.length-1; i++)
			ncover[i] = cover[i];
		holder[0]=cover[cover.length-1];
		holder[1]=cover.length-2;
		while(holder[1]>=0)
		{
			m=Checker(ncover, p, ncover.length);
			if(m)
			{
				System.out.println("The element "+holder[0]+" can be removed from this cover.");
				removed[0]++;
				return min(ncover, p, removed);
			}
			ncover[holder[1]]=holder[0];
			holder[0]=cover[1+holder[1]--];
		}
		return cover;
	}
	
	public static void main(String [] args) throws IOException
	{
		int [][] sieve = factors(100);
		int [] dummy = csize(100, sieve);
		for(int j=99; j>=5; j--)
		{
			printc(dummy[0], j+1, sieve);
			if(j==5)
				break;
			dummy = csize(j, sieve);
		}
		
	}
}