#ifndef STACK_H
#define STACK_H
#include "deque.h"

namespace arsSTL {
	template <class T, class Container = arsSTL::deque<T>>
	class stack {
	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::size_type size_type;
		typedef Container container_type;

	protected:
		Container c;

	public:
		explicit stack(const Container& x) :c(x) {}
		explicit stack(Container&&x = Container()) :c(std::move(x)) {}
		template <class Alloc> explicit stack(const Alloc& a) :c(a) {}
		template <class Alloc> stack(const Container& x, const Alloc& a) : c(x, a) {}
		template <class Alloc> stack(Container&& x, const Alloc& a) : c(std::move(x), a) {}
		template <class Alloc> stack(const stack& x, const Alloc& a) : c(x.c, a) {}
		template <class Alloc> stack(stack&& x, const Alloc& a) : c(std::move(x.c), a) {}

		Container get_container() { return c; }
		bool empty() const {
			return c.empty();
		}
		size_type size() const {
			return c.size();
		}
		reference top() {
			return c.back();
		}
		const_reference top() const {
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
			c.pop_back();
		}
		void swap(stack& s) noexcept(noexcept(arsSTL::swap(c, s.c))) {
			using arsSTL::swap;
			swap(c, s.c);
		}
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
		return x.get_container() == y.get_container();
	}
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return !(x == y);
	}

	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) {
		return x.get_container() < y.get_container();
	}
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) {
		return y < x;
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return !(x < y);
	}
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
		reutrn !(x > y);
	}

	template <class T, class Container>
	void swap(stack<T, Container>& x, stack<T, Container>& y) noexcept(noexcept(x.swap(y))) {
		x.swap(y);
	}
}
#endif
