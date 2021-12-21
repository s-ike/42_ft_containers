#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <exception>
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"

namespace ft {
	template < typename T, typename Allocator = std::allocator<T> >
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
		pointer			first ;
		// 最後の要素の1つ前方のポインター
		pointer			last ;
		// 確保したストレージの終端
		pointer			reserved_last ;
		// アロケーターの値
		allocator_type	alloc ;

	public:
		// constructor
		explicit vector(const allocator_type& __alloc = allocator_type())
			: first(0), last(0), reserved_last(0), alloc(__alloc)
		{}
		explicit vector(size_type __n, const value_type& __val = value_type(),
				 const allocator_type& __alloc = allocator_type())
			: first(0), last(0), reserved_last(0), alloc(__alloc)
		{
			if (__n > 0)
			{
				pointer __temp = allocate(__n);
				std::uninitialized_fill(__temp, __temp + __n, __val);
				first = __temp;
				reserved_last = last = first + __n;
			}

			// resize(__n, __val);

			// if (__n > 0)
			// {
			// 	allocate(__n);
			// 	for (size_type __i = 0; __i < __n; ++__i)
			// 		alloc.construct(&first[__i], __val);
			// }
		}
		template < typename InputIterator>
		vector(InputIterator __first, InputIterator __last, const allocator_type & __alloc = allocator_type(),
				typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: first(0), last(0), reserved_last(0), alloc(__alloc)
		{
			size_type __n = static_cast<size_type>(std::distance(__first, __last));
			if (__n > 0)
			{
				pointer __temp = allocate(__n);
				std::uninitialized_copy(__first, __last, __temp);
				first = __temp;
				reserved_last = last = first + __n;
			}

			// reserve(std::distance(__first, __last));
			// for (InputIterator __i = __first; __i != __last; ++__i)
			// 	push_back(*__i);
		}
		vector(const vector& __x)
			: first(0), last(0), reserved_last(0), alloc(__x.alloc)
		{
			size_type __n = __x.size();
			if (__n > 0)
			{
				pointer __temp = allocate(__n);
				std::uninitialized_copy(__x.begin(), __x.end(), __temp);
				first = __temp;
				reserved_last = last = first + __x.size();
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
		// デストラクター
		~vector()
		{
			clear();
			deallocate();
		}

		// コピー代入演算子ではアロケーターのコピーをする必要はない。
		// 自分自身への代入への対応が必要だ。
		// コピー代入のコピー先とコピー元の要素数が同じであるとは限らない。
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
					for (   auto src_iter = r.begin() + r.size(), src_end = r.end() ;
							src_iter != src_end ; ++src_iter, ++last )
					{
						alloc.construct( last, *src_iter ) ;
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
					for (size_type i = 0; i < r.size(); ++i, ++last)
					{
						alloc.construct(&first[i], r.first[i]);
					}
				}
			}
			return *this ;
		}

		// 要素アクセス
		// void push_back( const T & x ) ;
		// T & operator []( std::size_t i ) noexcept ;

		// イテレーターアクセス
		iterator begin()
		{
			// return first;
			return __make_iter(this->first);
			// return iterator(first);
		}
		iterator end()
		{
			// return last;
			return __make_iter(this->last);
			// return iterator(last);
		}
		const_iterator begin() const
		{
			// return first;
			return __make_iter(this->first);
			// return iterator(first);
		}
		const_iterator end() const
		{
			// return last;
			return __make_iter(this->last);
			// return iterator(last);
		}
		reverse_iterator rbegin()
		{
			return static_cast<reverse_iterator>(end());
		}
		reverse_iterator rend()
		{
			return static_cast<reverse_iterator>(begin());
		}
		const_reverse_iterator rbegin() const
		{
			return static_cast<const_reverse_iterator>(end());
		}
		const_reverse_iterator rend() const
		{
			return static_cast<const_reverse_iterator>(begin());
		}

		size_type size() const
		{
			return end() - begin() ;
		}
		bool empty() const
		{
			return begin() == end() ;
		}
		size_type capacity() const
		{
			return reserved_last - first ;
		}

		reference operator []( size_type i )
		{
			return first[i];
		}
		const_reference operator []( size_type i ) const
		{
			return first[i];
		}
		reference at( size_type i )
		{
			if ( i >= size() )
				throw std::out_of_range( "index is out of range." ) ;

			return first[i] ;
		}
		const_reference at( size_type i ) const
		{
			if ( i >= size() )
				throw std::out_of_range( "index is out of range." ) ;

			return first[i] ;
		}

		reference front()
		{
			return first;
		}
		const_reference front() const
		{
			return first;
		}
		reference back()
		{
			return last - 1;
		}
		const_reference back() const
		{
			return last - 1;
		}
		pointer data()
		{
			return first;
		}
		const_pointer data() const
		{
			return first;
		}

		void clear()
		{
			destroy_until( rend() ) ;
		}

		void reserve( size_type sz )
		{
			if ( sz <= capacity() )
				return ;

			pointer ptr = allocate( sz );
			pointer old_first = first ;
			size_type old_size = size();
			size_type old_capa = capacity();

			first = ptr ;
			last = first ;
			reserved_last = first + sz ;

			for (size_type i = 0; i < old_size; ++i, ++last)
				alloc.construct(&first[i], old_first[i]);
			for (size_type i = 0; i < old_size; ++i)
				destroy(&old_first[i]);
			alloc.deallocate(old_first, old_capa);
		}
		void resize (size_type n, value_type val = value_type())
		{
			// 現在の要素数より少ない
			if (n < size())
			{
				size_type diff = size() - n;
				destroy_until(rbegin() + diff);
				last = first + n;
			}
			// 現在の要素数より大きい
			else if (n > size())
			{
				reserve(n);
				for (; last != reserved_last; ++last)
				{
					alloc.construct(last, val);
				}
			}
		}

		void push_back(const value_type& val)
		{
			// 予約メモリーが足りなければ拡張
			if ( size() + 1 > capacity() )
			{
				size_type sz = size();
				// 1つだけ増やす
				if (sz == 0)
					sz = 1;
				else
					sz *= 2;
				reserve(sz);
			}

			// 要素を末尾に追加
			alloc.construct(last, val);
			// 有効な要素数を更新
			++last ;
		}

	private:
		iterator __make_iter(pointer __p);
		const_iterator __make_iter(const_pointer __p) const;

		pointer allocate(size_type n)
		{
			return alloc.allocate(n);
		}
		void deallocate()
		{
			alloc.deallocate(first, capacity());
		}
		void destroy( pointer ptr )
		{
			alloc.destroy(ptr);
		}
		void destroy_until( reverse_iterator rend )
		{
			for (reverse_iterator riter = rbegin() ; riter != rend ; ++riter, --last )
				destroy( &*riter ) ;
		}
		void destroy_all()
		{
			destroy_until(rend());
			deallocate();
			first = last = reserved_last = 0;
		}
	};

	template <class _Tp, class _Allocator>
	inline typename vector<_Tp, _Allocator>::iterator
	vector<_Tp, _Allocator>::__make_iter(pointer __p)
	{
		return iterator(__p);
	}

	template <class _Tp, class _Allocator>
	inline typename vector<_Tp, _Allocator>::const_iterator
	vector<_Tp, _Allocator>::__make_iter(const_pointer __p) const
	{
		return const_iterator(__p);
	}
}

#endif /* VECTOR_HPP */
