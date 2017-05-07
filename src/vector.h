#ifndef VECTOR_H
#define VECTOR_H

#include<memory>
#include"iterator.h" 
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
		using const_pointer = const T*;

		/*to do until iterator*/
		//using reverse_iterator = reverse_iterator<iterator>; 
		//using const_reverse_iterator = reverse_iterator<const_iterator>;
	public:
		explicit vector(const Allocator& = Allocator());
		explicit vector(size_type n);
		vector(size_type n, const T& value, const Allocator& = Allocator());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector<T, Allocator>& x);
		vector(vector&&);
		vector(const vector&, const Allocator&);
		vector(vector&&, const Allocator&);
		vector(std::initializer_list<T>, const Allocator& = Allocator());

		~vector();
		vector<T, Allocator>& operator=(const vector<T, Allocator>& x);
		vector<T, Allocator>& operator=(vector<T, Allocator>&& x);
		vector& operator=(std::initializer_list<T>);
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const T& t);
		void assign(std::initializer_list<T>);
		allocator_type get_allocator() const noexcept { return alloc; }

		//// iterators:
		iterator                begin() noexcept { return element; }
		const_iterator          begin() const noexcept { return element; }
		iterator                end() noexcept { return first_free;}
		const_iterator          end() const noexcept { return first_free; }

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
		template <class... Args> void emplace_back(Args&&... args) { emp_aux(end(), (args)...); }
		void push_back(const T& x) { emp_aux(end(), x); }
		void push_back(T&& x) { emp_aux(end(), std::forward<T&&>(x)); }
		//void pop_back();
	
		template <class... Args> iterator emplace(const_iterator position, Args&&... args);
		iterator insert(const_iterator position, const T& x) { emplace(position, x); }
		iterator insert(const_iterator position, T&& x) { emplace(position, std::forward<T&&>(x)); }
		//iterator insert(const_iterator position, size_type n, const T& x);
		//template <class InputIterator>
		//iterator insert(const_iterator position, InputIterator first,
		//	InputIterator last);
		//iterator insert(const_iterator position, initializer_list<T>);
	
		iterator erase(const_iterator position);
		iterator erase(const_iterator first, const_iterator last);
		void     swap(vector<T, Allocator>&);
		void     clear() noexcept {erase(begin(),end())};

    // == and !=
	public:
		template<class T, class Allocator>
		friend bool operator == (const vector<T, Allocator>& , const vector<T, Allocator>& );
		template<class T, class Allocator>
		friend bool operator != (const vector<T, Allocator>& , const vector<T, Allocator>& );

		// some helper functions
	private:
		template <class InputIterator>
		void vec_aux(InputIterator first, InputIterator last, std::false_type);
		template <class InputIterator>
		void vec_aux(InputIterator first, InputIterator last, std::true_type);
		void vec_free();
		template <class... Args>
		void emp_aux(iterator tempos, Args&&... args);
		//void ins_aux(iterator, const T&);


	private:
		iterator element;
		iterator first_free;
		iterator cap;
		Allocator alloc;
	};

	//construct function
	template<typename T,typename Allocator>
	vector<T, Allocator>::vector(const Allocator& a) :alloc{ a }, element(nullptr), first_free(nullptr), cap(nullptr){}
     
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type n) {
		element = alloc.allocate(n);
		uninitialized_fill_n(element, n, T());
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
		vec_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<typename T,typename Allocator>
	vector<T, Allocator>::vector(const vector<T, Allocator>& x){
		element = alloc.allocate(x.size());
		cap = first_free = uninitialized_copy(x.begin(), x.end(), element);
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(vector&& x):element(x.element),first_free(x.first_free),cap(x.cap){
		x.first_free = x.element = x.cap = nullptr;
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(const vector& x, const Allocator& a) : alloc(a) {
		element = alloc.allocate(x.size());
		cap = first_free = uninitialized_copy(x.begin(), x.end(), element);
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(vector&& x, const Allocator& a) :alloc(a),element(x.element),first_free(x.first_free),cap(x.cap) {
		x.element = x.cap = x.first_free = nullptr;

	}

	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(std::initializer_list<T> x, const Allocator& a):alloc(a){
		element = alloc.allocate(x.size());
		first_free = cap = uninitialized_copy(x.begin(), x.end(), element);
	}


	//deconstruct funciton
	template<typename T, typename Allocator>
	vector<T, Allocator>::~vector() {
		vec_free();
	}



	// operator=
	template<typename T,typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector<T, Allocator>& x) {
		auto tem = alloc.allocate(x.size());
		auto temcap = uninitialized_copy(x.begin(), x.end(), tem);
		vec_free();
		element = tem;
		cap = first_free = element = temcap;
		return *this
	}

	template<typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>:: operator=(vector<T, Allocator>&& x) {
		auto temelement = x.element;
		auto temfirst_free = x.first_free;
		auto temcap = x.cap;
		x.first_free = x.element = x.cap = nullptr;
		vec_free();
		element = temelement;
		first_free = temfirst_free;
		cap = temcap;
		return *this;
	}

	template<typename T, typename Allocator>
	vector<T,Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> x) {
		vec_free();
		element = alloc.allocate(x.size());
		first_free = cap = uninitialized_copy(x.begin(), x.end(), element);
		return *this;
	}


	// assign function
	template<typename T,typename Allocator>
	template <class InputIterator>
	void vector<T, Allocator>::assign(InputIterator first, InputIterator last) {
		vec_free();
		vec_aux(first, last,typename std::is_integral<InputIterator>::type());
		                    
	}

	template<typename T, typename Allocator>
	void vector<T, Allocator>::assign(size_type n, const T& t) {
		element = alloc.allocate(n);
		uninitialized_fill_n(element, n, t);
		cap = first_free = element + n;
	}

	template<typename T, typename Allocator>
	void vector<T, Allocator>::assign(std::initializer_list<T> x) {
		vec_free();
		element = alloc.allocate(x.size());
		first_free = cap = uninitialized_copy(x.begin(), x.end(), element);
	}


	// erase function
	template<typename T, typename Allocator>
	typename vector<T,Allocator>::iterator vector<T,Allocator>::erase(const_iterator position){
		iterator tem = (iterator)position;
		uninitialized_copy(tem, first_free, tem);
		--first_free;
		alloc.destroy(first_free);
		return tem;
	}
	template<typename T,typename Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
		iterator temfirst = (iterator) first;
		iterator temlast = (iterator)last;
		iterator tem = uninitialized_copy(temlast, first_free,temfirst);
		for (auto p = end(); p != temfirst;)
			alloc.destroy(--p);
		first_free = tem;
		return temfirst;
	}

	//swap function
	template<typename T, typename Allocator>
	void vector<T, Allocator>::swap(vector<T, Allocator>& x) {
		std::swap(first_free, x.first_free);
		std::swap(element, x.element);
		std::swap(cap, x.cap);
	}


	//emplace and insert function
	template<typename T,typename Allocator>
	template <class... Args> 
	typename vector<T, Allocator>::iterator vector<T, Allocator>::emplace(const_iterator position, Args&&... args) {
		iterator tempos = (iterator)position;
		emp_aux(tempos, (args)...);
		return tempos;
	}




	// friend functions 
	template<class T, class Allocator>
	bool operator == (const vector<T, Allocator>& x1, const vector<T, Allocator>& x2) {
		if (x1.size() != x2.size())
			return false;
		auto tem1 = x1.begin();
		auto tem2 = x2.begin();
		while (tem1 != x1.end()) {
			if (*tem1 != *tem2)
				return false;
			tem1++;
			tem2++;
		}
		return true;
	}

	template<class T, class Allocator>
	bool operator != (const vector<T, Allocator>& x1, const vector<T, Allocator>& x2) {
		return !(x1 == x2);
	}



	// vector auxiliary function 
	template<typename T, typename Allocator>
	template <class InputIterator>
	void vector<T, Allocator>::vec_aux(InputIterator first, InputIterator last, std::false_type) {
		element = alloc.allocate(last - first);
		cap = first_free = uninitialized_copy(first, last, element);

	}

	template<typename T, typename Allocator>
	template <class InputIterator>
	void vector<T, Allocator>::vec_aux(InputIterator first, InputIterator last, std::true_type) {
		element = alloc.allocate(first);
		uninitialized_fill_n(element, first, last);
		first_free = cap = element + first;
	}

	template<typename T,typename Allocator>
	void vector<T, Allocator>::vec_free() {
		if (element) {
			for (auto p = first_free; p != element;)
				alloc.destroy(--p);
			alloc.deallocate(element, cap - element);
		}
	}

	template<typename T, typename Allocator>
	template <class... Args>
	void vector<T, Allocator>::emp_aux(iterator tempos, Args&&... args) {
		if (end() < cap) {
			uninitialized_copy(tempos, end(), tempos + 1);
			alloc.construct(tempos, std::forward<Args>(args)...);
			first_free++;
		}
		else {
			size_type temsize = size() ? 2 * size() : 1;
			iterator temelement = alloc.allocate(temsize);
			iterator cur = uninitialized_copy(element, tempos, temelement);
			alloc.construct(cur, std::forward<Args>(args)...);
			iterator temfirst_free = uninitialized_copy(tempos, end(), cur + 1);
			vec_free();
			element = temelement;
			first_free = temfirst_free;
			cap = temsize + element;
		}
	}

}




#endif
