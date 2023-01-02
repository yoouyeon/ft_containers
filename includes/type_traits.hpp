#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP
/*
	- enable_if
	- is_integral
*/

/*
	NOTE - 
	https://en.cppreference.com/w/cpp/language/types#char16_t
*/

namespace ft
{
	//SECTION - enable_if
	template< bool B, class T = void >
	struct enable_if { };

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	//SECTION - is_integral
	template <class T, T v>
	struct integral_constant {
		typedef T value_type;
		typedef integral_constant<T,v> type;
		
		static const value_type value = v;
		operator T() const {return value;}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<class T> struct remove_cv                   {typedef T type;};
	template<class T> struct remove_cv<const T>          {typedef T type;};
	template<class T> struct remove_cv<volatile T>       {typedef T type;};
	template<class T> struct remove_cv<const volatile T> {typedef T type;};

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

	template<typename T> struct is_integral: is_integral_base<typename std::remove_cv<T>::type> {};
}

#endif
