#pragma once

template <typename Arg> struct Port
{
	typedef std::function<void(Arg)> type;
};

template <typename ...Args> struct Ports
{
	typedef std::tuple<typename Port<Args>::type...> type;
};

template <typename Ins, typename Outs> struct Node;
template <typename ...Ins, typename ...Outs> struct Node<types<Ins...>, types<Outs...>>
{
	typedef typename Ports<Ins...>::type InPorts;
	typedef typename Ports<Outs...>::type OutPorts;
	typedef typename std::function<InPorts(OutPorts)> func;
};
//template <typename ...Ins> struct In
//{
//	typedef typename Ports<Ins...>::type InPorts;
//	template <typename ...Outs> struct Out
//	{
//		typedef typename Ports<Outs...>::type OutPorts;
//		typedef typename std::function<InPorts(OutPorts)> Node;
//	};
//};

template <typename Arg, typename Ret>
Node<types<Arg>, types<Ret>> wrap(std::function<Ret(Arg)> func);

template <typename Arg, typename Ret, typename NodeT = Node<types<Arg>, types<Ret>>>
inline NodeT wrap(std::function<Ret(Arg)> func)
{
	return[func](NodeT::OutPorts outs)
	{
		// return the InPorts
		return[func, outs](Arg arg)
		{
			// call func with arg and pipe the result through outs
			outs(func(arg));
		};
	};
}

// making sure this stuff actually compiles
using Ports_test = Ports<types<int, int>>;
using Ports_test2 = Ports<types<int>>;
using Node_test = Node<types<int>, types<long>>;
