#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

ifstream bruh;

class Node
{
	Node * parent;
	Node * Child[3];
	int val[6];
	
	Node(Node * par)
	{
		parent = par;
		int valcount = 0;
		int childcount = 0;
		char input;
		int hold = 0;
		while(bruh.good())
		{
			input = bruh.get();
			hold = 0;
			if(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9')
			{
				while(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9')
				{
					hold = hold*10+(int)(input)-48;
					input = bruh.get();
				}
				if(valcount==0)
				{
					val[valcount++]=hold;
					val[1]=1;
				}
				else if(valcount==1)
				{
					val[4]=hold;
					val[5]=1;
					valcount++;
				}
				else if(valcount==2)
				{
					val[2]=val[4];
					val[4]=hold;
					val[3]=1;
					valcount++;
				}
			}
			if(input=='/')
			{
				input=bruh.get();
				if(input!='/')
				{
					if(childcount==0)
						Child[0]=new Node(this);
					else if(childcount==1)
						Child[2]=new Node(this);
					else
					{
						Child[1]=Child[2];
						Child[2]=new Node(this);
					}
					childcount++;
				}
				else
				{
					input=bruh.get();
					if(childcount==0)
					{Child[0]=NULL;Child[1]=NULL;Child[2]==NULL;}
					else if(childcount==1)
					{Child[1]==NULL;Child[2]=NULL;}
					else if(childcount==2)
						Child[1]=NULL;
					if(valcount==1)
					{
						val[3]=0;
						val[5]=0;
					}
					else if(valcount==2)
						val[3]=0;
					break;
				}
			}
		}
		
		
	}
	public: Node()
	{
		parent = NULL;
		int valcount = 0;
		int childcount = 0;
		char input;
		int hold = 0;
		while(bruh.good())
		{
			input = bruh.get();
			hold = 0;
			if(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9')
			{
				while(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9')
				{
					hold = hold*10+(int)(input)-48;
					input = bruh.get();
				}
				if(valcount==0)
				{
					val[valcount++]=hold;
					val[1]=1;
				}
				else if(valcount==1)
				{
					val[4]=hold;
					val[5]=1;
					valcount++;
				}
				else if(valcount==2)
				{
					val[2]=val[4];
					val[4]=hold;
					val[3]=1;
					valcount++;
				}
			}
			if(input=='/')
			{
				input=bruh.get();
				if(input!='/')
				{
					if(childcount==0)
					{
						Child[0]=new Node(this);
					}
					else if(childcount==1)
					{
						Child[2]=new Node(this);
					}
					else
					{
						Child[1]=Child[2];
						Child[2]=new Node(this);
					}
					childcount++;
				}
				else
				{
					input=bruh.get();
					if(childcount==0)
					{Child[0]=NULL;Child[1]=NULL;Child[2]==NULL;}
					else if(childcount==1)
					{Child[1]==NULL;Child[2]=NULL;}
					else if(childcount==2)
						Child[1]=NULL;
					if(valcount==1)
					{
						val[3]=0;
						val[5]=0;
					}
					else if(valcount==2)
						val[3]=0;
					break;
				}
				
			}
		}
		
		
	}
	public: int getVal(int i)
	{
		if(i>=6)
		{
			cout << "invalid input" << endl;
			return 2020;
		}
		else
			return val[i];
	}
	public: Node * getChild(int i)
	{
		if(i>=3)
		{
			cout << "invalid input" << endl;
			return NULL;
		}
		else
			return Child[i];
	}
	public: Node * getParent()
	{
		return parent;
	}
	
	void setParent(Node * par)
	{
		parent = par;
	}
	public: Node(int value[6])
	{
		parent = NULL;
		for(int i=0; i<6; i++)
		{
			if(i<3)
				Child[i]=NULL;
			val[i]=value[i];
		}
	}
	public: int numChildren()
	{
		int count = 0;
		for(int i=0; i<3; i++)
		{
			if(Child[i]!=NULL)
				count++;
		}
		return count;
	}
	
	public: void printNode()
	{
		cout << "( " << val[0] << " ";
		if(val[3]==1)
			cout << val[2] << " ";
		if(val[5]==1)
			cout << val[4] << " ";
		if(Child[0]!=NULL)
			Child[0]->printNode();
		if(Child[1]!=NULL)
			Child[1]->printNode();
		if(Child[2]!=NULL)
			Child[2]->printNode();
		cout << ") ";
	}
	public: int find(int valToFind)
	{
		if(Child[0]==NULL)
			return val[0];
		else if(val[0]>=valToFind)
			return Child[0]->find(valToFind);
		else if(Child[1]!=NULL)
			if(val[2]>=valToFind)
				return Child[1]->find(valToFind);
		if(val[4]>=valToFind)
			return Child[2]->find(valToFind);
		else
			return 2000;
	}
	public: Node * find1(int valToFind)
	{
		if(Child[0]==NULL)
			return this;
		else if(val[0]>=valToFind)
			return Child[0]->find1(valToFind);
		else if(Child[1]!=NULL)
			if(val[2]>=valToFind)
				return Child[1]->find1(valToFind);
		return Child[2]->find1(valToFind);
	}
	public: void setVal(int i, int j)
	{
		if(i>5)
		{cout << "invalid argument in setVal." << endl;return;}
		val[i]=j;
	}
	public: void setChild(int i, Node * j)
	{
		if(i>2)
		{cout << "invalid argument in setChild" << endl; return;}
		Child[i]=j;
	}
	public: void update(int i)//i refers to the child number
	{
		int cn=0;
		if(parent!=NULL)
		{
			if(parent->getVal(3)==1)
			{
				if(this==parent->getChild(1))
				{
					cn=1;
				}
			}
			if(this==parent->getChild(2))
				cn=2;
		}
		val[2*i]=Child[i]->getVal(4);
		if(i==2&&parent!=NULL)
		{
			parent->update(cn);
		}
	}
	public: void absorbhelp1(Node * a)
	{
		if(a->getVal(5)==1)
		{
			if(a->getVal(4)<val[0])
			{
				val[2]=val[0];
				val[0]=a->getVal(4);
				val[3]=1;
				Child[1]=Child[0];
				Child[0]=a;
				a->setParent(this);
			}
			else if(a->getVal(4)<val[4])
			{
				val[2]=a->getVal(4);
				val[3]=1;
				Child[1]=a;
				a->setParent(this);
			}
			else
			{
				val[2]=val[4];
				val[4]=a->getVal(4);
				val[3]=1;
				Child[1]=Child[2];
				Child[2]=a;
				a->setParent(this);
				parent -> update(2);
			}
		}
		else
		{
			if(a->getVal(0)<val[0])
			{
				val[2]=val[0];
				val[0]=a->getVal(0);
				val[3]=1;
				Child[1]=Child[0];
				Child[0]=a;
				a->setParent(this);
			}
			else if(a->getVal(0)<val[4])
			{
				val[2]=a->getVal(0);
				val[3]=1;
				Child[1]=a;
				a->setParent(this);
			}
			else
			{
				val[2]=val[4];
				val[4]=a->getVal(0);
				val[3]=1;
				Child[1]=Child[2];
				Child[2]=a;
				a->setParent(this);
				parent -> update(2);
			}
		}
	}
	public: void setNode(Node * a)
	{
		parent = a->getParent();
		for(int i=0; i<6; i++)
			val[i]=a->getVal(i);
		for(int i=0; i<3; i++)
			Child[i]=a->getChild(i);
	}
	public: void discard()
	{
		if(parent->getParent()==NULL&&parent->numChildren()==2)
		{
			int sibi=0;
			for(int i=0; i<3; i++)
				if(parent->getChild(i)!=NULL&&parent->getChild(i)!=this)
					sibi=i;
			parent->getChild(sibi)->setParent(NULL);
			parent->setNode(parent->getChild(sibi));
			if(parent->getVal(1)==1)
				parent->getChild(0)->setParent(parent);
			if(parent->getVal(3)==1)
				parent->getChild(1)->setParent(parent);
			if(parent->getVal(5)==1)
				parent->getChild(2)->setParent(parent);
			return;
			
		}
		Node * par = parent;
		int i=0;
		if(par->getChild(1)==this)
			i=1;
		else if(par->getChild(2)==this)
			i=2;
		par->setChild(i, NULL);
		par->setVal(2*i,0);
		par->setVal(2*i+1,0);
		parent=NULL;
		int parcount = par->numChildren();
		if(parcount==2)
		{
			if(i==2)
			{
				par->setChild(2, par->getChild(1));
				par->setChild(1, NULL);
				par->setVal(4, par->getVal(2));
				par->setVal(2, 0);
				par->setVal(5, 1);
				par->setVal(3, 0);
				int parpar = 0;
				if(par->getParent()->getChild(1)==par)
					parpar=1;
				else if(par->getParent()->getChild(2)==par)
					parpar=2;
				par->getParent()->update(parpar);
			}
			if(i==0)
			{
				par->setChild(0, par->getChild(1));
				par->setChild(1, NULL);
				par->setVal(0, par->getVal(2));
				par->setVal(2, 0);
				par->setVal(3, 0);
				par->setVal(1, 1);
			}
		}
		else
		{
			int k=0;
			for(int j=0; j<6; j++)
			{
				if(par->getVal(j)!=0)
				{
					k=j;
					break;
				}
			}
			if(k!=0)
			{
				par->setChild(0, par->getChild(k/2));
				par->setChild(k/2, NULL);
				par->setVal(0, par->getVal(k));
				par->setVal(1, 1);
				par->setVal(k, 0);
				par->setVal(k+1, 0);
			}
			int sibcount = 0;
			Node * parpar = par->getParent();
			for(int j=0; j<3; j++)
				if(parpar->getChild(j)!=NULL)
					sibcount+=parpar->getChild(j)->numChildren();
			if(sibcount==3||sibcount==5)
			{
				Node * sibling;
				int sibi, mei;
				for(int j=0; j<3; j++)
				{
					if(parpar->getChild(j)!=NULL&&parpar->getChild(j)!=par)
					{
						sibling=parpar->getChild(j);
						sibi=j;
					}
					if(parpar->getChild(j)==par)
						mei=j;
				}
				if(sibcount==5&&mei==0)
				{sibi=1;sibling=parpar->getChild(1);}
				if(mei<sibi)
				{
					sibling->setChild(1, sibling->getChild(0));
					sibling->setChild(0, par->getChild(0));
					par->getChild(0)->setParent(sibling);
					sibling->setVal(2, sibling->getVal(0));
					sibling->setVal(0, par->getVal(0));
					sibling->setVal(3, 1);
					parpar->update(sibi);
					parpar->update(2);
					par->discard();
				}
				else
				{
					sibling->setChild(1, sibling->getChild(2));
					sibling->setChild(2, par->getChild(0));
					par->getChild(0)->setParent(sibling);
					sibling->setVal(2, sibling->getVal(4));
					sibling->setVal(4, par->getVal(0));
					sibling->setVal(3, 1);
					parpar->update(sibi);
					parpar->update(2);
					par->discard();
				}
			}
			if(sibcount==4)
			{
				Node * sibling;
				int sibi, mei;
				for(int j=0; j<3; j++)
				{
					if(parpar->getChild(j)!=NULL&&parpar->getChild(j)!=par)
					{
						sibling=parpar->getChild(j);
						sibi=j;
					}
					if(parpar->getChild(j)==par)
						mei=j;
				}
				if(mei<sibi)
				{
					par->setChild(2, sibling->getChild(0));
					sibling->getChild(0)->setParent(par);
					sibling->setChild(0, sibling->getChild(1));
					sibling->setChild(1, NULL);
					par->setVal(4, sibling->getVal(0));
					par->setVal(5, 1);
					sibling->setVal(0, sibling->getVal(2));
					sibling->setVal(2, 0);
					sibling->setVal(3, 0);
					parpar->update(0);
					parpar->update(2);
				}
				else
				{
					par->setChild(2, par->getChild(0));
					par->setChild(0, sibling->getChild(2));
					sibling->getChild(2)->setParent(par);
					sibling->setChild(2, sibling->getChild(1));
					sibling->setChild(1, NULL);
					par->setVal(4, par->getVal(0));
					par->setVal(0, sibling->getVal(4));
					par->setVal(5, 1);
					sibling->setVal(4, sibling->getVal(2));
					sibling->setVal(2, 0);
					sibling->setVal(3, 0);
					parpar->update(0);
					parpar->update(2);
				}
			}
			else if(sibcount==6||sibcount==7)
			{
				Node * sibling;
				int sibi, mei;
				for(int j=0; j<3; j++)
				{
					if(parpar->getChild(j)->numChildren()==3)
					{
						sibling=parpar->getChild(j);
						sibi=j;
					}
					if(parpar->getChild(j)==par)
						mei=j;
				}
				if(sibcount==7)
				{
					if(mei==0||mei==2)
					{
						sibling=parpar->getChild(1);
						sibi=1;
					}
				}
				if(sibcount==6&&((mei==0&&sibi==2)||(mei==2&&sibi==0)))
				{
					Node * sibm = par->getParent()->getChild(1);
					if(mei==0)
					{
						par->setChild(2, sibm->getChild(0));
						par->setVal(4, sibm->getVal(0));
						par->setVal(5, 1);
						sibm->getChild(0)->setParent(par);
						sibm->setChild(0, sibm->getChild(2));
						sibm->setVal(0, sibm->getVal(4));
						sibm->setChild(2, sibling->getChild(0));
						sibm->setVal(4, sibling->getVal(0));
						sibling->getChild(0)->setParent(sibm);
						sibling->setChild(0, sibling->getChild(1));
						sibling->setVal(0, sibling->getVal(2));
						sibling->setChild(1, NULL);
						sibling->setVal(2, 0);
						sibling->setVal(3, 0);
						parpar->update(0);
						parpar->update(1);
						parpar->update(2);
						return;
						
					}
					else
					{
						par->setChild(2, par->getChild(0));
						par->setVal(4, par->getVal(0));
						par->setVal(5, 1);
						par->setChild(0, sibm->getChild(2));
						par->setVal(0, sibm->getVal(4));
						sibm->getChild(2)->setParent(par);
						sibm->setChild(2, sibm->getChild(0));
						sibm->setVal(4, sibm->getVal(0));
						sibm->setChild(0, sibling->getChild(2));
						sibm->setVal(0, sibling->getVal(4));
						sibling->getChild(2)->setParent(sibm);
						sibling->setChild(2, sibling->getChild(1));
						sibling->setVal(4, sibling->getVal(2));
						sibling-> setChild(1, NULL);
						sibling->setVal(2, 0);
						sibling->setVal(3, 0);
						parpar->update(0);
						parpar->update(1);
						parpar->update(2);
						return;
					}
				}
				if(mei<sibi)
				{
					par->setChild(2, sibling->getChild(0));
					sibling->getChild(0)->setParent(par);
					sibling->setChild(0, sibling->getChild(1));
					sibling->setChild(1, NULL);
					par->setVal(4, sibling->getVal(0));
					par->setVal(5, 1);
					sibling->setVal(0, sibling->getVal(2));
					sibling->setVal(2, 0);
					sibling->setVal(3, 0);
					parpar->update(mei);
					parpar->update(2);
				}
				else
				{
					par->setChild(2, par->getChild(0));
					par->setChild(0, sibling->getChild(2));
					sibling->getChild(2)->setParent(par);
					sibling->setChild(2, sibling->getChild(1));
					sibling->setChild(1, NULL);
					par->setVal(4, par->getVal(0));
					par->setVal(0, sibling->getVal(4));
					par->setVal(5, 1);
					sibling->setVal(4, sibling->getVal(2));
					sibling->setVal(2, 0);
					sibling->setVal(3, 0);
					parpar->update(sibi);
					parpar->update(2);
				}
			}
		}
		
	}
	
};

class Tree
{
	Node * root;
	
	public: Tree()
	{
		root = new Node();
	}
	public: void printTree()
	{
		root->printNode();
		cout << endl;
	}
	public: int search(int valToFind)
	{
		return root->find(valToFind);
	}
	public: void insert(int val)//returns true if element was insterted, returns false if it already existed.
	{
		int value[6] = {val, 1, 0, 0, 0, 0};
		Node * newNode = new Node(value);
		Node * b  = root->find1(newNode->getVal(0));
		if(b->getVal(0)==newNode->getVal(0))
		{
			cout << "insert failed, node already exists in tree." << endl;
			return;
		}
		this->absorb(b, newNode);
	}
	public: void absorb(Node * b, Node * a)
	{
		if(b==root)
		{
			int value[6];
			if(a->getVal(5)==1)
				value[0]=a->getVal(4);
			else
				value[0]=a->getVal(0);
			value[1]=1;value[2]=0;value[3]=0;
			if(b->getVal(5)==1)
				value[4]=b->getVal(4);
			else
				value[4]=b->getVal(0);
			value[5]=1;
			Node * MR = new Node(value);
			a->setParent(MR);
			b->setParent(MR);
			MR->setChild(0, a);
			MR->setChild(2, b);
			root = MR;
		}
		else if(b->getParent()->getChild(1)==NULL)
		{
			b->getParent()->absorbhelp1(a);
		}
		else
		{
			Node * left;
			int leftset[6];
			Node * bpar = b->getParent();
			if(a->getVal(5)==1)
			{
				if(a->getVal(4)<bpar->getVal(0))
				{
					leftset[0]=a->getVal(4);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=bpar->getVal(0);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, bpar->getVal(2));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, a);
					left->setChild(2, bpar->getChild(0));
					a->setParent(left);
					bpar->getChild(0)->setParent(left);
					bpar->setChild(0, bpar->getChild(1));
					bpar->setChild(1, NULL);
					
				}
				else if(a->getVal(4)<bpar->getVal(2))
				{
					leftset[0]=bpar->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=a->getVal(4);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, bpar->getVal(2));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, bpar->getChild(0));
					left->setChild(2, a);
					a->setParent(left);
					bpar->getChild(0)->setParent(left);
					bpar->setChild(0, bpar->getChild(1));
					bpar->setChild(1, NULL);
				}
				else if(a->getVal(4)<bpar->getVal(4))
				{
					leftset[0]=bpar->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=bpar->getVal(2);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, a->getVal(4));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, bpar->getChild(0));
					left->setChild(2, bpar->getChild(1));
					bpar->getChild(1)->setParent(left);
					bpar->getChild(0)->setParent(left);
					a->setParent(bpar);
					bpar->setChild(0, a);
					bpar->setChild(1, NULL);
					
				}
				else
				{
					leftset[0]=bpar->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=bpar->getVal(2);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, bpar->getVal(4));
					bpar->setVal(4, a->getVal(4));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, bpar->getChild(0));
					left->setChild(2, bpar->getChild(1));
					bpar->getChild(1)->setParent(left);
					bpar->getChild(0)->setParent(left);
					a->setParent(bpar);
					bpar->setChild(0, bpar->getChild(2));
					bpar->setChild(2, a);
					bpar->setChild(1, NULL);
					if(bpar->getParent()!=NULL)
						bpar->getParent()->update(2);
				}
			}
			else
			{
				if(a->getVal(0)<bpar->getVal(0))
				{
					leftset[0]=a->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=bpar->getVal(0);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, bpar->getVal(2));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, a);
					left->setChild(2, bpar->getChild(0));
					a->setParent(left);
					bpar->getChild(0)->setParent(left);
					bpar->setChild(0, bpar->getChild(1));
					bpar->setChild(1, NULL);
				}
				else if(a->getVal(0)<bpar->getVal(2))
				{
					leftset[0]=bpar->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=a->getVal(0);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, bpar->getVal(2));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, bpar->getChild(0));
					left->setChild(2, a);
					a->setParent(left);
					bpar->getChild(0)->setParent(left);
					bpar->setChild(0, bpar->getChild(1));
					bpar->setChild(1, NULL);
				}
				else if(a->getVal(0)<bpar->getVal(4))
				{
					leftset[0]=bpar->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=bpar->getVal(2);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, a->getVal(0));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, bpar->getChild(0));
					left->setChild(2, bpar->getChild(1));
					bpar->getChild(1)->setParent(left);
					bpar->getChild(0)->setParent(left);
					a->setParent(bpar);
					bpar->setChild(0, a);
					bpar->setChild(1, NULL);
				}
				else
				{
					leftset[0]=bpar->getVal(0);leftset[1]=1;leftset[2]=0;leftset[3]=0;leftset[4]=bpar->getVal(2);leftset[5]=1;
					left = new Node(leftset);
					bpar->setVal(0, bpar->getVal(4));
					bpar->setVal(4, a->getVal(0));
					bpar->setVal(2, 0);
					bpar->setVal(3, 0);
					left->setChild(0, bpar->getChild(0));
					left->setChild(2, bpar->getChild(1));
					bpar->getChild(1)->setParent(left);
					bpar->getChild(0)->setParent(left);
					a->setParent(bpar);
					bpar->setChild(0, bpar->getChild(2));
					bpar->setChild(2, a);
					bpar->setChild(1, NULL);
					if(bpar->getParent()!=NULL)
						bpar->getParent()->update(2);
				}
			} 
			this->absorb(bpar, left);
		}
	}
	public: void remove(int a)
	{
		int b = root->find(a);
		if(root->getVal(5)==0)
		{
			root=NULL;
			return;
		}
		if(b==a)
		{
			Node * c = root->find1(a);
			c->discard();
		}
		else
			cout << "could not remove, node does not exist." << endl;
	}
};

