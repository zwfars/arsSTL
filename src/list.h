#ifndef LIST_H
#define LIST_H

#include"list_elem.h"
#include"iterator.h"
#include<allocators>

namespace arsSTL {
	template < class T, class Allocator = std::allocator<T>>
	class list {
	public:
		using value_type = T;
		using reference = value_type&; ;
		using const_reference = const value_type&;
		using iterator = list_iterator<T>;
		using const_iterator = list_const_iterator<T>;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using allocator_type = Allocator;
		using pointer = typename std::allocator_traits<Allocator>::pointer;
		using const_point = typename std::allocator_traits<Allocator>::const_pointer;
		using reverse_iterator = arsSTL::reverse_iterator<iterator>;
		using const_reverse_iterator =  arsSTL::reverse_iterator<const_iterator>;
	private:
		using list_node = arsSTL::list_node<T>;
		using node_pointer = list_node*;
	
	public:
		explicit list(const Allocator& = Allocator());
		explicit list(size_type n);
		list(size_type n, const T& value, const Allocator& = Allocator());
		template <class InputIterator>
		list(InputIterator first, InputIterator last, const Allocator& = Allocator());
		list(const list<T, Allocator>& x);
		list(list&&);
		list(const list&, const Allocator&);
		list(list&&, const Allocator&);
		list(std::initializer_list<T>, const Allocator& = Allocator());
		~list() {
			clear();
			alloc.deallocate(first_free,1);
		}
		list<T, Allocator>& operator=(const list<T, Allocator>& x);
		list<T, Allocator>& operator=(list<T, Allocator>&& x);
		//list& operator=(initializer_list<T>);
		//template <class InputIterator>
		//void assign(InputIterator first, InputIterator last);
		//void assign(size_type n, const T& t);
		//void assign(initializer_list<T>);
		//allocator_type get_allocator() const noexcept { return alloc; }

		// iterators:
		iterator                begin() noexcept { return iterator(first_free->next); }
		const_iterator          begin() const noexcept { return const_iterator(first_free->next); }
		iterator                end() noexcept { return iterator(first_free); }
		const_iterator          end() const noexcept { return const_iterator(first_free); }

		//reverse_iterator        rbegin() noexcept;
		//const_reverse_iterator  rbegin() const noexcept;
		//reverse_iterator        rend() noexcept;
		//const_reverse_iterator  rend() const noexcept;

		const_iterator          cbegin() const noexcept { return const_iterator(first_free->next); }
		const_iterator          cend() const noexcept { return const_iterator(first_free); }
		//const_reverse_iterator  crbegin() const noexcept;
		//const_reverse_iterator  crend() const noexcept;

		//// capacity:
		size_type size() const noexcept { return sz; }
		size_type max_size() const noexcept { return size_t(-1) / sizeof(list_node); }
		//void      resize(size_type sz);
		//void      resize(size_type sz, const T& c);
		bool      empty() const noexcept { return sz == 0; }

		//// element access:
		reference       front() { return first_free->next->val; }
		const_reference front() const { return first_free->next->val; }
		reference       back() { return first_free->prev->val; }
		const_reference back() const { return first_free->next->val; }

		//// modifiers:
		template <class... Args> 
		void emplace_front(Args&&... args) { emp_aux(begin(), std::forward<Args>(args)...); }
		void pop_front() { erase(begin()); }
		template <class... Args> 
		void emplace_back(Args&&... args) { emp_aux(end(), std::forward<Args>(args)...); }
		void push_front(const T& x) { emp_aux(begin(), x); }
		void push_front(T&& x) { emp_aux(end(), std::forward<T>(x)); }
		void push_back(const T& x) { emp_aux(end(), x); }
		void push_back(T&& x) { emp_aux(end(), std::forward<T>(x)); }
		void pop_back() { erase(--end()); }

		template <class... Args> iterator emplace(const_iterator position, Args&&... args);
		iterator insert(const_iterator position, const T& x) { return emplace(position, x); }
		iterator insert(const_iterator position, T&& x) { return emplace(position, std::forward<T>(x)); }
		iterator insert(const_iterator position, size_type n, const T& x);
		template <class InputIterator>
		iterator insert(const_iterator position, InputIterator first,
			InputIterator last) {
			return ins_aux(iterator(position.cur), first, last, typename std::is_integral<InputIterator>::type());
		}
		iterator insert(const_iterator position, std::initializer_list<T> x) {
			return insert(iterator(position.cur), x.begin(), x.end());
		}


