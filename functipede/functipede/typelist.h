#pragma once

template<typename... Ts> struct types {
	template<typename T> using prepend = types<T, Ts...>;
};

template<int n, typename... Ts> struct nth_impl;
template<typename T, typename... Ts> struct nth_impl<0, T, Ts...> {
	using type = T;
};
template<int n, typename T, typename... Ts> struct nth_impl<n, T, Ts...> {
	using type = typename nth_impl<n - 1, Ts...>::type;
};
template<int n, typename... Ts> using nth = typename nth_impl<n, Ts...>::type;