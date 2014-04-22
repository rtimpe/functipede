// functipede.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tbb\flow_graph.h"
#include "Node.h"


int _tmain(int argc, _TCHAR* argv[])
{
	auto node = wrap<int, int>([](int a){ return a; });
	auto outport = [](int a){ std::cout << a << std::endl; };
	auto inports = node(std::make_tuple(outport));
	std::get<0>(inports)(1);
	return 0;
}

