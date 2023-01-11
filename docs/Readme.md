# ft_containers

## 🌟 index

## 🌟 STL Containers

자주 사용하는 자료구조들을 템플릿 클래스로 만들어서 객체들을 그 자료구조에 접근하고, 저장할 수 있게 해 준다.

종류가 좀 더 있지만, 우리 과제에서 구현해야 할 컨테이너 종류는 3가지이다.

- 순차 컨테이너 : 배열처럼 저장해서 순차적으로 접근할 수 있는 컨테이너 (vector)
- 연관 컨테이너 : 인덱스가 아닌 Key로 접근하는 컨테이너. 내부적으로 정렬을 한다. (map, set)
- 컨테이너 어댑터 : 순차 컨테이너를 기능을 제한하는 식으로 다른 방법으로 사용할 수 있게 하는 컨테이너 (vector를 사용하는 stack)

## 🌟 특성 정보 (traits) 클래스

템플릿은 컴파일 타임에 인스턴스화되기 때문에, 템플릿 클래스를 활용하는 함수를 만들 때 이 템플릿 클래스에 대한 정보를 알아내기 위해서 특성 정보 클래스를 사용한다.

### ✨ iterator_traits

#### ⭐️ iterator 종류

총 종류는 5개인데 여기서 구현하게 되는 이터레이터는 2종류이다.

- Bidirectional iterator : 한 칸씩 전진, 후진만 가능. 증감연산만 가능하다는 뜻이다.
- Random access iterator : 임의의 위치만큼 전진, 후진할 수 있다.

이런 iterator의 종류를 `iterator_tag` 들로 구분하고, 이 `itarator_tag` 들은 서로 상속 구조를 같은 빈 구조체이이다.

이렇게 iterator의 종류를 구분하는 것이 중요한 이유를 두 이터레이터 사이의 거리를 구하는 `algorithm` 헤더의 `distance` 함수를 예로 들어서 설명해보면, 임의의 숫자를 더하거나 빼는 연산이 가능한 Random access iterator의 경우에는 `end - start` 를 계산하여 구하는 반면에, Bidirectional iterator의 경우에는 `start == end` 가 될 때까지 길이와 iterator를 하나씩 증가시키는 방식으로 거리를 구한다.

빼기 연산이 가능한데 1씩 증기시키는 방법으로 거리를 구하는 것은 비효율적이기 때문에 `iterator_tag`를 확인해서 가장 효율적인 방법으로 거리를 구할 수 있게 되는 것이다.

#### ⭐️ iterator traits 클래스

iterator를 활용하는 알고리즘 함수들은 반복자만 인자로 받기 때문에 반복자가 탐색하고 있는 컨테이너에 대한 정보는 전혀 알지 못한다.

위에서 든 예시처럼, 반복자의 특성을 알면 좀 더 효율적으로 동작하는 경우가 있기 때문에, 반복자의 특성을 아는 방법을 알아보니 반복자 자체로는 그 특성을 알 수 있는 방법이 없다.

따라서 `iterator_traits` 라는 템플릿 클래스를 만들고, 그 안에 유용한 타입들을 정의해서 사용할 수 있게 해 줬다.

➡️ `iterator_traits` 클래스의 역할 : 반복자 타입을 템플릿 인수로 전달하면, 그 반복자가 내부에서 정의하고 있는 타입들을 약속된 이름으로 재정의한다.

![](https://user-images.githubusercontent.com/57761286/211635624-ac1099b0-ae0d-4a6b-8061-daa45d4a445e.png)

- `iterator_category` : 반복자의 종류 지정 (`std::bidirectional_iterator_tag`, `std::random_access_iterator_tag` 등)
- `value_type` : 반복자가 가리키는 대상의 타입
- `difference_type` : 반복자까지의 거리를 표현하는 타입

컨테이너들에 대한 이터레이터에서 `iterator_traits`를 사용하기 위해서 컨테이너에 대한 이터레이터를 구현할 때 `iterator_traits`에서 요구하는 타입들 (`difference_type`, `pointer` 같은 것들) 을 재정의 해 두어야 한다.

이렇게 재정의한 타입들은 `iterator_traits`를 통해서 일관된 이름으로 활용할 수 있게 된다.

#### ⭐️ 참고

- [특성 정보 클래스](http://egloos.zum.com/sweeper/v/3007176)
- [iterator_iterator](http://soen.kr/lecture/ccpp/cpp4/39-2-6.htm)
- [cppreference - iterator_traits](https://en.cppreference.com/w/cpp/iterator/iterator_traits)
