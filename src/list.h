#ifndef LIST_H
#define LIST_H

#include"list_elem.h"
#include"iterator.h"

namespace arsSTL {
	template < class T, class Allocator = std::allocator<T>>
	class list {
	public:
		using value_type = T;
		using reference = value_type&; ;
		using const_reference = const value_type&;
		using iterator = list_iterator<T>;
		using const_iterator = list_iterator<const T>;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using allocator_type = Allocator;
		using pointer = typename allocator_traits<Allocator>::pointer;
		using const_point = typename allocator_traits<Allocator>::const_pointer;
		using reverse_iterator = arsSTL::reverse_iterator<iterator>;
		using const_reverse_iterator =  arsSTL::reverse_iterator<const_iterator>;
		using list_node = arsSTL::list_node<T>;
		using my_list = list<T, Allocator>;
	
	public:
		//explicit list(const Allocator& = Allocator());
		//explicit list(size_type n);
		//list(size_type n, const T& value, const Allocator& = Allocator());
		//template <class InputIterator>
		//list(InputIterator first, InputIterator last, const Allocator& = Allocator());
		//list(const list<T, Allocator>& x);
		//list(list&&);
		//list(const list&, const Allocator&);
		//list(list&&, const Allocator&);
		//list(initializer_list<T>, const Allocator& = Allocator());
		//~list();
		//list<T, Allocator>& operator=(const list<T, Allocator>& x);
		//list<T, Allocator>& operator=(list<T, Allocator>&& x);
		//list& operator=(initializer_list<T>);
		//template <class InputIterator>
		//void assign(InputIterator first, InputIterator last);
		//void assign(size_type n, const T& t);
		//void assign(initializer_list<T>);
		//allocator_type get_allocator() const noexcept;

		//// iterators:
		//iterator                begin() noexcept;
		//const_iterator          begin() const noexcept;
		//iterator                end() noexcept;
		//const_iterator          end() const noexcept;

		//reverse_iterator        rbegin() noexcept;
		//const_reverse_iterator  rbegin() const noexcept;
		//reverse_iterator        rend() noexcept;
		//const_reverse_iterator  rend() const noexcept;

		//const_iterator          cbegin() const noexcept;
		//const_iterator          cend() const noexcept;
		//const_reverse_iterator  crbegin() const noexcept;
		//const_reverse_iterator  crend() const noexcept;

		//// capacity:
		//size_type size() const noexcept;
		//size_type max_size() const noexcept;
		//void      resize(size_type sz);
		//void      resize(size_type sz, const T& c);
		//bool      empty() const noexcept;

		//// element access:
		//reference       front();
		//const_reference front() const;
		//reference       back();
		//const_reference back() const;

		//// modifiers:
		//template <class... Args> void emplace_front(Args&&... args);
		//void pop_front();
		//template <class... Args> void emplace_back(Args&&... args);
		//void push_front(const T& x);
		//void push_front(T&& x);
		//void push_back(const T& x);
		//void push_back(T&& x);
		//void pop_back();

		//template <class... Args> iterator emplace(const_iterator position, Args&&... args);
		//iterator insert(const_iterator position, const T& x);
		//iterator insert(const_iterator position, T&& x);
		//iterator insert(const_iterator position, size_type n, const T& x);
		//template <class InputIterator>
		//iterator insert(const_iterator position, InputIterator first,
		//	InputIterator last);
		//iterator insert(const_iterator position, initializer_list<T>);


		//iterator erase(const_iterator position);
		//iterator erase(const_iterator first, const_iterator last);
		//void     swap(list<T, Allocator>&);
		//void     clear() noexcept;

		//// list operations:
		//void splice(const_iterator position, list<T, Allocator>& x);
		//void splice(const_iterator position, list<T, Allocator>&& x);
		//void splice(const_iterator position, list<T, Allocator>& x,
		//	const_iterator i);
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
	private:
		Allocator::rebind<list_node>::other alloc;
		iterator first_free;
		size_type sz;
	};

}

#endif