		iterator erase(const_iterator position);
		iterator erase(const_iterator first, const_iterator last);
		void     swap(list<T, Allocator>& x) {
			std::swap(first_free, x.first_free);
			std::swap(sz, x.sz);
		}
		void     clear() noexcept { erase(begin(), end()); }

		// list operations:
		//void splice(const_iterator position, list<T, Allocator>& x);
		//void splice(const_iterator position, list<T, Allocator>&& x);
		//void splice(const_iterator position, list<T, Allocator>& x,const_iterator i);
		//void splice(const_iterator position, list<T, Allocator>&& x,
		//	const_iterator i);
		//void splice(const_iterator position, list<T, Allocator>& x,
		//	const_iterator first, const_iterator last);
		//void splice(const_iterator position, list<T, Allocator>&& x,
		//	const_iterator first, const_iterator last);

		//void remove(const T& value);
		//template <class Predicate> void remove_if(Predicate pred);

		//void unique();
		//template <class BinaryPredicate> void unique(BinaryPredicate binary_pred);

		//void merge(list<T, Allocator>& x);
		//void merge(list<T, Allocator>&& x);
		//template <class Compare> void merge(list<T, Allocator>& x, Compare comp);
		//template <class Compare> void merge(list<T, Allocator>&& x, Compare comp);

		//void sort();
		//template <class Compare> void sort(Compare comp);

		//void reverse() noexcept;
	

	// aux funciton
	private:
		void list_init();
		template<typename...Args>
		node_pointer creat_aux(Args&&...);
		template<typename...Args>
		node_pointer emp_aux(iterator, Args...);
		
		template<typename InputIterator>
		iterator ins_aux(iterator postion, InputIterator first, InputIterator last, std::true_type);

		template<typename InputIterator>
		iterator ins_aux(iterator postion, InputIterator first, InputIterator last,std::false_type);

		void node_free(node_pointer position);

		template<typename InputIterator>
		void assign_aux(InputIterator first, InputIterator last, std::true_type);

		template<typename InputIterator>
		void assign_aux(InputIterator first, InputIterator last, std::false_type);


	private:
		/*syntax!!!*/
		typename Allocator::template rebind<list_node>::other alloc;
		node_pointer first_free;
		size_type sz;
	};



	//construct function
	template<typename T,typename Allocator>
	list<T, Allocator>::list(const Allocator& a):alloc(a){
		list_init();
	}
	template<typename T,typename Allocator>
	list<T, Allocator>::list(size_type n) {
		list_init();
		for (size_type i = 0; i < n; i++)
			emp_aux(end(), T());
	}

	template<typename T,typename Allocator>
	list<T, Allocator>::list(size_type n, const T& value, const Allocator& x):alloc(x){
		list_init();
		insert(begin(), n, value);
	}

	template<typename T,typename Allocator>
	template <class InputIterator>
	list<T, Allocator>::list(InputIterator first, InputIterator last, const Allocator& x):alloc(x){
		list_init();
		insert(begin(), first, last);
	}

	template<typename T,typename Allocator>
	list<T, Allocator>::list(const list<T, Allocator>& x) {
		list_init();
		insert(begin(), x.begin(), x.end());
	}

	template<typename T,typename Allocator>
	list<T,Allocator>::list(list&& x) {
		sz = x.sz;
		x.sz = 0;
		first_free = x.first_free;
		x.first_free = nullptr;
	}

	template<typename T,typename Allocator>
	list<T, Allocator>::list(const list& lx, const Allocator& x):alloc(x) {
		list_init();
		insert(begin(), lx.begin(), lx.end());
	}
	
	template<typename T,typename Allocator>
	list<T, Allocator>::list(list&& lx, const Allocator& x):alloc(x){
		sz = x.sz;
		x.sz = 0;
		first_free = x.first_free;
		x.first_free = nullptr;
	}

	template<typename T,typename Allocator>
	list<T, Allocator>::list(std::initializer_list<T> ix, const Allocator& x) {
		list_init();
		insert(begin(), ix.begin(), ix.end());
	}


	//operator = and assign
	template<typename T,typename Allocator>
	list<T, Allocator>& list<T, Allocator>:: operator=(const list<T, Allocator>& x) {
		if (this != &x) {
			clear();
			insert(begin(), x.begin(), x.end());
		}
		return *this;
	}

