#pragma once

template <typename Arg> using Port = std::function<void(Arg)>;

template <typename ArgList> struct Ports;
template <typename ...Args> struct Ports<types<Args...>> : public std::tuple<Port<Args>...> {};

template <typename InPorts, typename OutPorts>
using Node_guts = std::function<InPorts(OutPorts)>;

template <typename InList, typename OutList> using Node = Node_guts<Ports<InList>, Ports<OutList>>;

// making sure this stuff actually compiles
using Ports_test = Ports<types<int, int>>;
using Ports_test2 = Ports<types<int>>;
using Node_guts_test = Node_guts<Ports_test, Ports_test>;
using Node_test = Node<types<int, int>, types<int, int>>;