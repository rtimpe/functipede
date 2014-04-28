#pragma once

// borrowed from functionalcpp.wordpress.com

// functions, functors, lambdas, etc.
template<
	class F, class... Args,
	class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type,
	class = typename std::enable_if<!std::is_member_object_pointer<F>::value>::type
>
auto eval(F&& f, Args&&... args) -> decltype(f(std::forward<Args>(args)...))
	{
	return f(std::forward<Args>(args)...);
}

// const member function
template<class R, class C, class... Args>
auto eval(R(C::*f)() const, const C& c, Args&&... args) -> R
{
	return (c.*f)(std::forward<Args>(args)...);
}

template<class R, class C, class... Args>
auto eval(R(C::*f)() const, C& c, Args&&... args) -> R
{
	return (c.*f)(std::forward<Args>(args)...);
}

// non-const member function
template<class R, class C, class... Args>
auto eval(R(C::*f)(), C& c, Args&&... args) -> R
{
	return (c.*f)(std::forward<Args>(args)...);
}

// member object
template<class R, class C>
auto eval(R(C::*m), const C& c) -> const R&
{
	return c.*m;
}

template<class R, class C>
auto eval(R(C::*m), C& c) -> R&
{
	return c.*m;
}