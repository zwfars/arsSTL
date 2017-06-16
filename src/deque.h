#ifndef DEQUE_H
#define DEQUE_H

#include"iterator.h"
#include"deque_iterator.h"
#include<allocators>
#define min_mapsz 8

namespace arsSTL {
	template <class T, class Allocator = std::allocator<T> >
	class deque {
	public:
		// types:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = deque_iterator<T, T&, T*>;
		using const_iterator = deque_iterator<T, const T&, const T*>;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using  allocator_type = Allocator;
		//using pointer = typename std::allocator_traits<Allocator>::pointer;
		//using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
		//using reverse_iterator = arsSTL::reverse_iterator<iterator>;
		//using const_reverse_iterator = arsSTL::reverse_iterator<const_iterator>;
		using map_pointer = T**;

		// construct/copy/destroy:
		explicit deque(const Allocator& = Allocator()): val_alloc(Allocator()) { init_aux(0, T()); }
		explicit deque(size_type n) { init_aux(n, T()); }
		deque(size_type n, const T& value, const Allocator& = Allocator());
		//template <class InputIterator>
		//deque(InputIterator first, InputIterator last, const Allocator& = Allocator());
		//deque(const deque<T, Allocator>& x);
		//deque(deque&&);
		//deque(const deque&, const Allocator&);
		//deque(deque&&, const Allocator&);
		//deque(initializer_list<T>, const Allocator& = Allocator());

		//~deque();
		//deque<T, Allocator>& operator=(const deque<T, Allocator>& x);
		//deque<T, Allocator>& operator=(deque<T, Allocator>&& x);
		//deque& operator=(initializer_list<T>);
		//template <class InputIterator>
		//void assign(InputIterator first, InputIterator last);
		//void assign(size_type n, const T& t);
		//void assign(initializer_list<T>);
		//allocator_type get_allocator() const noexcept;

		//// iterators:
		iterator                begin() noexcept { return element; }
		//const_iterator          begin() const noexcept;
		iterator                end() noexcept { return first_free; }
		//const_iterator          end() const noexcept;

		//reverse_iterator        rbegin() noexcept;
		//const_reverse_iterator  rbegin() const noexcept;
		//reverse_iterator        rend() noexcept;
		//const_reverse_iterator  rend() const noexcept;

		//const_iterator          cbegin() noexcept;
		//const_iterator          cend() noexcept;
		//const_reverse_iterator  crbegin() const noexcept;
		//const_reverse_iterator  crend() const noexcept;

		//// capacity:
		size_type size() const noexcept { return (first_free - element); }
		//size_type max_size() const noexcept;
		//void      resize(size_type sz);
		//void      resize(size_type sz, const T& c);
		//void      shrink_to_fit();
		//bool      empty() const noexcept;

		//// element access:
		//reference       operator[](size_type n);
		//const_reference operator[](size_type n) const;
		//reference       at(size_type n);
		//const_reference at(size_type n) const;
		//reference       front();
		//const_reference front() const;
		//reference       back();
		//const_reference back() const;

		//// modifiers:
		//template <class... Args> void emplace_front(Args&&... args);
		//template <class... Args> void emplace_back(Args&&... args);
		//template <class... Args> iterator emplace(const_iterator position, Args&&... args);

		//void push_front(const T& x);
		//void push_front(T&& x);
		//void push_back(const T& x);
		//void push_back(T&& x);

		//iterator insert(const_iterator position, const T& x);
		//iterator insert(const_iterator position, T&& x);
		//iterator insert(const_iterator position, size_type n, const T& x);
		//template <class InputIterator>
		//iterator insert(const_iterator position, InputIterator first,
		//	InputIterator last);
		//iterator insert(const_iterator position, initializer_list<T>);

		//void pop_front();
		//void pop_back();

		//iterator erase(const_iterator position);
		//iterator erase(const_iterator first, const_iterator last);
		//void     swap(deque<T, Allocator>&);
		//void     clear() noexcept;

		//some auxiliary functions
		void init_aux(size_type n, const T& value);
		
		// class members
	private:
		iterator element;
		iterator first_free;
		size_type map_sz;
		map_pointer map;
		Allocator val_alloc;
		typename Allocator::template rebind<T*>::other map_alloc;
	};

	//deque construct functioin
	template<typename T,typename Allocator>
	deque<T, Allocator>::deque(size_type n, const T& value, const Allocator& a):val_alloc(a){
		init_aux(n, value);
	}


	//some auxiliary functions
	template<typename T,typename Allocator>
	void deque<T, Allocator>::init_aux(size_type n, const T& value) {
		size_type block_sz = chunk_sz(sizeof(T));
		size_type needed = n / block_sz + 1;
		map_sz = min_mapsz;
		if (map_sz < needed + 2)
			map_sz = needed + 2;
		map = map_alloc.allocate(map_sz);
		map_pointer temfirst = map + (map_sz - needed) / 2;
		map_pointer temlast = temfirst + needed - 1;
		for (auto cur = temfirst; cur <= temlast; ++cur)
			*cur = val_alloc.allocate(block_sz);
		for (auto cur = temfirst; cur < temlast; ++cur)
			uninitialized_fill_n(*cur, block_sz, value);
		element.set_node(temfirst);
		first_free.set_node(temlast);
		element.cur = element.first;
		first_free.cur = first_free.first + n % block_sz;
		uninitialized_fill(first_free.first, first_free.cur, value);
	}

}

#endif
