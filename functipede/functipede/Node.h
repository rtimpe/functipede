#pragma once

// A Node is a function that accepts a tuple of output port bindings as input and returns a tuple of input ports.

// Here we will take a a normal function and wrap it into a Node

template <typename ...Arg> struct Port
{
	typedef std::function<void(Arg...)> type;
};

template <typename ...Args> struct Ports
{
	typedef std::tuple<typename Port<Args>::type...> type;
};

template <class Func, class InPorts, class OutPorts>
struct wrapHelper
{
	template <class ...Args>
	struct wrapWrapper {
		static auto wrap(Func&& func)->std::function<InPorts(OutPorts)>
		{
			return[func](OutPorts outs)
			{
				// return the InPorts
				return std::make_tuple([func, outs](Args args...)
				{
					// call func with arg and pipe the result through outs
					std::get<0>(outs)(func(std::forward(args...)));
				});
			};
		}
	};
};

template <class Func,
	class InPorts = std::tuple<function_traits<Func>::arguments<Port>>,
	class OutPorts = std::tuple<Port<function_traits<Func>::return_type>>>
auto wrap(Func&& func)->std::function<InPorts(OutPorts)>
{
	return function_traits<Func>::arguments<wrapHelper<Func, InPorts, OutPorts>::wrapWrapper>::wrap(func);
}
