#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct myNode
{
    int key;
    myNode* left;
    myNode* right;

    myNode(int k):key(k),left(NULL),right(NULL){}

    ~myNode()
    {
        key = 0;
    }
};

class myTree
{
    myNode* root;
    int max;
    
    public:

        

        myTree();
        ~myTree();

        int height(myNode* node);
        int balanceFactor(myNode* node);

        myNode* RRrotate(myNode* node);
        myNode* LLrotate(myNode* node);
        myNode* LRrotate(myNode* node);
        myNode* RLrotate(myNode* node);
        myNode* balance(myNode* node);

        void insert(int key);
        myNode* insert(myNode* node, int key);
        void destroy(myNode* node);

        //TODO
        //swap function gia na mhn parabiazetai h sunthikh ths askhshs
        void swapKeys(myNode* node);

        //checkin for max
        void checkForMax(int key);

        void preOrder();
        myNode* preOrder(myNode* node);


        void print2D();
        void print2DUtil(myNode *, int) ;

        void printLevelOrder();
        void printLevelOrder(myNode*);
        void printGivenLevel(myNode*, int);  

        int get_max();

        void deleteMax();
        void deleteMax(myNode*);

        void swapNodeKeys(myNode*,myNode*);



};

void myTree::swapNodeKeys(myNode* node1,myNode* node2)
{
    int temp;
    temp = node1->key;
    node1->key = node2->key;
    node2->key = temp;
}

void myTree::deleteMax()
{
    deleteMax(root);
}

void myTree::deleteMax(myNode* node)
{
    //check if root = max
    // delete and fix tree
    // else go rigth
    if(node->key == max)
    {
        node->key = -1;
        //swap keys mexri na ftasei to -1 se fullo 
        //delete to node fullo
        while(height(node) != 1)
        {
            cout << "... " << height(node) << endl;
            if(node->left->key > node->right->key)
            {
                swapNodeKeys(node->left,node);
                node = node->left;
            }
            else
            {
                swapNodeKeys(node->right,node);
                node = node->right;
            }
            
        }
    }
    else
    {
        deleteMax(node->right);
    }
    
}

int myTree::get_max()
{
    return max;
}

void myTree::print2DUtil(myNode *node, int space)  
{  
    // Base case  
    if (node == NULL)  
        return;  
  
    // Increase distance between levels  
    space += 10;  
  
    // Process right child first  
    print2DUtil(node->right, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = 10; i < space; i++)  
        cout<<" ";  
    cout<<node->key<<"\n";  
  
    // Process left child  
    print2DUtil(node->left, space);  
}  
  
