#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data (Linked List)
class Node{
public:
	string key;
	int value;
	Node(string key,int value){
		this->key = key;
		this->value = value;
	}
};


//LRU Cache Data Structure
class LRUCache{
public:
	int maxSize;
	list<Node> l;
	unordered_map<string,list<Node>::iterator > m;

	LRUCache(int maxSize){
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}

	void insertKeyValue(string key,int value){
		//2 cases
		if(m.count(key)!=0){
			//replace the old value and update
			auto it = m[key];
			it-> value = value;
		}
		else{
			//check if cache if full or not
			//remove the least recently used item from cache
			if(l.size()==maxSize){
				Node last = l.back();
				m.erase(last.key); //remove from hashmap
				l.pop_back(); //remove from linked list
			}

			Node n(key,value);
			l.push_front(n);
			m[key] = l.begin();
		}
	}

	int* getValue(string key){
			
		if(m.count(key)!=0){
			auto it = m[key];

			int value = it->value;
			l.push_front(*it);
			l.erase(it);
			m[key] = l.begin();
			return &l.begin()->value;
		}	
		return NULL;

	}

	string mostRecentKey(){
		return l.front().key;
	}

};


int main(){
	LRUCache lru(3);
	lru.insertKeyValue("Shivani",10);
	lru.insertKeyValue("Riya",20);
	lru.insertKeyValue("Tushar",30);
	cout << lru.mostRecentKey() <<endl;

	lru.insertKeyValue("Shivani",40);
	cout << lru.mostRecentKey() <<endl;

	int *orders = lru.getValue("Shivani");
	if(orders!=NULL){
		cout<<"Order for Shivani "<<*orders <<endl;
	}


	lru.insertKeyValue("OM",20);

	if(lru.getValue("priya")==NULL){
		cout<<"priya doesn't exist";
	}

	if(lru.getValue("Tushar")==NULL){
		cout<<"Tushar doesn't exist";
	}

	if(lru.getValue("Priya")==NULL){
		cout<<"Priya doesn't exist";
	}
	if(lru.getValue("Shivani")==NULL){
		cout<<"Shivani doesn't exist";
	}

	

	return 0;
}	
