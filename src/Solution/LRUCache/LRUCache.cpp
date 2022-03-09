#include "LRUCache.h"
#include <algorithm>

using namespace std;

LRUCache::LRUCache(int capacity)
{
	this->capacity=capacity;
	size=0;
	lru.resize(capacity);
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	vector<int>::iterator i;
	for(i=requestsNo.begin();i<requestsNo.end();i++)
	{
		vector<int>::iterator k;
		for(k=lru.begin();k!=lru.end();k++)
			if(i==k)
				lru.erase(i);
		for(int j=lru.capacity();j!=0;j--)
			lru[j]=lru[j-1];
		lru[0]=*i;
	}
	return lru;
}

int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	return lru.capacity();
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity=capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	lru=aux;
}
