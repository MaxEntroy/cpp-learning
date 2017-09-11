/*************************************************************************
	> File Name: LRUCache.h
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年09月03日 星期日 15时25分37秒
 ************************************************************************/
#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <utility>
#include <unordered_map>
#include <list>

template<class KeyType, class ValueType>
class LRUCache {
public:
	LRUCache(int capacity) : cap_(capacity) {}
	bool get(KeyType key, ValueType& value);
	void put(KeyType key, ValueType value);
private:
	typedef std::pair<int, int> Node;
	typedef typename std::list<Node>::iterator Iter;
	
	std::list<Node> cache_list_;
	std::unordered_map<KeyType, Iter> cache_map_;
	int cap_;
};

template<class KeyType, class ValueType>
bool LRUCache<KeyType, ValueType>::get(KeyType key, ValueType& value){
	if( cache_map_.find(key) == cache_map_.end() ) return false;
	else{
		Iter it = cache_map_[key];

		// get the value
		value = cache_map_[key]->second;
		
		// move to head
		cache_list_.splice(cache_list_.begin(), cache_list_, it);
		
		return true;
	}
}

template<class KeyType, class ValueType>
void LRUCache<KeyType, ValueType>::put(KeyType key, ValueType value){
	if( cache_map_.find(key) != cache_map_.end() ){
		Iter it = cache_map_[key];
		
		// update the value
		it->second = value;

		// move to head
		cache_list_.splice(cache_list_.begin(), cache_list_, it);
	}
	else{
		Node node(key, value);
		
		if( cache_list_.size() == cap_ ){
			cache_map_.erase(cache_list_.back().first);
			cache_list_.pop_back();
		}

		cache_list_.push_front(node);
		cache_map_[key] = cache_list_.begin();
	}
}

#endif