	template<typename T, typename Allocator>
	list<T, Allocator>& list<T,Allocator>::operator=(list<T, Allocator>&& x) {
		if (this != &x) {
			clear();
			swap(x);
		}
		return *this;
	}

	template<typename T, typename Allocator>
	list& list<T, Allocator>::operator=(initializer_list<T> x) {
		clear();
		insert(begin(), x.begin(), x.end());
	}

	template<typename T,typename Allocator>
	template <class InputIterator>

	void list<T, Allocator>::assign(InputIterator first, InputIterator last) {
		
		assign_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<typename T, typename Allocator>
	void list<T, Allocator>::assign(size_type n, const T& t) {
		assing_aux(n, t, std::true_type);
	}

	template<typename T,typename Allocator>
	void list<T, Allocator>::assign(initializer_list<T> x) {
		assign(x.begin(), x.end());
	}

	//modifiers  insert functions
	template<typename T,typename Allocator>
	template <class... Args> 
	typename list<T, Allocator>::iterator list<T, Allocator>::emplace(const_iterator position, Args&&... args) {
		auto tot = emp_aux(iterator(position.cur), std::forward<Args>(args)...);
		return iterator(tot);
	}

	template<typename T,typename Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator position, size_type n, const T& x) {
		iterator tem(position.cur);
		for (size_type i = 0; i < n; i++) {
			emp_aux(tem, x);
			++tem;
		}
		return iterator(position.cur);
	}

	//modifiers erase functions
	template<typename T,typename Allocator>
	typename list<T, Allocator>::iterator list<T,Allocator>::erase(const_iterator position) {
		node_pointer tem = position.cur;
		node_pointer ans(nullptr);
		if (sz > 0) {
			ans = tem->next;
			tem->prev->next = tem->next;
			tem->next->prev = tem->prev;
			node_free(tem);
		}
		return iterator(ans);
	}

	template<typename T,typename Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator first, const_iterator last) {
		while (first!= last)
			erase(first++);
		return iterator(last.cur);
	}



	// auxiliary function
	template<typename T,typename Allocator>
	void list<T, Allocator>::list_init() {
		first_free = alloc.allocate(1);
		first_free->next = first_free;
		first_free->prev = first_free;
	}

	template<typename T,typename Allocator>
	template<typename...Args>
	typename list<T, Allocator>::node_pointer list<T, Allocator>::creat_aux(Args&&...args) {
		node_pointer tem = alloc.allocate(1);
		alloc.construct(tem,(args)...);
		return tem;
	}

	template<typename T,typename Allocator>
	template<typename...Args>
	typename list<T,Allocator>::node_pointer list<T, Allocator>::emp_aux(iterator position, Args...args) {
		node_pointer tem = creat_aux(std::forward<Args>(args)...);
		tem->next = position.cur;
		tem->prev = position.cur->prev;
		tem->prev->next = tem;
		position.cur->prev = tem;
		++sz;
		return tem;
	}

	template<typename T,typename Allocator>
	template<typename InputIterator>
	typename list<T, Allocator>::iterator list<T, Allocator>::ins_aux(iterator position, InputIterator first, InputIterator last,std::true_type) {
		while (first--)
			insert(position, last);
		return position;
	}

	template<typename T, typename Allocator>
	template<typename InputIterator>
	typename list<T,Allocator>::iterator list<T, Allocator>::ins_aux(iterator position, InputIterator first, InputIterator last, std::false_type) {
		while (1) {
			--last;
			position = insert(position, *last);
			if (last == first)
				break;
		}
		return position;
	}

	template<typename T,typename Allocator>
	void list<T, Allocator>::node_free(node_pointer position) {
		--sz;
		alloc.destroy(position);
		alloc.deallocate(position, 1);
	}

	template<typename T,typename Allocator>
	template<typename InputIterator>
	void list<T, Allocator>::assign_aux(InputIterator first, InputIterator last, std::true_type) {
		clear();
		ins_aux(begin(), first, last, std::true_type);
	}

	template<typename T, typename Allocator>
	template<typename InputIterator>
	void list<T, Allocator>::assign_aux(InputIterator first, InputIterator last, std::false_type) {
		iterator tem = begin();
		for (; first != last&&tem != end(); tem++, first++) {
			alloc.destory(tem);
			alloc.construct(tem, *first);
		}
		insert(end(), first, last);
		erase(tem, end());
	}

}

#endif
