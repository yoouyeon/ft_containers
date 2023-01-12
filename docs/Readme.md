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

### ✨ type_traits

#### ⭐️ remove_cv

`const`, `volatile` 한정자를 제거해준다.

- `const` : 
- `volatile` : 이렇게 선언된 변수에 대해서는 최적화를 진행하지 않는다. (레지스터에 값이 있는지를 확인하지 않고 매번 메모리를 참조한다.)

```cpp
template<class T> struct remove_cv                   {typedef T type;};
template<class T> struct remove_cv<const T>          {typedef T type;};
template<class T> struct remove_cv<volatile T>       {typedef T type;};
template<class T> struct remove_cv<const volatile T> {typedef T type;};
```

2, 3, 4 라인처럼 템플릿에 const, volatile 한정자가 붙은 타입이 들어왔을 때에도 한정자를 뗀 T 타입을 type으로 정의해주었다.

```cpp
is_integral_base<typename std::remove_cv<T>::type>
```

그래서 이렇게 `remove_<cv>`의 템플릿으로 전달한 다음에 type을 참조하게 되면 한정자가 모두 제거된 T를 참조할 수 있게 된다.

#### ⭐️ integral_constant

T 타입의 value 멤버의 값을 v 로 설정한다.

```cpp
template <class T, T v>
struct integral_constant {
	typedef T value_type;
	typedef integral_constant<T,v> type;
	
  static const value_type value = v;
};
```

이런 식으로 활용 가능

```cpp
typedef integral_constant<bool, true> true_type;
true_type::value // <- true
typedef integral_constant<bool, false> false_type;
false_type::value // <- false
```

#### ⭐️ is_integral

T가 정수 계열인지 확인한다.

`is_integral_base` 구조체를 상속받는 빈 구조체

```cpp
template<typename T> struct is_integral: is_integral_base<typename std::remove_cv<T>::type> {};
```

`is_integral_base` 구조체 : 기본적으로는 false_type 구조체를 상속받아 value 값으로 false를 갖지만, 일부 타입에 대해서는 true를 상속받는 구조체로 오버로딩 된다.

```cpp
// 기본적으로는 false_type을 상속받아 val
template<typename> struct is_integral_base: public false_type {};

template<> struct is_integral_base<bool>: public true_type {};
template<> struct is_integral_base<signed char>: public true_type {};
template<> struct is_integral_base<unsigned char>: public true_type {};
template<> struct is_integral_base<wchar_t>: public true_type {};
template<> struct is_integral_base<short int>: public true_type {};
template<> struct is_integral_base<unsigned short int>: public true_type {};
template<> struct is_integral_base<int>: public true_type {};
template<> struct is_integral_base<unsigned int>: public true_type {};
template<> struct is_integral_base<long int>: public true_type {};
```

type 값을 확인해서 T가 정수 계열인지를 확인할 수 있다.

#### ⭐️ enable_if

SFINAE : Substitution Failure Is Not A Error

컴파일시에 타입에 맞는 함수를 찾아가는 과정에 함수의 인자를 치환하는 작업을 하게 되는데, 타입이 맞지 않거나 타입에 맞는 표현이 아니라면 치환이 실패한다.

보통의 경우에는 치환이 실패할 경우에는 컴파일 에러를 띄우고 실행을 중단하는데, SFINAE를 활용하게 되면 치환 실패했을 경우에 컴파일 에러를 띄우지 않고 오버로딩 후보군에서 제외시키는 방식으로 동작한다.

일반적인 경우에는 빈 `enable_if` 로 오버로딩되다가, 첫번째 인자가 true일 경우에는 두번째 `enable_if`로 오버로딩되어 `type`이 정의되게 된다.

`type` 타입이 있는지를 확인하는 방법을 사용하면 된다.

```cpp
template< bool B, class T = void >
struct enable_if { };

template<class T>
struct enable_if<true, T> { typedef T type; };
```

이터레이터는 주소값을 가지기 때문에 컴파일 단계에서는 아래 두 생성자를 구분하기가 어렵다. 따라서 enable_if로 컴파일 에러를 발생시켜 후보군에서 제외시키는 방법을 사용한다.

```cpp
std::vector<int> v1(42, 4242);
std::vector<int> v2(v.begin(), v.end());
```



```cpp
template<class InputIt>
vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type* = 0)
```





#### ⭐️ 참고

- [SFINAE 와 enable_if](https://modoocode.com/255)

- [enable_if](http://egloos.zum.com/sweeper/v/3059985)

## 🌟 red-black tree

### ✨ Modifiers

```cpp
// bool의 의미 - true : 없는 key를 추가함 false : 존재하던 key의 값을 업데이트함.
// case 1) 트리가 빈 경우 : 루트로 설정해준다.
// case 2) 그 외 : _insert_node(const value_type& value) 함수 호출
ft::pair<iterator, bool> insert( const value_type& value );

// 여기서 말하는 pos는 insert할 정확한 위치가 아닌, 최대한 그 지점과 비슷한 곳에 삽입하라는 뜻이다.
// 최적화된 삽입을 위한 함수이고 트리는 정렬되기 때문에 pos가 뭐든 들어야가 하는 곳은 정확하다.
// 내 컨테이너에서는 아직까지는 느린 점을 찾지 못해서 pos가 주어지는 insert도 위의 value 만 받는 함수와 완전히 동일하게 동작한다.
iterator insert( iterator pos, const value_type& value )
```

