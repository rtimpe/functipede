// functipede.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tbb\flow_graph.h"
#include "Node.h"


int _tmain(int argc, _TCHAR* argv[])
{
	auto lambda = [](int a){return a; };
	auto node = wrap(lambda);
	return 0;
}

