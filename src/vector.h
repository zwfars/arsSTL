#ifndef VECTOR_H
#define VECTOR_H

#include<memory>
#include"iterator.h"
#include <type_traits>   
#include<allocators>

namespace arsSTL {
	template <class T, class Allocator = std::allocator<T> > 
	class vector {
	public:
		using reference = T&;
		using const_reference = const T&;
		using iterator = T*;
		using const_iterator = const T*;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using allocator_type = Allocator;
		using pointer = T*;
		using const_pointer = T* const;

		/*to do until iterator*/
		//using reverse_iterator = reverse_iterator<iterator>; 
		//using const_reverse_iterator = reverse_iterator<const_iterator>;
	public:
		explicit vector(const Allocator& = Allocator());
		explicit vector(size_type n);
		vector(size_type n, const T& value, const Allocator& = Allocator());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last);
		//vector(const vector<T, Allocator>& x);
		//vector(vector&&);
		//vector(const vector&, const Allocator&);
		//vector(vector&&, const Allocator&);
		//vector(initializer_list<T>, const Allocator& = Allocator());

		//~vector();
		//vector<T, Allocator>& operator=(const vector<T, Allocator>& x);
		//vector<T, Allocator>& operator=(vector<T, Allocator>&& x);
		//vector& operator=(initializer_list<T>);
		//template <class InputIterator>
		//void assign(InputIterator first, InputIterator last);
		//void assign(size_type n, const T& t);
		//void assign(initializer_list<T>);
		//allocator_type get_allocator() const noexcept;

		//// iterators:
		iterator                begin() noexcept { return element; }
		const_iterator          begin() const noexcept { return element; }
		iterator                end() noexcept { return first_free; };
		const_iterator          end() const noexcept { return first_free };

		//reverse_iterator        rbegin() noexcept;
		//const_reverse_iterator  rbegin() const noexcept;
		//reverse_iterator        rend() noexcept;
		//const_reverse_iterator  rend() const noexcept;

		const_iterator          cbegin() noexcept { return element; }
		const_iterator          cend() noexcept { return first_free; }
		//const_reverse_iterator  crbegin() const noexcept;
		//const_reverse_iterator  crend() const noexcept;

		//// capacity:
		size_type size() const noexcept { return first_free - element; }
		size_type max_size() const noexcept { return size_t(-1) / sizeof(T); };
		//void      resize(size_type sz);
		//void      resize(size_type sz, const T& c);
		size_type capacity() const noexcept { return cap - element; };
		bool      empty() const noexcept { return element == first_free; }
		//void      reserve(size_type n);
		//void      shrink_to_fit();

		// element access:
		reference       operator[](size_type n) { return *(begin() + n); }
		const_reference operator[](size_type n) const { return *(cbegin() + n); }
		reference       at(size_type n) { return *(begin() + n); }
		const_reference at(size_type n) const {return *(cbegin() + n);}
		reference       front() { return *begin(); }
		const_reference front() const { return *cbegin(); }
		reference       back() { return *(end() - 1); }
		const_reference back() const { return *(cend() - 1); }
	
		////data access
		//T*       data() noexcept;
		//const T* data() const noexcept;
	
		//// modifiers:
		//template <class... Args> void emplace_back(Args&&... args);
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
		//void     swap(vector<T, Allocator>&);
		//void     clear() noexcept;

		// some helper functions
		template <class InputIterator>
		void auxvec(InputIterator first, InputIterator last, std::false_type);
		template <class InputIterator>
		void auxvec(InputIterator first, InputIterator last, std::true_type);

	private:
		iterator element;
		iterator first_free;
		iterator cap;
		Allocator alloc;
	};

	template<typename T,typename Allocator>
	vector<T, Allocator>::vector(const Allocator& a) :alloc{ a }, element(0), first_free(0), cap(0){}
     
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type n) {
		element = alloc.allocate(n);
		cap = first_free = element + n;
	}
	
	template<typename T, typename Allocator>
	vector<T,Allocator>::vector(size_type n, const T& value, const Allocator& a): alloc(a){
		element = alloc.allocate(n);
		auto tem = element;
		for (int i = 0; i != n; i++)
			alloc.construct(tem++,value);
		first_free = cap = tem;
	}

	template<typename T,typename Allocator>
	template <class InputIterator>
	vector<T, Allocator>::vector(InputIterator first, InputIterator last) {
		auxvec(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<typename T, typename Allocator>
	template <class InputIterator>
	void vector<T, Allocator>::auxvec(InputIterator first, InputIterator last, std::false_type) {
		element = alloc.allocate(last - first);
		cap = first_free = uninitialized_copy(first, last, element);
		
	}

	template<typename T, typename Allocator>
	template <class InputIterator>
	void vector<T, Allocator>::auxvec(InputIterator first, InputIterator last, std::true_type) {
		element = alloc.allocate(first);
		auto tem = element;
		for (int i = 0; i != first; i++)
			alloc.construct(tem++, last);
		first_free = cap = tem;
	}


}




#endif
