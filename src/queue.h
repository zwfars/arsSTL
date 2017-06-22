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
		explicit queue(Container&& x = Container()) :c(x) {}
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
    //note that const is important
		Container get_container() const {
			return c;
		}
	};

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
}

#endif
