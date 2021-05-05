#include<bits/stdc++.h> 
using namespace std; 

template<typename K,typename V> 
class Hashmap{
struct Node  
{
    K key;  
    V value;  
    Node *next;   
};
Node* arr[100]; 

public:
	Hashmap(){
		for(int i =0;i<100;i++){
			arr[i]=NULL;
		}
	}
	//Universal hashing for double,int,char is H(x) = ((ax+b) mod p) mod m where m is bucket size, p is prime >=m,
	// and  a, b are randomly chosen integers whose modulo with p is != 0
	
	int hash(int val){
		return ((val*11 + 37)%107)%100;
	}
	int hash(double val){
		int temp = val*11 + 37;
		return ((temp)%107)%100;
	}
	int hash(char val){
		return ((val*11 + 37)%107)%100;
	}
	// for sting i am using Bernstein's hash function is h = ((h*a) + x[i]) mod p ..for each chacter in string x where a is 33 and initial value of h is 5381  
	int hash(string val){
		int h = 5381,a=33,p=107;
		for(int i =0;i<val.length();i++){
			h = ((h*a) + val[i]) % p;
		}
		return h%100;
	}
	void insert(K k,V v){
		int index = hash(k);
		if(arr[index]){
			Node* ptr = arr[index];
			while(ptr->next){
				ptr = ptr->next;
			}
			Node* newnode = new Node();
			newnode->key = k;
			newnode->value = v;
			newnode->next = NULL;
			ptr ->next = newnode;
		}
		else{
			Node* newnode = new Node();
			newnode->key = k;
			newnode->value = v;
			newnode->next = NULL;
			arr[index] = newnode;
		}
	}
	V operator[](K k){
		int index = hash(k);
		V val;
		if(arr[index]){
			Node* ptr = arr[index];
			while(ptr){
				if(ptr->key == k){
					val = ptr->value;
				}
				ptr=ptr->next;
			}
			//cout<<"key not present"<<endl;
		}
		else{
			//cout<<"key not present"<<endl;
		}
		return val;
	}
	void erase(K k){
		int index = hash(k),c=0;;
		if(arr[index]){
			Node* ptr = arr[index];
			while(ptr){
				ptr=ptr->next;
				c++;
			}
		}
		if(c ==1){
			arr[index] = NULL;
		}
		else if(c >1){
			if(arr[index]->key == k){
				arr[index] = arr[index]->next;
			}
			else{
				Node* ptr = arr[index];Node* ptr2 = ptr->next;
				while(ptr2){
				if(ptr2->key == k){
					ptr->next = ptr2->next;
					break;
				}
				ptr=ptr->next;
				ptr2=ptr->next;
			}	
			}	
		}
	}
	string find(K k){
		int index = hash(k);
		if(arr[index]){
			Node* ptr = arr[index];
			while(ptr){
				if(ptr->key == k){
					return "True";
				}
				ptr=ptr->next;
			}
		}
		return "False";
	}
	void display(){
		for(int i =0;i<99;i++){
			Node* current = arr[i];
			if(current){
				cout<<i<<" ";
				while(current){
					cout<<"[ "<<current->key<<" "<<current->value<<" ]"<<" ";
					current = current->next;
				}
			}
		}
	}
};

int main(){
	Hashmap<char,char> Unordered_Map;  
	//string key,value;
	char key,value;
	//double key,value;
	//int key,value;
	int q,n;
	cin>>q;
	while(q--){
		cin>>n;
	switch(n){
		case 1:
			cin>>key>>value;
			Unordered_Map.insert(key,value);
			Unordered_Map.display();
			break;
		case 2:
			cin>>key;
			Unordered_Map.erase(key);
			Unordered_Map.display();
			break;
		case 3:
			cin>>key;
			cout<<Unordered_Map.find(key)<<endl;
			break;
		case 4:
			cin>>key;
			cout<<Unordered_Map[key]<<endl;
			break;
		default:
			cout<<"invalid selection"<<endl;
			break;
	}
}
	return 0;
}
