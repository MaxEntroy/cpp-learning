#include "LRUCache.h"
#include <iostream>

int main( void ){
	LRUCache<int, int> obj(2);
	int val = 0;
	bool ret;

	obj.put(1, 1);
	obj.put(2, 2);

	ret = obj.get(1, val); // 1
	if(ret) std::cout << val << std::endl;
	else std::cout << -1 << std::endl;
	
	obj.put(3, 3);
	
	ret = obj.get(2, val); // -1
	if(ret) std::cout << val << std::endl;
	else std::cout << -1 << std::endl;
	obj.put(4, 4);
	ret = obj.get(1, val); // 1
	if(ret) std::cout << val << std::endl;
	else std::cout << -1 << std::endl;
	
	ret = obj.get(3, val);
	if(ret) std::cout << val << std::endl;
	else std::cout << -1 << std::endl;
	ret = obj.get(4, val);
	if(ret) std::cout << val << std::endl;
	else std::cout << -1 << std::endl;

	return 0;
}