int main()
{
	bruh.open("23treeandme.txt", ios::in);
	cout << "This is what the mcguffin tree looks like." << endl;
	Tree * mcguffin = new Tree();
	mcguffin->printTree();
	cout << "testing all cases for search." << endl;
	cout << endl;
	cout << "the successor to 21 in mcguffin is " << mcguffin->search(21) << endl;
	cout << "the successor to 22 in mcguffin is " << mcguffin->search(22) << endl;
	cout << "the successor to 40 in mcguffin is " << mcguffin->search(40) << endl;
	cout << endl;
	cout << "Testing all easy insertion and deletion cases." << endl;
	cout << endl;
	mcguffin -> insert(34);
	cout << "mcguffin after inserting 34." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(34);
	cout << "mcguffin after removing 34." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(37);
	cout << "mcguffin after inserting 37." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(37);
	cout << "mcguffin after removing 37." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(40);
	cout << "mcguffin after inserting 40." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(40);
	cout << "mcguffin after removing 40." << endl;
	mcguffin->printTree();
	cout << endl;
	cout << "testing inserting duplicates and removing what is not there." << endl;
	cout << endl;
	mcguffin -> remove(40);
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(39);
	mcguffin->printTree();
	cout << endl;
	cout << "testing reccurence of insert and remove. Handles the megaroot case and root death, as well as the bbba case of reccurence insertion and the sibcount=3 right and sibcount = 5 right cases." << endl;
	cout << endl;
	mcguffin -> insert(40);
	cout << "mcguffin after inserting 40." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(41);
	cout << "mcguffin after inserting 41." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(42);
	cout << "mcguffin after inserting 42." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(43);
	cout << "mcguffin after inserting 43." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(43);
	cout << "mcguffin after removing 43." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(42);
	cout << "mcguffin after removing 42." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(41);
	cout << "mcguffin after removing 41." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(40);
	cout << "mcguffin after removing 40." << endl;
	mcguffin->printTree();
	cout << endl;
	cout << "testing remaining reccurence insert cases (abbb, babb, bbab) as well as sibcount=3 left deletion case." << endl;
	cout << endl;
	mcguffin -> insert(10);
	cout << "mcguffin after inserting 10." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(10);
	cout << "mcguffin after removing 10." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(12);
	cout << "mcguffin after inserting 12." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(12);
	cout << "mcguffin after removing 12." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(15);
	cout << "mcguffin after inserting 15." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(15);
	cout << "mcguffin after removing 15." << endl;
	mcguffin->printTree();
	cout << endl;
	cout << "testing deletion for sibcount = 4" << endl;
	cout << endl;
	mcguffin -> insert(32);
	cout << "mcguffin after inserting 32." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(36);
	cout << "mcguffin after removing 36." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(36);
	cout << "mcguffin after inserting 36." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(32);
	cout << "mcguffin after removing 32." << endl;
	mcguffin->printTree();
	cout << endl;
	cout << "testing deletion cases for sibcount = 5" << endl;
	cout << endl;
	mcguffin -> remove(14);
	cout << "mcguffin after removing 14." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(3);
	cout << "mcguffin after removing 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(3);
	cout << "mcguffin after inserting 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(5);
	cout << "mcguffin after removing 5." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(5);
	cout << "mcguffin after inserting 5." << endl;
	mcguffin->printTree();
	cout << endl;
	cout << "testing deletion cases for sibcount = 7." << endl;
	cout << endl;
	mcguffin -> insert(2);
	cout << "mcguffin after inserting 2." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(6);
	cout << "mcguffin after inserting 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(11);
	cout << "mcguffin after removing 11." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(11);
	cout << "mcguffin after inserting 11." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(6);
	cout << "mcguffin after removing 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(14);
	cout << "mcguffin after inserting 14." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(5);
	cout << "mcguffin after removing 5." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(5);
	cout << "mcguffin after inserting 5." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(14);
	cout << "mcguffin after removing 14." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(14);
	cout << "mcguffin after inserting 14." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(6);
	cout << "mcguffin after inserting 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(3);
	cout << "mcguffin after removing 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(2);
	cout << "mcguffin after removing 2." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(3);
	cout << "mcguffin after inserting 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(6);
	cout << "mcguffin after removing 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(6);
	cout << "mcguffin after inserting 6." << endl;
	mcguffin->printTree();
	cout << endl;
	
	cout << "testing the deletion cases for sibcount = 6." << endl;
	cout << endl;
	
	mcguffin -> remove(14);
	cout << "mcguffin after removing 14." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(3);
	cout << "mcguffin after removing 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(3);
	cout << "mcguffin after inserting 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(6);
	cout << "mcguffin after removing 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(6);
	cout << "mcguffin after inserting 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(11);
	cout << "mcguffin after removing 11." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(11);
	cout << "mcguffin after inserting 11." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(6);
	cout << "mcguffin after removing 6." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> insert(14);
	cout << "mcguffin after inserting 14." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(3);
	cout << "mcguffin after removing 3." << endl;
	mcguffin->printTree();
	cout << endl;
	mcguffin -> remove(39);
	cout << "mcguffin after removing 39." << endl;
	mcguffin->printTree();
	cout << endl;
	cout << "test run concluded." << endl;
	
}