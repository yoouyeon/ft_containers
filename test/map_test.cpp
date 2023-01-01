#include <iostream>
#include <map>
#include <vector>

int main(void) {
	// SECTION - end, rend에 관하여
	std::map<int, bool> std_map;
	// 값 하나를 넣고 end, rend를 저장
	std_map.insert(std::make_pair(1, true));
	auto end1 = std_map.end();
	auto rend1 = std_map.rend();
	// key가 1보다 큰 값들을 넣고 새로운 end, rend를 저장
	std_map.insert(std::make_pair(2, true));
	std_map.insert(std::make_pair(3, true));
	std_map.insert(std::make_pair(4, true));
	auto end2 = std_map.end();
	auto rend2 = std_map.rend();
	// 변했는지 비교해보기
	std::cout << "===== map ======\n";
	std::cout << "end1 과 end2는 동일합니다 : " << std::boolalpha << (end1 == end2) << "\n";
	std::cout << "rend1 과 rend2는 동일합니다 : " << std::boolalpha << (rend1 == rend2) << "\n";
	// 벡터 결과도 확인해보기
	std::vector<int> std_vector;
	auto vend1 = std_vector.end();
	auto vrend1 = std_vector.rend();
	std_vector.push_back(1);
	std_vector.push_back(2);
	auto vend2 = std_vector.end();
	auto vrend2 = std_vector.rend();
	std::cout << "==== vector ====\n";
	std::cout << "end1 과 end2는 동일합니다 : " << std::boolalpha << (vend1 == vend2) << "\n";
	std::cout << "rend1 과 rend2는 동일합니다 : " << std::boolalpha << (vrend1 == vrend2) << "\n";
	/* 출력 (이왜진)
	 * ===== map ======
	 * end1 과 end2는 동일합니다 : true
	 * rend1 과 rend2는 동일합니다 : true
	 * ==== vector ====
	 * end1 과 end2는 동일합니다 : false
	 * rend1 과 rend2는 동일합니다 : false
	*/
	/**
	 * NOTE
	 * vector의 end는 
	 * 
	 */
	// !SECTION

	return (0);
}