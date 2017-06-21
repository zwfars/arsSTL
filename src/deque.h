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
		using pointer = typename std::allocator_traits<Allocator>::pointer;
		using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
		using reverse_iterator = arsSTL::reverse_iterator<iterator>;
		using const_reverse_iterator = arsSTL::reverse_iterator<const_iterator>;
		using map_pointer = T**;

		// construct/copy/destroy:
		explicit deque(const Allocator& = Allocator()) : val_alloc(Allocator()) { init_aux(0, T()); }
		explicit deque(size_type n) { init_aux(n, T()); }
		deque(size_type n, const T& value, const Allocator& = Allocator());
		template <class InputIterator>
		deque(InputIterator first, InputIterator last, const Allocator& = Allocator()) :val_allo(Allocator()) {
			init_aux(0, T());
			insert(begin(), first, last);
		}
		deque(const deque<T, Allocator>& x) {
			init_aux(0, T());
			insert(begin(), x.begin(), x.end());
		}
		deque(deque&& x) {
			init_aux(0, T());
			swap(x);
		}
		deque(const deque& x, const Allocator& a) :val_alloc(a) {
			init_aux(0, T());
			insert(begin(), x.begin(), x.end());
		}
		deque(deque&& x, const Allocator& a):val_alloc(a) {
			init_aux(0, T());
			swap(x);
		}
		deque(std::initializer_list<T> x, const Allocator& = Allocator()) {
			init_aux(0, T());
			insert(begin(), x.begin(),x.end());
		}

		~deque() { 
			erase(begin(), end());
			map_alloc.deallocate(map, map_sz);
		}
		deque<T, Allocator>& operator=(const deque<T, Allocator>& x) {
			clear();
			insert(begin(), x.begin(), x.end());
			return *this;
		}
		deque<T, Allocator>& operator=(deque<T, Allocator>&& x) {
			clear();
			swap(x);
			return *this;
		}
		deque& operator=(std::initializer_list<T> x){
			clear();
			insert(begin(), x.begin(), x.end());
			return *this;
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			clear();
			insert(begin(), first, last);
		}
		void assign(size_type n, const T& t) {
			clear();
			insert(begin(), n, t);
		}
		void assign(std::initializer_list<T> x) {
			clear();
			insert(begin(), x.begin(), x.end());
		}
		allocator_type get_allocator() const noexcept { return val_alloc; }

		//// iterators:
		iterator                begin() noexcept { return element; }
		const_iterator          begin() const noexcept { return element; }
		iterator                end() noexcept { return first_free; }
		const_iterator          end() const noexcept { return first_free; }

		reverse_iterator        rbegin() noexcept { return reverse_iterator(first_free); }
		const_reverse_iterator  rbegin() const noexcept { return reverse_iterator(first_free); }
		reverse_iterator        rend() noexcept { return reverse_iterator(element); }
		const_reverse_iterator  rend() const noexcept { return reverse_iterator(element); }

		const_iterator          cbegin() noexcept { return element; }
		const_iterator          cend() noexcept { return first_free; }
		const_reverse_iterator  crbegin() const noexcept { return reverse_iterator(first_free); }
		const_reverse_iterator  crend() const noexcept { return reverse_iterator(element); }

		//// capacity:
		size_type size() const noexcept { return (first_free - element); }
		size_type max_size() const noexcept { return size_type(-1) / sizeof(T); }
		void      resize(size_type sz) { resize(sz, T()); }
		void      resize(size_type sz, const T& c);
		void      shrink_to_fit();
		bool      empty() const noexcept { return size() == 0; }

		//// element access:
		reference       operator[](size_type n) { return *(begin() + n); }
		const_reference operator[](size_type n) const { return *(begin() + n); }
		reference       at(size_type n) { return *(begin() + n); }
		const_reference at(size_type n) const { return *(begin() + n); }
		reference       front() {return *element; }
		const_reference front() const { return *element; }
		reference       back() { return *(first_free - 1); }
		const_reference back() const { return *(first_free - 1); }

		//// modifiers:
		template <class... Args> void emplace_front(Args&&... args);
		template <class... Args> void emplace_back(Args&&... args);
		template <class... Args> iterator emplace(const_iterator position, Args&&... args);

		void push_front(const T& x) { emplace_front(x); }
		void push_front(T&& x) { emplace_front(std::forward<T>(x)); }
		void push_back(const T& x) { emplace_back(x); }
		void push_back(T&& x) { emplace_back(std::forward<T>(x)); }

		iterator insert(const_iterator position, const T& x) { return emplace(position, x); }
		iterator insert(const_iterator position, T&& x) { return emplace(position, std::forward<T>(x)); }
		iterator insert(const_iterator position, size_type n, const T& x);
		template <class InputIterator>
		iterator insert(const_iterator position, InputIterator first,
			InputIterator last);
		iterator insert(const_iterator position, std::initializer_list<T> x) { insert(position, x.begin(), x.end()); }

		void pop_front();
		void pop_back();

		iterator erase(const_iterator position) { return erase(position, position + 1); }
		iterator erase(const_iterator first, const_iterator last);
		void     swap(deque<T, Allocator>&);
		void     clear() noexcept {
			erase(begin(), end());
			map_alloc.deallocate(map, map_sz);
			init_aux(0, T());
		}

	private:
		//some auxiliary functions
		void init_aux(size_type n, const T& value);
		void map_front_aux(size_type added_num = 1);
		void map_back_aux(size_type added_num = 1);
		void map_added_aux(size_type added_num,bool added_front);
		void rotate_aux(iterator first, iterator new_first, iterator last);
		void reverse_aux(iterator first, iterator last);
		template<typename InputIterator>
		void insert_aux(const_iterator position, InputIterator first, InputIterator last, std::false_type);
		template<typename InputIterator>
		void insert_aux(const_iterator position, InputIterator first, InputIterator last, std::true_type);
		
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

	//capacity 
	template<typename T,typename Allocator>
	void deque<T, Allocator>::resize(size_type n, const T& c) {
		while (size() < n)
			emplace_back(c);
		while (size() > n)
			pop_back();
	}

	//modifiers  emplace and insert
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
		if (first_free.cur == first_free.last-1) {
			map_back_aux();
			auto tem = first_free.parent + 1;
			*tem = val_alloc.allocate(chunk_sz(sizeof(T)));
			val_alloc.construct(first_free.cur, (args)...);
			first_free.set_node(tem);
			first_free.cur = first_free.first;
		}
		else
			val_alloc.construct(first_free.cur++, (args)...);
		element.cur = element.first + off;
	}

	template<typename T, typename Allocator>
	template <class... Args>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::emplace(const_iterator position, Args&&... args) {
		auto pos = position - element;
		if ((pos << 1) < size()) {
			emplace_front((args)...);
			rotate_aux(begin(), begin() + 1, begin() + pos + 1);
		}
		else {
			emplace_back((args)...);
			rotate_aux(begin() + pos, end() - 1, end());
		}
		return begin() + pos;
	}

	template<typename T,typename Allocator>
	typename deque<T, Allocator>::iterator deque<T,Allocator>::insert(const_iterator position, size_type n, const T& value) {
		auto off = position - element;
		for (size_type i = 0; i < n; i++)
			emplace(position, value);
		return begin() + off;
	}

	template<typename T,typename Allocator>
	template<typename InputIterator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator position,InputIterator first,InputIterator last) {
		auto off = position - begin();
		insert_aux(position, first, last, std::is_integral<InputIterator>::type());
		return begin() + off;
	}

	//modifiers pop and erase
	template<typename T,typename Allocator>
	void deque<T, Allocator>::pop_front() {
		val_alloc.destroy(element.cur);
		if (element.cur == element.last - 1) {
			val_alloc.deallocate(element.first, chunk_sz(sizeof(T)));
			element.set_node(element.parent + 1);
			element.cur = element.first;
		}
		else {
			++element.cur;
		}
		
	}

	template<typename T,typename Allocator>
	void deque<T, Allocator>::pop_back() {
		if (first_free.cur == first_free.first) {
			// have deallcated the memory
			val_alloc.deallocate(first_free.first, chunk_sz(sizeof(T)));
			first_free.set_node(first_free.parent - 1);
			first_free.cur = first_free.last;
		}
		val_alloc.destroy(--first_free.cur);
	}

	template<typename T,typename Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::erase(const_iterator first, const_iterator last) {
		size_type cnt = last - first;
		size_type off = first - begin();
		if (first - begin() > last - end()) {
			rotate_aux(first.remove_const(), last.remove_const(), end());
			for (auto i = 1; i <= cnt; i++)
				pop_back();
		}
		else {
			rotate_aux(begin(), first.remove_const(), last.remove_const());
			for (auto i = 1; i <= cnt; i++)
				pop_front();
		}
		return begin() + off;
	}

	template<typename T, typename Allocator>
	void deque<T, Allocator>::shrink_to_fit() {
		if ((first_free.cur - first_free.first) + (element.last - element.cur + 1) < chunk_sz(sizeof(T))) {
			deque tem(begin(), end());
			clear();
			swap(tem);
		}
	}
	
	//modifiers clear and swap

	template<typename T,typename Allocator>
	void deque<T, Allocator>::swap(deque<T, Allocator>& other) {
		if (*this != other) {
			std::swap(element, other.element);
			std::swap(first_free, other.first_free);
			std::swap(map, other.map);
			std::swap(map_sz, other.map_sz);
		}
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
			uninitialized_copy(element.parent, first_free.parent + 1, cur_elem);
			map_alloc.deallocate(map, last_sz);
			map = next_map;
			map_sz = next_sz;
		}
		element.set_node(cur_elem);
		first_free.set_node(cur_elem + last_sz - 1);
	}

	template<typename T,typename Allocator>
	void deque<T, Allocator>::rotate_aux(iterator first, iterator new_first, iterator last) {
		reverse_aux(first, new_first);
		reverse_aux(new_first, last);
		reverse_aux(first, last);
	}
	
	template<typename T,typename Allocator>
	void deque<T, Allocator>::reverse_aux(iterator first, iterator last) {
		--last;
		while (first < last) {
			std::swap(*first, *last);
			++first;
			--last;
		}
	}

	template<typename T,typename Allocator>
	template<typename InputIterator>
	void deque<T, Allocator>::insert_aux(const_iterator position, InputIterator first, InputIterator last, std::false_type) {
		size_type cnt = 0;                 //calculate the number of insertion
		size_type off = position - begin();
		if ((off << 1) < size()) {
			while (1) {
				--last;
				emplace_front(*last);
				++cnt;
				if (first == last)
					break;
			}
			rotate_aux(begin(), begin() + cnt, begin() + cnt + off);
		}
		else {
			size_type old_sz = size();
			while (first != last) {
				emplace_back(*first);
				++first;
				++cnt;
			}
			rotate_aux(begin() + off, begin() + old_sz, end());
		}
	}

	template<typename T, typename Allocator>
	template<typename InputIterator>
	void deque<T, Allocator>::insert_aux(const_iterator position, InputIterator first, InputIterator last, std::true_type) {
		size_type off = position - begin();
		if ((off << 1) < size()) {
			for (size_type i = 1; i <= first; i++)
				emplace_front(last);
			rotate_aux(begin(), begin() + first, begin() + first + off);
		}
		else {
			size_type old_sz = size();
			for (size_type i = 1; i <= first; i++)
				emplace_back(last);
			rotate_aux(begin() + off, begin() + old_sz, end());
		}
	}


	//some non-member functions
	template<typename T,typename Allocator>
	bool operator==(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); ++i)
			if (rhs[i] != lhs[i])
				return false;
		return true;
	}

	template<typename T, typename Allocator>
	bool operator!=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs){
		return !(lhs == rhs);
	}

	template<typename T,typename Allocator>
	bool operator<(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		size_t i;
		for (i = 0; i < lhs.size() && i < rhs.size(); ++i) {
			if (lhs[i] < rhs[i])
				return true;
			else if (lhs[i]>rhs[i])
				return false;
		}
		if (i == lhs.size())
			return true;
		return false;
	}

	template<typename T, typename Allocator>
	bool operator>(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		return rhs < lhs;
	}

	template<typename T, typename Allocator>
	bool operator<=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		return !(lhs>rhs);
	}

	template<typename T, typename Allocator>
	bool operator>=(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		return !(lhs<rhs);
	}
	
	template<typename T,typename Allocator>
	void swap(const deque<T, Allocator>& lhs, const deque<T, Allocator>& rhs) {
		lhs.swap(rhs);
	}

}

#endif
