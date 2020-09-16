#include <iostream>
#include "../Gacha-Utilities/GachaCore.hxx"
#include "../Gacha-Utilities/Gacha-Utilities.hxx"

using namespace gacha_utilities;

int main() {
	auto data = new int[5 * 4];
	for (int i = 0; i < 20; i++) {
		data[i] = i;
	}
	GachaPool<int> pool(&data[0], &data[20]);
	auto pool2 = pool;
	base_iterator<GachaPool<int>::InternalType> j = pool.begin();
	for (int i = 0; i < pool.size(); i++, j++) {
		std::cout << pool[i] << " | " << (*j) << " | " << pool2[i] << std::endl;
	}
	system("pause");
	return 0;
}
