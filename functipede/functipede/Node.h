#pragma once

template <typename Arg> struct Port {
	typedef std::function<void(Arg)> type;
};

//template <typename ...Args> using Ports = std::tuple<Port<Args>...>;
template <typename ...Args> struct Ports {
	typedef std::tuple<typename Port<Args>::type...> type;
};

template <typename InPorts, typename OutPorts> using Node_guts = std::function<InPorts(OutPorts)>;

template <typename ...Ins> struct In {
	typedef typename Ports<Ins...>::type InPorts;
	template <typename ...Outs> struct Out {
		typedef typename Ports<Outs...>::type OutPorts;
		typedef typename Node_guts<InPorts, OutPorts> Node;
	};
};

// making sure this stuff actually compiles
using Ports_test = Ports<types<int, int>>;
using Ports_test2 = Ports<types<int>>;
using Node_guts_test = Node_guts<Ports_test, Ports_test>;
using Node_test = In<int, int>::Out<int, int>::Node;
using Node_test2 = In<int>::Out<int>::Node;