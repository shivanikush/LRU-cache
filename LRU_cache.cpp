#include<bits/stdc++.h>
#include<iostream>
using namespace std;

//Create Global variable for cache size(total number of cache lines)
int cacheSize;


//Create Global data structures for cache and TLB lookup on heap
	//Cache -> Queue
	list<int> cache;
	//Hash map for TLB
	unordered_map<int, list<int> :: iterator> TLB;

//LRU implementation
void access(int page){
	if(TLB.find(page) == TLB.end()){
		cout << "Cache Miss.\n\tAdding page to cache...\n\t";

		if(cache.size() == cacheSize){
			cout << "All cache lines full.\n\tRemoving LRU page...\n\t";
			int page_to_be_removed = (cache.back());
			cout << "Removed page"<< page_to_be_removed << endl;
			TLB.erase(page_to_be_removed); //removing page entry from TLB
			cache.pop_back();
			cache.push_front(page);
			TLB[page] = cache.begin();
			cout << "\tPage" << page <<" added to cache" << endl;
		}else{	
			cache.push_front(page);
			TLB[page] = cache.begin(); //Updating TLB entry for the page
			cout << "\tPage" << page <<" added to cache" << endl;
		}

	}else{
		cache.remove(page);
		cache.push_front(page);
		TLB[page] = cache.begin();
		cout << "Cache Hit, timeline updated\n";
	}
	cout << endl << endl;

}


int main(){
	cout << "Size of the cache: ";
	cin >> cacheSize;
	
	access(1);
	access(2);
	access(3);
	access(1);
	access(4);
	access(5);
	access(5);
	access(1);
	access(6);
	access(4);

	return 0;
}