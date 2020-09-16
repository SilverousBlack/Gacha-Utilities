#include <iostream>
#include "../Gacha-Utilities/GachaCore.hxx"
#include "../Gacha-Utilities/Gacha-Utilities.hxx"

using namespace gacha_utilities;

int main() {
	auto data = new int[5 * 4];
	data[0] = 1;
	GachaPool<int> pool({1, 2, 3, 4, 5});
	base_iterator<GachaPool<int>::InternalType> j(pool.begin());
	for (int i = 0; i < 5; i++) {
		std::cout << i << ": " << pool[i] << " | " << *j << std::endl;
		j++;
	}
	pool.resize(50, 6);
	std::cout << pool.size() << std::endl;
	j = pool.begin();
	for (int i = 0; i < pool.size(); i++) {
		std::cout << i << ": " << pool[i] << " | " << *j << std::endl;
		j++;
	}
	signed long long begin = 7;
	unsigned long long end = 9;
	pool.pop(begin, 9);
	std::cout << pool.size() << std::endl;
	j = pool.begin();
	for (int i = 0; i < pool.size(); i++) {
		std::cout << i << ": " << pool[i] << " | " << *j << std::endl;
		j++;
	}
	pool.resize(100);
	std::cout << pool.size() << std::endl;
	j = pool.begin();
	for (int i = 0; i < pool.size(); i++) {
		std::cout << i << ": " << pool[i] << " | " << *j << std::endl;
		j++;
	}
	system("pause");
	return 0;
}
