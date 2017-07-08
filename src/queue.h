#ifndef QUEUE_H
#define QUEUE_H
#include"deque.h"

namespace arsSTL {
	template <class T, class Container = arsSTL::deque<T> >
	class queue {
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;
	protected:
		Container c;
	public:
		explicit queue(const Container& x) :c(x) {}
		explicit queue(Container&& x = Container()) :c(std::forward<Container>(x)) {}
		template <class Alloc> explicit queue(const Alloc& a) :c(a) {}
		template <class Alloc> queue(const Container& x, const Alloc& a) : c(x, a) {}
		template <class Alloc> queue(Container&& x, const Alloc& a) : c(std::move(x), a) {}
		template <class Alloc> queue(const queue& x, const Alloc& a) : c(x.c, a) {}
		template <class Alloc> queue(queue&& x, const Alloc& a) : c(std::move(x.c), a) {}

		bool empty() const {
			return c.empty();
		}
		size_type size() const {
			return c.size();
		}
		reference front() {
			return c.front();
		}
		const_reference front() const {
			return c.front();
		}
		reference back() {
			return c.back();
		}
		const_reference back() const {
			return c.back();
		}
		void push(const value_type& x) {
			c.push_back(x);
		}
		void push(value_type&& x) {
			c.push_back(std::move(x));
		}
		template <class... Args> void emplace(Args&&... args) {
			c.emplace_back(std::forward<Args>(args)...);
		}
		void pop() {
			c.pop_front();
		}
		void swap(queue& q) noexcept(noexcept(arsSTL::swap(c, q.c))) {
			using arsSTL::swap;
			swap(c, q.c);
		}
		// aux funtion
		const Container& get_container() const {
			return c;
		}
	};

	// some non-member function of queue
	template <class T, class Container>
	bool operator==(const queue<T, Container>& x, const queue<T, Container>& y) {
		return x.get_container() == y.get_container();
	}
	template <class T, class Container>
	bool operator!=(const queue<T, Container>& x, const queue<T, Container>& y) {
		return !(x == y);
	}

	template <class T, class Container>
	bool operator< (const queue<T, Container>& x, const queue<T, Container>& y) {
		return x.get_container() < y.get_container();
	}
	template <class T, class Container>
	bool operator> (const queue<T, Container>& x, const queue<T, Container>& y) {
		return y < x;
	}
	template <class T, class Container>
	bool operator>=(const queue<T, Container>& x, const queue<T, Container>& y) {
		return !(x < y);
	}
	template <class T, class Container>
	bool operator<=(const queue<T, Container>& x, const queue<T, Container>& y) {
		return !(x > y);
	}

	template <class T, class Container>
	void swap(queue<T, Container>& x, queue<T, Container>& y) noexcept(noexcept(x.swap(y))) {
		x.swap(y);
	}



	template <class T,class Container = vector<T>,
	class Compare = std::less<typename Container::value_type> >
	class priority_queue {
	public:
		using value_type = typename Container::value_type ;
		using reference = typename Container::reference ;
		using const_reference = typename Container::const_reference;
		using size_type = typename Container::size_type ;
		using container_type = Container;
	protected:
		Container c;
		Compare comp;
	public:
		priority_queue(const Compare& x, const Container& cx) :comp(x), c(cx) {
			force_heap();
		}
		explicit priority_queue(const Compare& x = Compare(), Container&& cx = Container()) :
			c(std::forward<Container>(cx)), comp(x) {
			force_heap();
		}
		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& x, const Container& cx) :
			comp(x), c(cx) {
			c.clear();
			c.insert(first, last);
			force_heap();
		}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last,const Compare& x = Compare(), Container&&cx = Container()):
			comp(x), c(std::forward<Container>cx) {
			c.clear();
			c.insert(first, last);
			force_heap();
		}

		template <class Alloc> 
		explicit priority_queue(const Alloc& a):c(a) {
			force_heap();
		}
		template <class Alloc> 
		priority_queue(const Compare& x, const Alloc& a) : comp(x), c(a) {
			force_heap();
		}
		template <class Alloc> 
		priority_queue(const Compare& x, const Container& cx, const Alloc&a) : comp(x), c(cx, a) {
			force_heap();
		}
		template <class Alloc> 
		priority_queue(const Compare& x, Container&& cx, const Alloc& a) : comp(x), c(std::forward<Container>(cx), a) {
			force_heap();
		}
		template <class Alloc> 
		priority_queue(const priority_queue& x, const Alloc& a) :comp(x.comp), c(x.c, a) {
			force_heap();
		}
		template <class Alloc> 
		priority_queue(priority_queue&& x, const Alloc&a) :comp(x.comp), c(std::move(x.c), a) {
			force_heap();
		}

		bool empty() const {
			return c.empty();
		}
		size_type size() const {
			return c.size();
		}
		const_reference top() const {
			return c.front();
		}
		void push(const value_type& x) {
			emplace(x);
		}
		void push(value_type&& x) {
			emplace(std::forward<value_type>(x));
		}
		template <class... Args> void emplace(Args&&... args) {
			c.emplace_back(std::forward<Args>(args)...);
			swim(c.size() - 1);
		}
		void pop() {
			if (!c.empty()) {
				std::swap(c[0], c[size() - 1]);
				c.pop_back();
				if(!c.empty())
					sink(0);
			}
		}
		void swap(priority_queue& q) noexcept(noexcept(std::swap(c, q.c))
			&& noexcept(std::swap(comp, q.comp))) {
			using std::swap;
			swap(c, q.c);
			swap(comp, q.comp);
		}
	private:
		void force_heap() {
			size_type len = c.size();
			for (int i = len / 2 - 1; i >= 0; --i)
				sink(i);
		}
		void sink(size_type k) {
			size_type len = c.size();
			while (2 * k + 1 <= len - 1) {
				size_type tem = 2 * k + 1;
				if ((tem + 1) <= (len - 1) && comp(c[tem], c[tem + 1]))
					++tem;
				if (comp(c[tem], c[k]))
					break;
				std::swap(c[k], c[tem]);
				k = tem;
			}
		}
		void swim(size_type k) {
			while (k > 0 && comp(c[(k-1)/2],c[k])) {
				std::swap(c[k], c[(k - 1) / 2]);
				k = (k - 1) / 2;
			}
		}
	};

	//some non-member function
	template <class T, class Container, class Compare>
	void swap(priority_queue<T, Container, Compare>& x,
		priority_queue<T, Container, Compare>& y)
		noexcept(noexcept(x.swap(y))) {
		x.swap(y);
	}
}

#endif
