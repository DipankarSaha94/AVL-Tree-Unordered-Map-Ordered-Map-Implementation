#include<bits/stdc++.h> 
using namespace std; 

template<typename K,typename V> 
class Map{
struct Node  
{
    K key; 
	V val; 
    Node *left;  
    Node *right;  
    int height;
};

Node* root;
int size; 

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
Node* maintainBalanceInsert(Node* node, K key){
	
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
   
  
Node* insert(Node *node, K key,V val)  
{
    if (node == NULL){
    	node = new Node;
    	node->key = key;
    	node->val = val;
    	node->left = NULL;  
    	node->right = NULL;  
    	node->height = 1;
    	size += 1;

		return node;  	
	}
  
    if (key < node->key)  
        node->left = insert(node->left, key,val);  
    else if(key > node->key) 
        node->right = insert(node->right, key,val);
    else{
    	node->val = val;
    	return node;
	}

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
Node* erase(Node* node, K key)  
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
			if(size>0) 
            size--;
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

bool search(Node* node,K val){
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

V& find(Node* node,K val){
	Node* current = node;     
    while (current){
        if (current->key > val){
        	current = current->left;
		}
        else if (current->key < val){
            current = current->right;
        }
        else{
        	return current->val;
		}
    }
}

void inOrder(Node *root)  
{  
    if(root != NULL)  
    {    
        inOrder(root->left);
    	cout << root->key << " "<<root->val <<"  ";
        inOrder(root->right);  
    }  
} 
	
public:
    Map()
    {
        root = NULL;
        size =0;
    }

    void insert(K x,V y)
    {
        root = insert(root,x,y);
    }
    void erase(K x)
    {
        root = erase(root,x);
    }
    bool search(K x){
    	return (search(root,x));
	}
	void display()
    {
        inOrder(root);
        cout << endl;
    }
	void clear(){
		root = NULL;
		size = 0;
	}	
	V& operator[](K k){
		V ans;
		if(search(root,k)){
		return find(root,k);
		}
		else{
			root = insert(root,k,ans);
			return find(root,k);
		}
	}
	
	int mapsize(){
		return size;
	}
 
};    

int main()  
{
	Map<string,string> Ordered_Map;  
	string key,value;
	//char key,value;
	//double key,value;
	//int key,value;
	int q,n;
	cin>>q;
	while(q--){
		cin>>n;
	switch(n){
		case 1:
			cin>>key>>value;
			Ordered_Map.insert(key,value);
			Ordered_Map.display();
			break;
		case 2:
			cin>>key;
			Ordered_Map.erase(key);
			Ordered_Map.display();
			break;
		case 3:
			cin>>key;
			cout<<Ordered_Map.search(key)<<endl;
			break;
		case 4:
			cin>>key;
			cout<<Ordered_Map[key]<<endl;
			break;
		case 5:
			cin>>key>>value;
			Ordered_Map[key] = value;
			cout<<Ordered_Map[key]<<endl;
			break;
		case 6:
			cout<<Ordered_Map.mapsize()<<endl;
			break;
		case 7:
			Ordered_Map.clear();
			Ordered_Map.display();
			break;
		default: 
			cout<<"Invalid selection "<<endl;
	}
}
	return 0;
}
