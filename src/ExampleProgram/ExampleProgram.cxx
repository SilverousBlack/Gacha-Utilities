#include <iostream>
#include "../Gacha-Utilities/GachaCore.hxx"
#include "../Gacha-Utilities/Gacha-Utilities.hxx"

using namespace gacha_utilities;

int main() {
	auto data = new int[5 * 4];
	for (int i = 0; i < 20; i++) {
		data[i] = i;
	}
	std::vector<char> some = { 2, 3, 4, 6, 0, 7, 8, 9, 21 };
	GachaPool<int> pool = { 2, 3, 4, 5, 0, 7, 8, 9, 21 };
	GachaPool<int> pool2 = { 2, 3, 4, 5, 0, 7, 8, 9, 22 };
	pool.append(some.rbegin(), some.rend());
	base_iterator<GachaPool<int>::InternalType> j = pool.begin();
	for (int i = 0; i < pool.size(); i++, j++) {
		std::cout << pool[i] << " | " << (*j) << std::endl;
	}
	system("pause");
	return 0;
}
