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
		reference       operator[](size_type n) { return *(begin() + n); }
		//const_reference operator[](size_type n) const;
		//reference       at(size_type n);
		//const_reference at(size_type n) const;
		//reference       front();
		//const_reference front() const;
		//reference       back();
		//const_reference back() const;

		//// modifiers:
		template <class... Args> void emplace_front(Args&&... args);
		template <class... Args> void emplace_back(Args&&... args);
		//template <class... Args> iterator emplace(const_iterator position, Args&&... args);

		void push_front(const T& x) { emplace_front(x); }
		void push_front(T&& x) { emplace_front(std::forward<T>(x)); }
		void push_back(const T& x) { emplace_back(x); }
		void push_back(T&& x) { emplace_back(std::forward<T>(x)); }

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
		void map_front_aux(size_type added_num = 1);
		void map_back_aux(size_type added_num = 1);
		void map_added_aux(size_type added_num,bool added_front);
		
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

	//modifiers
	template<typename T,typename Allocator>
	template <class... Args> 
	void deque<T, Allocator>::emplace_front(Args&&... args) {
		difference_type off = first_free.cur - first_free.first;
		if(element.cur==element.first){
			map_front_aux();
			auto tem = element.parent - 1;
			*tem = val_alloc.allocate(chunk_sz(sizeof(T)));
			element.set_node(tem);
			element.cur = element.last;
		}
		first_free.cur = off + first_free.first;
		val_alloc.construct(--element.cur, (args)...);
	}

	template<typename T, typename Allocator>
	template <class... Args>
	void deque<T, Allocator>::emplace_back(Args&&...args) {
		difference_type off = element.cur - element.first;
		if (first_free.cur == first_free.last - 1) {
			map_back_aux();
			auto tem = first_free.parent + 1;
			*tem = val_alloc.allocate(chunk_sz(sizeof(T)));
			first_free.set_node(tem);
			first_free.cur = first_free.first;
		}
		element.cur = element.first + off;
		val_alloc.construct(first_free.cur++, (args)...);
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

	template<typename T,typename Allocator>
	void deque<T,Allocator>::map_front_aux(size_type added_num) {
		if (added_num > element.parent - map) {
			map_added_aux(added_num, true);
		}
	}

	template<typename T,typename Allocator>
	void deque<T, Allocator>::map_back_aux(size_type added_num) {
		if (added_num > map + map_sz - first_free.parent - 1) {
			map_added_aux(added_num, false);
		}
	}

	template<typename T,typename Allocator>
	void deque<T, Allocator>::map_added_aux(size_type added_num, bool added_front) {
		size_type last_sz = first_free.parent - element.parent + 1;
		size_type cur_sz = last_sz + added_num;
		map_pointer cur_elem;
		if (map_sz > 2 * cur_sz) {
			cur_elem = map + (map_sz - cur_sz) / 2 + (added_front ? added_num : 0);
			if (element.parent >= cur_elem)
				uninitialized_copy(element.parent, first_free.parent + 1, cur_elem);
			else {
				auto last_tem = first_free.parent;
				auto tem = cur_elem + last_sz - 1;
				for (; tem >= cur_elem; --tem, --last_tem)
					tem = last_tem;
			}
		}
		else {
			size_type next_sz = map_sz + std::max(map_sz, cur_sz) + 2;
			map_pointer next_map = map_alloc.allocate(next_sz);
			cur_elem = next_map + (next_sz - cur_sz) / 2 + (added_front ? added_num : 0);
			uninitialized_copy(element.parent, first_free.parent + 1, next_map);
			map_alloc.deallocate(map, last_sz);
			map = next_map;
			map_sz = next_sz;
		}
		element.set_node(cur_elem);
		first_free.set_node(cur_elem + last_sz - 1);
	}

}

#endif
