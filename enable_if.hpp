#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
	template<bool _B, class _T = void>
	struct enable_if
	{};

	template<class _T>
	struct enable_if<true, _T>
	{
		typedef _T type;
	};
}

#endif /* ENABLE_IF_HPP */
