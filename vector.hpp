#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <exception>
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"

namespace ft {
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef T*										pointer;
		typedef const T* 								const_pointer;
		typedef vector_iterator<pointer>				iterator;
		typedef vector_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;

	private :
		// 先頭の要素へのポインター
		pointer         __begin;
		// 最後の要素の1つ前方のポインター
		pointer         __end;
		// 確保したストレージの終端
		pointer         __end_cap;
		// アロケーターの値
		allocator_type  __alloc;

	public:
		// constructor
		explicit vector(const allocator_type& __alloc = allocator_type())
			: __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__alloc)
		{}
		explicit vector(size_type __n, const value_type& __val = value_type(),
				 const allocator_type& __alloc = allocator_type())
			: __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__alloc)
		{
			if (__n > 0)
			{
				__vallocate(__n);
				std::uninitialized_fill(__begin, __begin + __n, __val);
                __end = __begin + __n;
			}

			// resize(__n, __val);

			// if (__n > 0)
			// {
			// 	allocate(__n);
			// 	for (size_type __i = 0; __i < __n; ++__i)
			// 		alloc.construct(&first[__i], __val);
			// }
		}
		template <class InputIterator>
		vector(InputIterator __first, InputIterator __last, const allocator_type & __alloc = allocator_type(),
				typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__alloc)
		{
			size_type __n = static_cast<size_type>(std::distance(__first, __last));
			if (__n > 0)
			{
				__vallocate(__n);
				std::uninitialized_copy(__first, __last, __begin);
                __end = __begin + __n;
			}

			// reserve(std::distance(__first, __last));
			// for (InputIterator __i = __first; __i != __last; ++__i)
			// 	push_back(*__i);
		}
		vector(const vector& __x)
			: __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__x.__alloc)
		{
			size_type __n = __x.size();
			if (__n > 0)
			{
				__vallocate(__n);
				std::uninitialized_copy(__x.begin(), __x.end(), __begin);
                __end = __begin + __n;
			}

			// // llvm
			// // size_type __n = __x.size();
			// // if (__n > 0)
			// // {
			// // 	__vallocate(__n);
			// // 	__construct_at_end(__x.__begin_, __x.__end_, __n);
			// // }

			// if (!__x.first)
			// 	return;

			// reserve(__x.size());
			// // コメント
			// // pointer dest = first;
			// // iterator src = r.begin();
			// // for (; src != r.end(); ++src, ++dest)
			// // {
			// // 	std::cout << typeid(src).name() << std::endl;
			// // 	alloc.construct(dest, *src);
			// // }
			// // last = first + r.size();
			// for (size_type i = 0; i < __x.size(); i++)
			// 	alloc.construct(&first[i], __x.first[i]);
			// last = first + __x.size();
		}
		// destructor
		~vector()
		{
            if (__begin != NULL)
            {
                __clear();
			    __deallocate();
            }
		}

		// コピー代入演算子ではアロケーターのコピーをする必要はない。
		// 自分自身への代入への対応が必要だ。
		// コピー代入のコピー先とコピー元の要素数が同じであるとは限らない。
        // TODO: assginを実装してから考える
		vector& operator=(const vector& r)
		{
			// 1. 自分自身への代入なら何もしない
			if ( this == &r )
				return *this ;

			// 2. 要素数が同じならば
			if ( size() == r.size() )
			{	// 要素ごとにコピー代入
				std::copy( r.begin(), r.end(), begin() ) ;
			}
			// 3. それ以外の場合で
			else
			{
				// 予約数が十分ならば、
				if ( capacity() >= r.size() )
				{
					// 有効な要素はコピー
					std::copy( r.begin(), r.begin() + r.size(), begin() ) ;
					// 残りはコピー構築
					for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end();
							src_iter != src_end ; ++src_iter, ++__end )
					{
						__alloc.construct(__begin, *src_iter ) ;
					}
				}
				// 4. 予約数が不十分ならば
				else
				{
					// 要素をすべて破棄
					destroy_all() ;
					// 予約
					reserve( r.size() ) ;
					// コピー構築
					// iterator src_iter = r.begin(), src_end = r.end(), dest_iter = begin();
					// for (; src_iter != src_end ; ++src_iter, ++dest_iter, ++last )
					// {
					// 	alloc.construct( dest_iter, *src_iter ) ;
					// }
					for (size_type i = 0; i < r.size(); ++i, ++__end)
					{
						__alloc.construct(&__begin[i], r.__begin[i]);
					}
				}
			}
			return *this ;
		}

        // Iterators
        iterator begin()
        {
            return __make_iter(__begin);
        }
        const_iterator begin() const
        {
            return __make_iter(__begin);
        }
        iterator end()
        {
            return __make_iter(__end);
        }
        const_iterator end() const
        {
            return __make_iter(__end);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        // Capacity
        size_type size() const
        {
            return end() - begin() ;
        }
        size_type max_size() const
        {
            return std::min(__alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }
        /*
        vector<_Tp, _Allocator>::resize(size_type __sz, const_reference __x)
        {
            size_type __cs = size();
            if (__cs < __sz)
                this->__append(__sz - __cs, __x);
            else if (__cs > __sz)
                this->__destruct_at_end(this->__begin_ + __sz);
        }
        */
        void resize(size_type __n, value_type __val = value_type())
        {
            size_type __cs = size();
            if (__cs > __n)
            {
                size_type __diff = __cs - __n;
                destroy_until(rbegin() + __diff);
                __end = __begin + __n;
            }
            else if (__cs < __n)
            {
                reserve(__n);
                for (; __end != __begin + __n; ++__end)
                {
                    __alloc.construct(__end, __val);
                }
            }
        }
        size_type capacity() const
        {
            return static_cast<size_type>(__end_cap - __begin);
        }
        bool empty() const
        {
            return __begin == __end;
        }
        /*
        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::reserve(size_type __n)
        {
            if (__n > capacity())
            {
                if (__n > max_size())
                    this->__throw_length_error();
                allocator_type& __a = this->__alloc();
                __split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
                __swap_out_circular_buffer(__v);
            }
        }
        */
        void reserve(size_type __sz)
        {
            if (__sz <= capacity())
                return ;

            pointer __old_begin = __begin;
            size_type __old_size = size();
            size_type __old_capa = capacity();

            __vallocate(__sz);

            for (size_type __i = 0; __i < __old_size; ++__i, ++__end)
                __alloc.construct(&__begin[__i], __old_begin[__i]);
            for (size_type __i = 0; __i < __old_size; ++__i)
                destroy(&__old_begin[__i]);
            __alloc.deallocate(__old_begin, __old_capa);
        }

        // Element access
        reference operator[](size_type __n)
        {
            return __begin[__n];
        }
        const_reference operator[](size_type __n) const
        {
            return __begin[__n];
        }
        reference at(size_type __n)
        {
            if (__n >= size())
                throw std::out_of_range("vector");
            return __begin[__n];
        }
        const_reference at(size_type __n) const
        {
            if (__n >= size())
                throw std::out_of_range("vector");
            return __begin[__n];
        }
        reference front()
        {
            return *__begin;
        }
        const_reference front() const
        {
            return *__begin;
        }
        reference back()
        {
            return *(__end - 1);
        }
        const_reference back() const
        {
            return *(__end - 1);
        }

        // Modifiers
        template <class InputIterator>
        typename ft::enable_if<!std::is_integral<InputIterator>::value, void>::type
        assign(InputIterator __first, InputIterator __last)
        {
            clear();
            for (; __first != __last; ++__first)
                push_back(*__first);
        }
        void assign(size_type __n, const value_type& __val)
        {
            if (__n <= capacity())
            {
                size_type __s = size();
                std::fill_n(__begin, std::min(__n, __s), __val);
                if (__n > __s)
                    std::uninitialized_fill_n(__begin + __s, __n - __s, __val);
                else
                    __base_destruct_at_end(__begin + __n);
            }
            else
            {
                __vdeallocate();
                __vallocate(__n);
                std::uninitialized_fill_n(__begin, __n, __val);
            }
            __end = __begin + __n;
        }
        void push_back(const value_type& val)
        {
            /*
            // 余裕がある
            if (this->__end_ != this->__end_cap())
            {
                __construct_one_at_end(__x);
            }
            else
                __push_back_slow_path(__x);
            */
            // 予約メモリーが足りなければ拡張
            if (size() + 1 > capacity())
            {
                size_type __sz = size();
                // 1つだけ増やす
                if (__sz == 0)
                    __sz = 1;
                else
                    __sz *= 2;
                reserve(__sz);
            }

            // 要素を末尾に追加
            __alloc.construct(__end, val);
            // 有効な要素数を更新
            ++__end;
        }
        void pop_back()
        {
            __base_destruct_at_end(__end - 1);
        }
        iterator insert(iterator __position, const value_type& __val)
        {
            // line 1745
            // pointer __p = __begin + (__position - begin());

            size_type __idx = __position - begin();
            if (size() == capacity())
                reserve(size() == 0 ? 1 : size() * 2);
            __alloc.construct(__begin + size(), back());
            ++__end;
            iterator __pos = begin() + __idx;
            for (iterator __i = end() - 1; __i != __pos; --__i)
                *__i = *(__i - 1);
            *(begin() + __idx) = __val;
            // if (__end < __end_cap)

            // if (__p < __end)
            // {
            //     push_back(__val);
            //     __p = __begin + (__position - begin());
            //     for (pointer __ptr = __end - 1; __ptr != __p; --__ptr)
            //     {
            //         std::cout << *__ptr << std::endl;
            //     }

            // }
            // else
            //     push_back(__val);

            // if (__end < __end_cap)
            // {
            //     __alloc.construct(__end, __val);
            //     ++__end;
            //     if (__p < __end)
            //     {
            //         pointer __ptr = __end;
            //         for (; __ptr != __p; --__ptr)
            //         {
            //             std::cout << *__ptr << std::endl;
            //             *__ptr = *(__ptr - 1);
            //         }

            //         // __move_range(__p, this->__end_, __p + 1);
            //         // const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
            //         // if (__p <= __xr && __xr < this->__end_)
            //         //     ++__xr;
            //         // *__p = *__xr;
            //     }
            // }
            // else
            // {
            //     // allocator_type& __a = this->__alloc();
            //     // __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
            //     // __v.push_back(__x);
            //     // __p = __swap_out_circular_buffer(__v, __p);
            // }
            // return __make_iter(__p);
            return __pos;
        }
        void insert(iterator __position, size_type __n, const value_type& __val)
        {
            size_type __idx = __position - begin();
            if (__n > 0)
            {
                while (__n--)
                {
                    iterator __pos = begin() + __idx;
                    insert(__pos, __val);
                }
            }
        }
        template <class InputIterator>
        typename ft::enable_if<!std::is_integral<InputIterator>::value, void>::type
        insert(iterator __position, InputIterator __first, InputIterator __last)
        {
            size_type __idx = __position - begin();
            while (__first != __last)
            {
                iterator __pos = begin() + __idx;
                insert(__pos, *--__last);
            }
        }
        iterator erase(iterator __position)
        {
            if (__position == end())
                return __position;
            for (iterator __i = __position + 1; __i != end(); ++__i)
                *(__i - 1) = *__i;
            __alloc.destroy(&*(end() - 1));
            --__end;
            return __position;
        }
        iterator erase(iterator __first, iterator __last)
        {
            while (__first != __last)
            {
                erase(__first);
                --__last;
            }
            return __first;
        }
        void swap(vector& __x)
        {
            pointer __temp_begin = __x.__begin;
            pointer __temp_end = __x.__end;
            pointer __temp_end_cap = __x.__end_cap;
            allocator_type __temp_alloc = __x.__alloc;

            __x.__begin = __begin;
            __x.__end = __end;
            __x.__end_cap = __end_cap;
            __x.__alloc = __alloc;

            __begin = __temp_begin;
            __end = __temp_end;
            __end_cap = __temp_end_cap;
            __alloc = __temp_alloc;
        }
        void clear()
        {
            destroy_until(rend());
        }

	private:
        void __vallocate(size_type __n)
        {
            if (__n > max_size())
                throw std::length_error("vector");
            __begin = __end = __alloc.allocate(__n);
            __end_cap = __begin + __n;
        }
        void __vdeallocate()
        {
            if (__begin != NULL)
            {
                clear();
                __deallocate();
                __begin = __end = __end_cap = NULL;
            }
        }

		pointer allocate(size_type n)
		{
			return __alloc.allocate(n);
		}
        void __clear()
        {
            __base_destruct_at_end(__begin);
        }
        // destroy_until
        void __base_destruct_at_end(pointer __new_last)
        {
            pointer __soon_to_be_end = __end;
            while (__new_last != __soon_to_be_end)
                __alloc.destroy(--__soon_to_be_end);
            __end = __new_last;
        }
		void __deallocate()
		{
			__alloc.deallocate(__begin, capacity());
		}
		void destroy( pointer ptr )
		{
			__alloc.destroy(ptr);
		}
		void destroy_until( reverse_iterator rend )
		{
			for (reverse_iterator riter = rbegin() ; riter != rend ; ++riter, --__end)
				destroy( &*riter ) ;
		}
		void destroy_all()
		{
			destroy_until(rend());
			__deallocate();
			__begin = __end = __end_cap = NULL;
		}

        iterator __make_iter(pointer __p)
        {
            return iterator(__p);
        }
        const_iterator __make_iter(const_pointer __p) const
        {
            return const_iterator(__p);
        }
	};

    template <class _T, class _Allocator>
    void swap(vector<_T, _Allocator>& __x, vector<_T, _Allocator>& __y)
    {
        __x.swap(__y);
    }
}

#endif /* VECTOR_HPP */
