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
		Container get_container() const {
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
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;
	protected:
		Container c;
		Compare comp;
	public:
		priority_queue(const Compare& x, const Container& cx) :comp(x), c(cx) {}
		explicit priority_queue(const Compare& x = Compare(), Container&& cx = Container()) :
			c(std::forward<Container>(cx)), comp(x) {}
		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& x, const Container& cx) :
			comp(x), c(cx) {
			c.clear();
			c.insert(first, last);
		}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last,const Compare& x = Compare(), Container&&cx = Container()):
			comp(x), c(std::forward<Container>cx) {
			c.clear();
			c.insert(first, last);
		}

		template <class Alloc> 
		explicit priority_queue(const Alloc& a) :c(a) {}
		template <class Alloc> 
		priority_queue(const Compare& x, const Alloc& a) : comp(x), c(a) {}
		template <class Alloc> 
		priority_queue(const Compare& x, const Container& cx, const Alloc&a) : comp(x), c(cx, a) {}
		template <class Alloc> 
		priority_queue(const Compare& x, Container&& cx, const Alloc& a) : comp(x), c(std::forward<Container>(cx), a);
		template <class Alloc> 
		priority_queue(const priority_queue& x, const Alloc& a) :comp(x.comp), c(x.c, a) {}
		template <class Alloc> 
		priority_queue(priority_queue&& x, const Alloc&a) :comp(x.comp), c(std::move(x.c), a) {}

		bool empty() const {
			return c.empty();
		}
		size_type size() const {
			return c.size();
		}
		const_reference top() const {
			return c.front();
		}
		void push(const value_type& x);
		void push(value_type&& x);
		template <class... Args> void emplace(Args&&... args);
		void pop();
		void swap(priority_queue& q) noexcept(noexcept(swap(c, q.c))
			&& noexcept(swap(comp, q.comp))) {
			using std::swap;
			swap(c, q.c);
			swap(comp, q.comp);
		}
	};
}

#endif
