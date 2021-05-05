#include<bits/stdc++.h> 
using namespace std; 

template<typename T> 
class AVLTree{
struct Node  
{
    T key;  
    Node *left;  
    Node *right;  
    int height;
};

Node* root;

int height(Node* n)
{
    return (n == NULL ? 0 : n->height);
}

int getBalance(Node *n)  
{
	return (n == NULL ? 0 : (height(n->left) - height(n->right)));
}

Node *rightRotate(Node *node)  
{  
    Node *tnode = node->left;  
    Node *temp = tnode->right;  
  
    tnode->right = node;  
    node->left = temp;  
   
    node->height = max(height(node->left),height(node->right)) + 1;  
    tnode->height = max(height(tnode->left),height(tnode->right)) + 1;  
   
    return tnode;  
}  
  
Node *leftrightRotate(Node *node)  
{  
    node->left = leftRotate(node->left);  
    return rightRotate(node);    
}  

Node *rightleftRotate(Node *node)  
{  
    node->right = rightRotate(node->right);  
    return leftRotate(node);  
}  
  
Node *leftRotate(Node *node)  
{  
    Node *tnode = node->right;  
    Node *temp = tnode->left;  
   
    tnode->left = node;  
    node->right = temp;  
   
    node->height = max(height(node->left),height(node->right)) + 1;  
    tnode->height = max(height(tnode->left),height(tnode->right)) + 1;  
   
    return tnode;  
}  
  
Node* maintainBalanceInsert(Node* node, T key){
	
	int balance = getBalance(node);  
  
    // L-L Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // R-R Case  
    if (balance < -1 && key >= node->right->key)  
        return leftRotate(node);  
  
    // L-R Case  
    if (balance > 1 && key >= node->left->key)  
    {  
        return leftrightRotate(node);  
    }  
  
    // R-L Case  
    if (balance < -1 && key < node->right->key)  
    {    
        return rightleftRotate(node);  
    }  
    return node;
}

Node* maintainBalanceErase(Node* node){
	int balance = getBalance(node);  

    // L-L Case  
    if (balance > 1 && getBalance(node->left) > 0)  
        return rightRotate(node);  
  
    // L-R Case  
    if (balance > 1 && getBalance(node->left) < 0)  
    {  
        return leftrightRotate(node); 
    }  
  
    // R-R Case  
    if (balance < -1 && getBalance(node->right) < 0)  
        return leftRotate(node);  
  
    // R-L Case  
    if (balance < -1 && getBalance(node->right) > 0)  
    {  
        return rightleftRotate(node); 
    }  
    return node;
}

Node* insert(Node *node, T key)  
{
    if (node == NULL){
    	node = new Node;
    	node->key = key;
    	node->left = NULL;  
    	node->right = NULL;  
    	node->height = 1;

		return node;  	
	}
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else  
        node->right = insert(node->right, key);    
  	
    node->height = 1 + max(height(node->left),height(node->right));
   
    return maintainBalanceInsert(node,key);  
} 

Node * minNode(Node* node)  
{  
    Node* current = node;  
  
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}
Node* erase(Node* node, T key)  
{  

    if (node == NULL)  
        return node;  
   
    if ( key < node->key )  
        node->left = erase(node->left, key);  
   
    else if( key > node->key )  
        node->right = erase(node->right, key);  
        
    else
    {  
        if( (node->left == NULL) || (node->right == NULL) )  
        {  
            Node *temp = node->left ? node->left : node->right;  
    
            if (temp == NULL)  
            {  
                temp = node;  
                node = NULL;  
            }  
            else
            *node = *temp; 
            free(temp);  
        }  
        else
        {  
            Node* temp = minNode(node->right);  
            node->key = temp->key;  
            node->right = erase(node->right,temp->key);  
        }  
    }  
  
    if (node == NULL)  
    return node;  
  
    node->height = 1 + max(height(node->left),height(node->right));
  
    return maintainBalanceErase(node);  
} 

void count(Node* node,T val,int* ans){
	if(!node)
		return;
	if(node->key==val){
		*ans += 1;
		count(node->left,val,ans);
		count(node->right,val,ans);
	}
		
	if(node->key>val)
		count(node->left,val,ans);
	if(node->key<val)
		count(node->right,val,ans);
}
void closeval(Node* node,int val,int *m,int *ans){
	if(!node)
	return;
	int cval;
	if(val >= node->key)
		cval = val - node->key;
	else
		cval = node->key - val;
		
	if(*m > cval){
		*m = cval;
		*ans = node->key;
 	}
	if(val>node->key)
		closeval(node->right, val, m, ans);
	else if(node->key>val)
		closeval(node->left, val, m, ans);	
}
void closeval(Node* node,char val,int *m,int *ans){
	if(!node)
	return;
	int cval;
	if(val >= node->key)
		cval = val - node->key;
	else
		cval = node->key - val;
	
	if(*m > cval){
		*m = cval;
		*ans = node->key;
 	}
	if(val>node->key)
		closeval(node->right, val, m, ans);
	else if(node->key>val)
		closeval(node->left, val, m, ans);	
}
void closeval(Node* node,double val,double *m,double *ans){
	if(!node)
	return;
	double cval;
	if(val >= node->key)
		cval = val - node->key;
	else
		cval = node->key - val;
	
	if(*m > cval){
		*m = cval;
		*ans = node->key;
 	}
	if(val>node->key)
		closeval(node->right, val, m, ans);
	else if(node->key>val)
		closeval(node->left, val, m, ans);	
}
void closeval(Node* node,string val,int *m,string *ans){
	if(!node)
	return;

	int  cval = stringVal(val,node->key);
	
	if(*m > cval){
		*m = cval;
		*ans = node->key;
 	}
	if(val>node->key)
		closeval(node->right, val, m, ans);
	else if(node->key>val)
		closeval(node->left, val, m, ans);	
}
int stringVal(string s1, string s2){
	int sum1 =0,sum2=0;
	for(int i=0;i<s1.size();i++)
		sum1 += s1[i];
	for(int i=0;i<s2.size();i++)
		sum2 += s2[i];
	if(sum1>sum2)
		return sum1-sum2;
	else
		return sum2-sum1;
}
void range(Node* node,T val1,T val2,int *ans){
	if(!node)
		return;
	if(node->key>=val1 && node->key<=val2){
		*ans += 1;
		range(node->left,val1,val2,ans);
		range(node->right,val1,val2,ans);
	}
		
	if(node->key>=val1 && node->key>val2)
		range(node->left,val1,val2,ans);
	if(node->key<val1 && node->key<=val2)
		range(node->right,val1,val2,ans);	
}
bool search(Node* node,T val){
	Node* current = node;     
    while (current){
        if (current->key > val)
            current = current->left;
        else if (current->key < val){
            current = current->right;
        }
        else{
        	return true;
		}
    }
    return false;
}
void preOrder(Node *root)  
{  
    if(root != NULL)  
    {  
    	cout << root->key << " "; 
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}
void kthutil(Node* node, T *ans,int k , int *count){
	if(!node || *count >= k)
	return;

	kthutil(node->right,ans,k,count);
	*count += 1;	
	if(k == *count)
		*ans = node->key;	
	kthutil(node->left,ans,k,count);	
}
void inOrder(Node *root)  
{  
    if(root != NULL)  
    {    
        inOrder(root->left);
    	cout << root->key << " ";
        inOrder(root->right);  
    }  
} 

void lowerBound(Node* node,T val,int* ans)  
{  
    if(!node)
		return;
	if(node->key < val){
		*ans += 1;
		lowerBound(node->left,val,ans);
		lowerBound(node->right,val,ans);
	}
	else
		lowerBound(node->left,val,ans);
} 
void upperBound(Node* node,T val,int* ans)  
{  
    if(!node)
		return;
	if(node->key <= val){
		*ans += 1;
		upperBound(node->left,val,ans);
		upperBound(node->right,val,ans);
	}
	else
		upperBound(node->left,val,ans);
} 
public:
    AVLTree()
    {
        root = NULL;
    }

    void insert(T x)
    {
        root = insert(root,x);
    }
    void erase(T x)
    {
        root = erase(root,x);
    }
   int lowerBound(T x)
    {
    	int c=1;
        lowerBound(root,x,&c);
        return c;
    }
    int upperBound(T x)
    {
    	int c=1;
        upperBound(root,x,&c);
        return c;
    }
    bool search(T x){
    	return (search(root,x));
	}
	int count(T x){
		int c = 0;
		count(root,x,&c);
    	return c;
	}
	void display()
    {
        inOrder(root);
        cout << endl;
        preOrder(root);
        cout << endl;
    }
	int closeval(int x){
		int num1 =1000000, num2=0;
		closeval(root,x,&num1,&num2);
		return num2;	
	}	
	char closeval(char x){
		int num1 =1000000, num2=0;
		closeval(root,x,&num1,&num2);
		return num2;	
	}
	double closeval(double x){
		double num1 =1000000, num2=0.0;
		closeval(root,x,&num1,&num2);
		return num2;	
	}
	string closeval(string x){
		int num1 =1000000; string ans= "";
		closeval(root,x,&num1,&ans);
		return ans;	
	}
	int range(T val1,T val2){
		int ans =0;
		range(root,val1,val2,&ans);
		return ans;
	}
	T kthlargest(int x){
		int count = 0;
		T ans;
		kthutil(root,&ans,x,&count);
		return ans;
	}
 
};    

int main()  
{
	AVLTree<int> Tree;  
	//string value,value2;
	//char value,value2;
	//double value,value2;
	int value,value2;
	int q,n,k;
	cin>>q;
	while(q--){
		cin>>n;
	switch(n){
		case 1:
			cin>>value;
			Tree.insert(value);
			Tree.display();
			break;
		case 2:
			cin>>value;
			Tree.erase(value);
			Tree.display();
			break;
		case 3:
			cin>>value;
			cout<<Tree.search(value)<<endl;
			break;
		case 4:
			cin>>value;
			cout<<Tree.count(value)<<endl;
			break;
		case 5:
			cin>>value;
			cout<<Tree.lowerBound(value)<<endl;
			break;
		case 6:
			cin>>value;
			cout<<Tree.upperBound(value)<<endl;
			break;
		case 7:
			cin>>value;
			cout<<Tree.closeval(value)<<endl;
			break;
		case 8:
			cin>>k;
			cout<<Tree.kthlargest(k)<<endl;
			break;
		case 9:
			cin>>value>>value2;
			cout<<Tree.range(value,value2)<<endl;
			break;
		}
	}
	return 0;
}
