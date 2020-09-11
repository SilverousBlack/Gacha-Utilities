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
		std::cout << pool[i] << " | " << *j << std::endl;
		j++;
	}
	system("pause");
	return 0;
}
