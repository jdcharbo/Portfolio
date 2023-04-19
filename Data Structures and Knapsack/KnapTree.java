public class KnapTree
{
	
	treenode root;
	int count;
	int levels;
	int index;
	int Weight;
	public KnapTree(item [] n, int W)
	{
		root.data=new item(0, 0, 0); root.left=root.right=root.parent=null; count=1; root.bound=0; 
		for(int i=0; i<n.length; i++)
		{root.set[i]=false;}
		levels = n.length+1; index = 2; Weight = W;
		insert(n);
		Boundfill(root, 0, n);
	}
	
	public treenode bfs()
	{
		treenode v = root;
		treenode u;
		double best = v.bound;
		Q = new QueueLL();
		Q.enqueue(v);
		while(!Q.isEmpty())
		{
			v = Q.dequeue();
			if(v.bound > best)
			{
				for(int i=0; i<2; i++)
				{
					if(i==0)
						u=v.left;
					else
						u=v.right;
					if(u.data.getValue()>best)
						best = u.data.getValue();
					if(u.bound>best)
						Q.enqueue(u);
				}
			}
		}
		return v;
	}
	
	
	public void insert(item [] n)
	{
		root.left=inserthelp(root, n, null, 0, 0);
		root.right=inserthelp(root, n, null, 0, 1);
	}
	private treenode inserthelp(treenode r, item [] n, treenode parent, int level, int child)
		// returns the new root of the subtree we insert into
	{
		
		if(level > levels)
			return null;
		treenode newnode=new treenode();
		if(r==null) // empty subtree
		{
			if(child==0)
			{
				newnode.data = new item(index, (int)(parent.data.getWeight()+n[level-1].getWeight()), (int)(parent.data.getValue()+n[level-1].getValue()));
				for(int i=0; i<parent.set.length; i++)
				{
					if(i==level-1)
						r.set[i]=true;
					else
						r.set[i]=parent.set[i];
				}
			}
			else
			{
				newnode.data = new item(index, (int)(parent.data.getWeight()), (int)(parent.data.getValue()));
				for(int i=0; i<parent.set.length; i++)
				{
					r.set[i]=parent.set[i];
				}
			}
			index++;
			newnode.left=newnode.right=null; newnode.parent=parent;
			count++;
			newnode.bound=0;
		}
		if(r.left==null) // x is smaller
		{
			r.left=inserthelp(r.left,n,r,level+1,0);
		}
		if(r.right==null)
		{
			r.right=inserthelp(r.right,n,r,level+1,1);
		}
		return newnode;
	}
	
	public void Boundfill(treenode r, int level, item [] n)
	{
		if(r.left==null)
		{
			r.bound = r.data.getValue();
			return;
		}
		if(r.data.getWeight()>Weight)
		{
			return;
		}
		Boundfill(r.left, level+1, n); Boundfill(r.right, level+1, n);
		int sum = 0;
		int w = 0;
		treenode s = r;
		int lt = level;
		while(lt<=levels&&w<Weight)
		{
			if(w+s.data.getWeight()>Weight)
			{
				item j = new item(index+1, (int)(s.data.getWeight()), (int)(s.data.getValue()));
				j.frac((w+s.data.getWeight()+Weight)/(s.data.getWeight()));
				sum+=j.getValue();
				w+=j.getWeight();
			}
			else
			{
				sum+=s.data.getValue();
				w+=s.data.getWeight();
			}
			s=s.left;
			lt++;
		}
		r.bound = sum;
	}
	
	
	QueueLL Q;
	
	
}