// Wrapper over print2DUtil()  
void myTree::print2D()  
{  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  

void myTree::preOrder()  
{  
    preOrder(root);
} 

myNode* myTree::preOrder(myNode* node)
{
    if(node != NULL)  
    {    
        preOrder(node->left); 
        cout << node->key << "(" << height(node) << ")"; 
        preOrder(node->right);        
    }
}

void myTree::swapKeys(myNode* node)
{
    int temp;
    temp = node->key;
    node->key = node->left->key;
    node->left->key = temp;
    cout << "swapping keys" << endl;
}

void myTree::checkForMax(int key)
{
    if(key > max) 
    {
        max = key;
        cout << "max max max:" << max << endl;
    }
}

myTree::myTree():root(NULL),max(-1){}

myTree::~myTree()
{
    destroy(root);
}

int myTree::height(myNode* node)
{
    int h=0;
    if(node!=NULL)
    {
        int lheight=height(node->left);
	    int rheight=height(node->right); 

        if(lheight>rheight)
        {
            h=lheight;
        }
        else
        {
            h=rheight;
        }
        h+=1;
    }
    return h;
}

int myTree::balanceFactor(myNode* node)
{
    int lheight=height(node->left);
	int rheight=height(node->right);
	
	return lheight-rheight;
}

myNode* myTree::LLrotate(myNode* node)
{
    myNode* temp;
    temp = node->left;
    node->left = temp->right;
    temp->right = node;
    if(temp->right->key > node->key)
    {
        swapKeys(temp);
        cout << "happened" << endl;
    }
    cout << "LL rotation" << endl;
    return temp;
}

myNode* myTree::RRrotate(myNode* node)
{
    myNode* temp;
    temp = node->right;
    node->right = temp->left;
    temp->left = node;
    if(temp->left->key > node->key)
    {
        swapKeys(temp);
        cout << "happened3" << endl;
    }
    cout << "RR rotation" << endl;
    return temp;
}

myNode* myTree::LRrotate(myNode* node)
{
    cout << "LR rotating" << endl;
    myNode* temp;
    temp = node->right;
    node->left = RRrotate(temp);
    temp = NULL;
    delete temp;
    return LLrotate(node);
}

myNode* myTree::RLrotate(myNode* node)
{
    cout << "RL rotating" << endl;
    myNode* temp;
    temp = node->left;
    node->right = LLrotate(temp);
    temp = NULL;
    delete temp;
    return RRrotate(node);
}

myNode* myTree::balance(myNode* node)
{
    if(balanceFactor(node)>1)
    {
        if(balanceFactor(node->left)>0)
        {
            node = LLrotate(node);
        }
        else
        {
            node = LRrotate(node);
        }
        
    }
    else if(balanceFactor(node)<-1)
    {
        if(balanceFactor(node->right)>0)
        {
            node = RLrotate(node);
        }
        else
        {
            node = RRrotate(node);
        }
    }
    return node;
}

// auth h insert kaleitai apo thn main
// 
void myTree::insert(int key)
{
    root = insert(root,key);
}

myNode* myTree::insert(myNode* node, int key)
{
    //if tree is empty
    //add the node to the root
    
    if(node == NULL)
    {
        cout << "adding key to the root: " << key << endl;
        node = new myNode(key);
        checkForMax(node->key);
        //node = balance(node);
        return node;
    }

    if (key > node->key)
    {
        //if(node->right != NULL)
        //{
        cout << "checking right: " << key << endl;
        node->right = insert(node->right, key);
        node = balance(node);
        //}
        /*else
        {
            cout << "adding new node right: " << key << endl;
            node->right = new myNode(key);
            checkForMax(node->key);
            node = balance(node);

        }*/
    
        
    }
    else if (key < node->key)
    {
        int coin = rand() % 2;

        int bf=balanceFactor(node);
        //if coin is 1 go right else left
        if(bf>0)
        {
            //if(node->right != NULL)
            //{
            cout << "checking for going right: " << key << endl;
            node->right = insert(node->right, key);
            node = balance(node);
            //}
            /*else
            {
                cout << "adding new node right: " << key << endl;
                node->right = new myNode(key);
                checkForMax(node->key);
                node = balance(node);

            }*/
        }
        else
        {
            //if(node->left != NULL)
            //{
            cout << "checking for going left: " << key << endl;
            node->left = insert(node->left, key);
            node = balance(node);
            //}
            /*else
            {
                cout << "adding new node left: " << key << endl;
                node->left = new myNode(key);
                checkForMax(node->key);
                node = balance(node);
            }*/
        }
        

    }
    //else uparxei hdh h timh
    //node = balance(node);
    return node;
    
}

void myTree::destroy(myNode* node)									
// destroy is used in destructor to delete nodes of tree recursively
{
	if(node!=NULL)
	{
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

void myTree::printLevelOrder()
{
    printLevelOrder(root);
}

void myTree::printLevelOrder(myNode* node)  
{  
    int h = height(node);  
    int i;  
    for (i = 1; i <= h; i++)  
        printGivenLevel(node, i);  
}  
  
/* Print nodes at a given level */
void myTree::printGivenLevel(myNode* node, int level)  
{  
    if (node == NULL)  
        return;  
    if (level == 1)  
        cout << node->key << " ";  
    else if (level > 1)  
    {  
        printGivenLevel(node->left, level-1);  
        printGivenLevel(node->right, level-1);  
    }  
}  

int main()
{

    srand (time(NULL));
    myTree* treeee = new myTree();
    treeee->insert(90);
    treeee->insert(50);
    treeee->insert(60);
    treeee->insert(66);
    treeee->insert(12);
    treeee->insert(90);
    treeee->insert(30);
    treeee->insert(9);
    treeee->insert(70);
    treeee->print2D();
    cout << endl;
    //cout << treeee->get_max() << endl;
    treeee->deleteMax();
    treeee->print2D();
    cout << "EISAI O KALUTEROS PROGRAMMER TOU KOSMOU OLOU!!!1111!!" << endl;
}