#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {
    // remove_const

    template <class _Tp> struct remove_const            {typedef _Tp type;};
    template <class _Tp> struct remove_const<const _Tp> {typedef _Tp type;};

    // remove_volatile

    template <class _Tp> struct remove_volatile               {typedef _Tp type;};
    template <class _Tp> struct remove_volatile<volatile _Tp> {typedef _Tp type;};

    // remove_cv

    template <class _Tp> struct remove_cv
    {typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;};

    template <class _Tp, _Tp __v>
    struct integral_constant
    {
        static const _Tp          value = __v;
        typedef _Tp               value_type;
        typedef integral_constant type;
        operator value_type() const {return value;}
    };

    #define _LIBCPP_BOOL_CONSTANT(__b) integral_constant<bool,(__b)>
    typedef _LIBCPP_BOOL_CONSTANT(true)  true_type;
    typedef _LIBCPP_BOOL_CONSTANT(false) false_type;

    // is_integral

    template <class _Tp> struct __libcpp_is_integral                     : public false_type {};
    template <>          struct __libcpp_is_integral<bool>               : public true_type {};
    template <>          struct __libcpp_is_integral<char>               : public true_type {};
    template <>          struct __libcpp_is_integral<signed char>        : public true_type {};
    template <>          struct __libcpp_is_integral<unsigned char>      : public true_type {};
    template <>          struct __libcpp_is_integral<wchar_t>            : public true_type {};
    template <>          struct __libcpp_is_integral<short>              : public true_type {};
    template <>          struct __libcpp_is_integral<unsigned short>     : public true_type {};
    template <>          struct __libcpp_is_integral<int>                : public true_type {};
    template <>          struct __libcpp_is_integral<unsigned int>       : public true_type {};
    template <>          struct __libcpp_is_integral<long>               : public true_type {};
    template <>          struct __libcpp_is_integral<unsigned long>      : public true_type {};

    template <class _Tp> struct is_integral
        : public __libcpp_is_integral<typename remove_cv<_Tp>::type> {};
}

#endif /* IS_INTEGRAL_HPP */
