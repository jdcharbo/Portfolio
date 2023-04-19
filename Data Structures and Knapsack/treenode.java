public class treenode
	{
		public double profit;
		public double bound;
		public boolean [] set;
		public int level;
		public double weight;
		public treenode(int n)
		{
			bound = 0;
			profit = 0;
			set = new boolean[n];
			for(int i=0; i<n; i++)
			set[i]=false;
			level = 0;
			weight = 0;
		}
	}