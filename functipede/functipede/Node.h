#pragma once

template <typename In, typename Out> struct Node_impl;
template <typename ...Ins, typename ...Outs>
struct Node_impl<types<Ins...>, types<Outs...>> {
	using value = std::function<std::tuple<std::function<void(Ins)>...>()>;
};

using TestNode = Node_impl<types<int, int>, types<int, int>>;