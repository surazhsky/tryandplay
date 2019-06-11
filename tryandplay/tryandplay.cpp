#include <iostream>
#include <typeinfo>
#include <utility>
#include <vector>

#include <algorithm>
#include <memory>
#include <string>

template<typename... Ts>
void ignore(Ts... ts) 
{
}

template <typename T>
double to_double(T t0)
{
	if (typeid(t0) == typeid(double) || typeid(t0) == typeid(float))
		return t0;
	return 1.0*((int)(t0));
}

template <typename T>
double sum(T t0)
{
	return to_double(t0);
}

template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type //return type
is_odd(T i) 
{ 
	std::cout << __FUNCSIG__ << std::endl;
	return bool(i % 2); 
}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
	class = typename std::enable_if<std::is_integral<T>::value>::type>
	bool is_even(T i) 
{
	std::cout << __FUNCSIG__ << std::endl;
	return !bool(i % 2);
}


template <typename T0, typename... Ts>
double sum(T0 t0, Ts... rest)
{
	return to_double(t0) + sum(rest...);
}

template <typename T>
T tentimes(T t)
{
	//std::cout << __FUNCDNAME__ << std::endl;
	//std::cout << __FUNCSIG__ << std::endl;
	return t * 10;
}

// Our base case just returns the value.
template <typename T>
double power_sum(T t) 
{ 
	return t; 
}

// Our new recursive case.
template <typename T, typename... Rest>
double power_sum(T t, Rest... rest) {
//	std::cout << __FUNCSIG__ << std::endl;
	return t + power_sum(tentimes(rest)...);
}

template<typename... Iterators>
std::tuple<Iterators...> increment_all(Iterators&... its) {
	return std::make_tuple((++its)...);
}


int global = 10;



int main()
{
	ignore(1.0, 5, true);
	ignore();

	double sum_up = sum(2.0, 1.0, 3.3, 20.2, 'a');
	std::cout << sum_up << std::endl;


	std::cout << to_double('s') << std::endl;

	std::cout << power_sum(2.0, 3.0, 5.0) << std::endl;

	//auto result = increment_all();
	std::cout << std::boolalpha;
	std::cout << is_odd(4) << std::endl;
	std::cout << is_even(4) << std::endl;

	/*
	std::cout << global << std::endl;
	auto foo = [=]() mutable { ++global; };
	foo();
	std::cout << global << std::endl;
	[] { ++global; } ();
	std::cout << global << std::endl;
	//[global] { ++global; } ();

	static int static_int = 10;
	std::cout << static_int << std::endl;
	auto foo = [=]() mutable { ++static_int; };
	foo();
	std::cout << static_int << std::endl;
	[] { ++static_int; } ();
	std::cout << static_int << std::endl;
	//[static_int] { ++static_int; } ();

	*/

	using namespace std::string_literals;
	std::vector<std::string> vs{"the perfect string"};
	std::find_if(vs.begin(), vs.end(), [](std::string const& s) {
		return s == "foo"s + "bar"s; });
	std::find_if(vs.begin(), vs.end(), [p = "foo"s + "bar"s](std::string const& s) { return s == p; });

	return 0;
}