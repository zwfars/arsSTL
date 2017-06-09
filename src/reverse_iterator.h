#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator.h"

namespace arsSTL {
	template< class Iterator >
	class reverse_iterator : public iterator<
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference> {
	public:
		using iterator_type = Iterator;                        
		using difference_type = typename iterator_traits<Iterator>::difference_type;
		using pointer = typename iterator_traits<Iterator>::pointer;
		using reference = typename iterator_traits<Iterator>::reference;
	public:
		reverse_iterator():current(nullptr) {}
		explicit reverse_iterator(Iterator x) : current(x) {}
		template <class U> reverse_iterator(const reverse_iterator<U>& u): current(u.base()) {}
		template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u) { current = u.base(); return *this; }
		//reverse_iterator(it).base() == it
		Iterator base() const { return current; }
		reference operator*() const {
			Iterator tem = current;
			return *(--tem); }
		pointer operator->() const { return &(operator*()) };
		reverse_iterator& operator++();
		reverse_iterator  operator++(int);
		reverse_iterator& operator--();
		reverse_iterator  operator--(int);
		reverse_iterator  operator+ (difference_type n) const;
		reverse_iterator& operator+=(difference_type n);
		reverse_iterator  operator- (difference_type n) const;
		reverse_iterator& operator-=(difference_type n);
		reference operator[](difference_type n) const { return *(*this + n); }

	protected:
		Iterator current;
	};


	// operator function
	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator++() {
		--current;
		return *this;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>:: operator++(int) {
		reverse_iterator<Iterator> tem = *this;
		--current;
		return tem;
	}
	
	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator--() {
		++current;
		return *this;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>:: operator--(int) {
		reverse_iterator<Iterator> tem = *this;
		++current;
		return tem;
	};

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+ (difference_type n) const {
		return reverse_iterator<Iterator>(current + n);
	}

	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator+=(difference_type n) {
		current += n;
		return *this;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(difference_type n) const {
		return reverse_iterator<Iterator>(current - n);
	}
	
	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator-=(difference_type n){
		current += n;
		return *this;
	}

	//friend function
	template< class Iterator1, class Iterator2 >
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return !(lhs == rhs);
	}

	template< class Iterator1, class Iterator2 >
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template< class Iterator1, class Iterator2 >
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return !(rhs < lhs);
	}
	template< class Iterator1, class Iterator2 >
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return !(lhs <= rhs);
	}
	template< class Iterator1, class Iterator2 >
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
		return !(lhs < rhs);
	}

};

#endif
