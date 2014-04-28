// functipede.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tbb\flow_graph.h"
#include "Node.h"

static float free_function(const std::string& a, int b)
{
	return (float)a.size() / b;
}

static void testFunctionTraits()
{
	using Traits = function_traits<decltype(free_function)>;

	static_assert(Traits::arity == 2, "");
	static_assert(std::is_same<Traits::return_type, float>::value, "");
	static_assert(std::is_same<Traits::argument<0>::type, const std::string&>::value, "");
	static_assert(std::is_same<Traits::argument<1>::type, int>::value, "");
	static_assert(
		std::is_same<
			Traits::arguments<std::tuple>,
			std::tuple<const std::string&, int>
		>::value,
		"");

	auto node = wrap(free_function);
}

int _tmain(int argc, _TCHAR* argv[])
{
	testFunctionTraits();
	return 0;
}
