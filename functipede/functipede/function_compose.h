#pragma once

#include "function_eval.h"
#include "function_traits.h"

template <class F, class G>
auto compose(F&& f, G&& g) -> std::function<typename function_traits<F>::return_type(
typename function_traits<G>::template argument<0>::type)>
{
	using F_traits = typename function_traits<F>;
	using G_traits = typename function_traits<G>;

	static_assert(F_traits::arity == 1, "error: only unary functions can be composed.");
	static_assert(G_traits::arity == 1, "error: only unary functions can be composed.");

	using Arg = typename G_traits::template argument<0>::type;

	return [=](Arg arg){return eval(f, eval(g, arg)); };
}