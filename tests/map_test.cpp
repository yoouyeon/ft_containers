#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "../includes/map.hpp"

// void test_end(void) {
// 	// SECTION - end, rend에 관하여
// 	std::map<int, bool> std_map;
// 	// 값 하나를 넣고 end, rend를 저장
// 	std_map.insert(std::make_pair(1, true));
// 	auto end1 = std_map.end();
// 	auto rend1 = std_map.rend();
// 	// key가 1보다 큰 값들을 넣고 새로운 end, rend를 저장
// 	std_map.insert(std::make_pair(2, true));
// 	std_map.insert(std::make_pair(3, true));
// 	std_map.insert(std::make_pair(4, true));
// 	auto end2 = std_map.end();
// 	auto rend2 = std_map.rend();
// 	// 변했는지 비교해보기
// 	std::cout << "===== map ======\n";
// 	std::cout << "end1 과 end2는 동일합니다 : " << std::boolalpha << (end1 == end2) << "\n";
// 	std::cout << "rend1 과 rend2는 동일합니다 : " << std::boolalpha << (rend1 == rend2) << "\n";
// 	// 벡터 결과도 확인해보기
// 	std::vector<int> std_vector;
// 	auto vend1 = std_vector.end();
// 	auto vrend1 = std_vector.rend();
// 	std_vector.push_back(1);
// 	std_vector.push_back(2);
// 	auto vend2 = std_vector.end();
// 	auto vrend2 = std_vector.rend();
// 	std::cout << "==== vector ====\n";
// 	std::cout << "end1 과 end2는 동일합니다 : " << std::boolalpha << (vend1 == vend2) << "\n";
// 	std::cout << "rend1 과 rend2는 동일합니다 : " << std::boolalpha << (vrend1 == vrend2) << "\n";
// 	/* 출력 (이왜진)
// 	 * ===== map ======
// 	 * end1 과 end2는 동일합니다 : true
// 	 * rend1 과 rend2는 동일합니다 : true
// 	 * ==== vector ====
// 	 * end1 과 end2는 동일합니다 : false
// 	 * rend1 과 rend2는 동일합니다 : false
// 	*/
// 	// !SECTION
// }

// void test_erase(){
// 	std::map<int, std::string> test_map;
// 	test_map.insert(std::make_pair(3, "삭제하려는 것"));
// 	test_map.insert(std::make_pair(5, "남아야 하는 것"));
// 	auto target = test_map.begin();
// 	std::cout << "==== map status (1) ====\n";
// 	for(auto iter = test_map.begin(); iter != test_map.end(); iter++) {
// 		std::cout << (*iter).first << " - " << (*iter).second << "\n";
// 	}
// 	std::cout << "========== end =========\n";
// 	std::cout << "! target : " << (*target).first << " - " << (*target).second << "\n";
// 	// begin을 바꿔줌.
// 	test_map.insert(std::make_pair(2, "남아야 하는 것"));
// 	test_map.insert(std::make_pair(1, "남아야 하는 것"));
// 	test_map.insert(std::make_pair(4, "남아야 하는 것"));
// 	std::cout << "==== map status (2) ====\n";
// 	for(auto iter = test_map.begin(); iter != test_map.end(); iter++) {
// 		std::cout << (*iter).first << " - " << (*iter).second << "\n";
// 	}
// 	std::cout << "========== end =========\n";
// 	// 삭제함
// 	test_map.erase(target);
// 	std::cout << "==== map status (3) ====\n";
// 	for(auto iter = test_map.begin(); iter != test_map.end(); iter++) {
// 		std::cout << (*iter).first << " - " << (*iter).second << "\n";
// 	}
// 	std::cout << "========== end =========\n";
// }

// void test_insert() {
// 	std::map<int, char> test_map;
// 	test_map.insert(std::make_pair(1, 'a'));
// 	std::cout << "key : 1 , value : " << test_map.at(1) << std::endl;
// 	// 중복된 키를 다른 값으로 넣어봄
// 	test_map.insert(std::make_pair(1, 'b'));
// 	std::cout << "key : 1 , value : " << test_map.at(1) << std::endl;
// 	/** 출력
// 	 * key : 1 , value : a
// 	 * key : 1 , value : a
// 	 */
// }

void test_iterator() {
	ft::map<int, int> mm;
	// ft::map<int, int> mm2;
	mm[1] = 1;
	mm[2] = 2;
	mm[3] = 3;
	ft::map<int, int>::iterator iter = mm.begin();
	iter--;
	std::cout << "==== " << iter->first << std::endl;
	std::cout << "====\n";
}

int main(void) {
	// test_end();
	// test_erase();
	// test_insert();
	// test_iterator();
	ft::map<int, int, std::greater<int> > mm;
	mm[1] = 1;
	mm[2] = 2;
	mm[3] = 3;
	// system("leaks container");
	return (0);
}