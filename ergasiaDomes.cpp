#include<cstdlib>
#include<iostream>

using namespace std;

class LinkedList
{
	private:
		struct NodeCol
		{
				int col;
				int data;
				NodeCol* nextCol;

				NodeCol(int column=0,int d=0):col(column),data(d),nextCol(NULL){};
				//EDW GIATI OXI GET COL?
				int get_data()
				{
					return data;
				}
				int get_column()
				{
					if(this!=NULL)
					{
						return col;
					}
					else
					{
						return 40;
					}
				}
		};

		struct NodeRow
		{
				int row;
				NodeCol* start;
				NodeRow* nextRow;
			
				NodeRow(int r=0):row(r),start(NULL),nextRow(NULL){};

				int get_row()
				{
					return row;
				};
		};

		NodeRow* head;

	public:
		LinkedList():head(NULL){};

		void InsertRow(int r);
		void InsertCol(int r,int c,int d);
		void Print();
		void Delete();
		void fillTheArray(int r, int c);
		LinkedList Add(LinkedList& l1,LinkedList& l2,int r, int c);
		LinkedList Insertion(int r,int c);

};

void LinkedList::InsertRow(int r)
{
	if(head==NULL)
	{
		NodeRow *next=new NodeRow(r);
		head=next;
	}
	else
	{
		NodeRow *tmp=head;
		while(tmp->nextRow!=NULL)
		{
			tmp=tmp->nextRow;
		}

		NodeRow *next=new NodeRow(r);
		tmp->nextRow=next;

		tmp=NULL;
		delete(tmp);
		}	
}

void LinkedList::InsertCol(int r,int c,int d)
{
	NodeRow *tmp=head;
	while(true)
	{
		if(tmp->get_row()==r)
		{
			if(tmp->start==NULL)
			{
				NodeCol *temp=new NodeCol(c,d);
				tmp->start=temp;
			}
			else
			{
				NodeCol *temp=tmp->start;
				
				while(temp->nextCol!=NULL)
				{
					temp=temp->nextCol;
				}

				NodeCol *next=new NodeCol(c,d);
				temp->nextCol=next;

				temp=NULL;
				delete(temp);
			}
			break;
		}
		tmp=tmp->nextRow;
	}
}

void LinkedList::Print()
{			//na tsekarei poia stoixeia einai 0 kai poia oxi
	NodeRow *tmp = head;
	while(tmp != NULL)
	{
		NodeCol *temp=tmp->start;
		while(temp!=NULL)
		{
			cout << temp->get_data() << " " ;
			temp=temp->nextCol;
		}
		cout << endl;
		tmp = tmp->nextRow;
	}
}
void LinkedList::Delete()
{
	NodeRow *tmp = this->head;
	NodeCol *ctmp = tmp->start;
	if(ctmp->nextCol!=NULL)
	{
		NodeCol *ctmp2 = ctmp->nextCol;
		tmp->start = ctmp2;
		free(ctmp);
	}
	else
	{
		free(ctmp);
		NodeRow *temp = tmp->nextRow;
		head = temp;
		free(tmp);
	}
}

void LinkedList::fillTheArray(int r, int c){
	int Array[r][c];
	NodeRow *tmp = head;
	for(int i=0; i<r; i++)
	{
		if(tmp->get_row()< i)
		{
			for (int j=0;j<c;j++)
			{
				Array[i][j] = 0;
				cout << Array[i][j] << " ";
			}
		}
		while(tmp != NULL)
		{
			if(tmp->get_row() != i)
			{
				for(int j=0;j<c;j++)
				{
					Array[i][j] = 0;
					cout << Array[i][j] << " ";
				}
				cout << endl;
				break;
			}
			NodeCol *temp = tmp->start;
			while(temp!= NULL)
			{
				for(int j=0;j<c;j++)
				{
					if(temp == NULL)
					{
						Array[i][j] = 0;
						cout << Array[i][j] << " ";
						continue;
					}
					if(temp->get_column() == j)
					{
						Array[i][j] = temp->get_data();
						cout << Array[i][j] << " ";
						temp=temp->nextCol;
					}
					else
					{
						Array[i][j] = 0;
						cout << Array[i][j] << " ";
					}
				}
			}
			tmp = tmp->nextRow;
			cout << endl;
			break;
		}
	}
	
}

LinkedList LinkedList::Insertion(int row,int col)
{
	LinkedList sth;
	int x;
	int i,j;
	for(int i=0; i<row;i++)
	{
	int found=0;	   //den exoun vrethei stoixeia
		for(int j=0;j<col;j++)//mpainei sto disdiastato
		{
			cout << "Give array's next element: " << endl;
			cin >> x;
			if(found==0)//an olh h grammh exei mhdenika den tupwnetai kan
			{
				if(x!=0)//an den einai 0
				{
					found=1;
					sth.InsertRow(i);
					sth.InsertCol(i,j,x);
				}
			}
			else
			{
				if(x!=0)
				{
					sth.InsertCol(i,j,x);
				}
			}
		}
		cout << endl;
	}
	return sth;
}

