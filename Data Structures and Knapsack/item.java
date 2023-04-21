public class item implements Comparable{
	int index;
	double weight;
	double value;
	public item(int i, int w, int v){
		index = i;
		weight = w;
		value = v;
	}
	public String toString(){
		return "item "+index;
	}
	public int getIndex()
	{
		return index;
	}
	public double getWeight()
	{
		return weight;
	}
	public double getValue(){
		return value;
	}
	public void frac(double r)
	{
		weight*= r;
		value*=r;
	}
	public int compareTo(Object x)
	{
		if(x instanceof item)
		{
			item y=(item)x;
			double ratio = value/weight;
			double r2 = y.getValue()/y.getWeight();
			if(ratio>r2)
				return 1;
			else if (ratio==r2)
				return 0;
			else
				return -1;
		}
		else
			return 0;
	}
	
}