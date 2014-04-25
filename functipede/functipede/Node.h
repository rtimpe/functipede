#pragma once

template <typename Inner, typename Outer> class composed
{
public:
	explicit composed(Inner inner = Inner(), Outer outer = Outer()) :
		_inner(inner),
		_outer(outer) {}

	template <typename T>
	auto operator()(T x) -> decltype(Outer()(Inner()(x)))
	{
		return _outer(_inner(x));
	}

private:
	Inner _inner;
	Outer _outer;
};

template <typename Function1, typename Function2>
composed<Function1, Function2> compose(Function1 f1, Function2 f2)
{
	return composed<Function1, Function2>(f1, f2);
}