LinkedList LinkedList::Add(LinkedList& l1, LinkedList& l2, int row, int col)
{	
	LinkedList sum;
	NodeRow *tmp = sum.head;
	NodeRow *tmp1 = l1.head;
	NodeRow *tmp2 = l2.head;
	
	for(int i=0;i<row;i++)
	{ 	
		if(tmp1!=NULL && tmp2!=NULL)
		{	
			if(tmp1->get_row()==tmp2->get_row())
			{	
				sum.InsertRow(tmp1->get_row());
				NodeCol *ctmp1 = tmp1->start;
				NodeCol *ctmp2 = tmp2->start;
				for(int j=0;j<col;j++)
				{
					if(ctmp1!=NULL && ctmp2!=NULL)
					{
						if(ctmp1->get_column()==ctmp2->get_column())
						{
							sum.InsertCol(tmp1->get_row(),ctmp1->get_column(),ctmp1->get_data()+ctmp2->get_data());
							l1.Delete();
							l2.Delete();
							ctmp1=ctmp1->nextCol;
							ctmp2=ctmp2->nextCol;
						}
						else if(ctmp1->get_column()<ctmp2->get_column())
						{
							sum.InsertCol(tmp1->get_row(),ctmp1->get_column(),ctmp1->get_data());
							l1.Delete();
							ctmp1=ctmp1->nextCol;
						}
						else if(ctmp2->get_column()<ctmp1->get_column())
						{
							sum.InsertCol(tmp2->get_row(),ctmp2->get_column(),ctmp2->get_data());
							l2.Delete();
							ctmp2=ctmp2->nextCol;
						}
					}
					else if(ctmp1==NULL && ctmp2!=NULL)
					{
						sum.InsertCol(tmp2->get_row(),ctmp2->get_column(),ctmp2->get_data());
						l2.Delete();
						ctmp2=ctmp2->nextCol;
					}
					else if(ctmp2==NULL && ctmp1!=NULL)
					{
						sum.InsertCol(tmp1->get_row(),ctmp1->get_column(),ctmp1->get_data());
						l1.Delete();
						ctmp1=ctmp1->nextCol;

					}
				}
				tmp1=tmp1->nextRow;
				tmp2=tmp2->nextRow;
			}
			else if(tmp1->get_row()<tmp2->get_row())
			{

				sum.InsertRow(tmp1->get_row());
				int temporary = tmp1->get_row();
				NodeCol *ctmp = tmp1->start;
				while(tmp1->get_row() == temporary && ctmp!=NULL)
				{
					sum.InsertCol(tmp1->get_row(),ctmp->get_column(),ctmp->get_data());
					l1.Delete();
					ctmp=ctmp->nextCol;
				}
				tmp1=tmp1->nextRow;

			}
			else
			{
				sum.InsertRow(tmp2->get_row());
				NodeCol *ctmp = tmp2->start;
				while(ctmp!=NULL)
				{
					sum.InsertCol(tmp2->get_row(),ctmp->get_column(),ctmp->get_data());
					l2.Delete();
					ctmp=ctmp->nextCol;
				}
				tmp2=tmp2->nextRow;
			}
		}
		else if(tmp1==NULL && tmp2!=NULL)
		{
			sum.InsertRow(tmp2->get_row());
			NodeCol *ctmp = tmp2->start;
			while(ctmp!=NULL)
			{
				sum.InsertCol(tmp2->get_row(),ctmp->get_column(),ctmp->get_data());
				l2.Delete();
				ctmp=ctmp->nextCol;
			}
			tmp2=tmp2->nextRow;
		}
		else if(tmp2==NULL && tmp1!=NULL)
		{
			sum.InsertRow(tmp1->get_row());
			NodeCol *ctmp=tmp1->start;
			while(ctmp!=NULL)
			{
				sum.InsertCol(tmp1->get_row(),ctmp->get_column(),ctmp->get_data());
				l1.Delete();
				ctmp=ctmp->nextCol;
			}
			tmp1=tmp1->nextRow;

		}

	}
	return sum;
}


int main()
{
	int row,column;

	cout << "Give array'a dimensions: (2 inputs)" << endl;
	cin >> row;
	cin >> column;

	LinkedList sth1 = sth1.Insertion(row,column);
	cout << "___________" << endl;
	LinkedList sth2 = sth2.Insertion(row,column);
	cout << "___________" << endl;

	sth1.Print();
	cout << "___________" << endl;
	sth2.Print();
	cout << "___________" << endl;

	LinkedList sth3;
	sth3 = sth3.Add(sth1,sth2,row,column);
	sth3.Print();
	cout << "___________" << endl;
	sth3.fillTheArray(row,column);
}