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
		typename iterator_traits<Iterator>::reference>{
	public:
		using iterator_type = Iterator;
		using difference_type = typename iterator_traits<Iterator>::difference_type;
		using pointer = typename iterator_traits<Iterator>::pointer;
		using reference = typename iterator_traits<Iterator>::reference;
	public:
		reverse_iterator():current(nullptr) {}
		explicit reverse_iterator(Iterator x) : current(x) {}
		template <class U> reverse_iterator(const reverse_iterator<U>& u): current((Iterator)u) {}
		template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u) { current = (Iterator)u; return *this; }
		Iterator base() const { return current + 1; }
		reference operator*() const { return *current; }
		pointer operator->() const { return &(operator*()) };
		reverse_iterator& operator++();
		reverse_iterator  operator++(int);
		reverse_iterator& operator--();
		reverse_iterator  operator--(int);
		reverse_iterator  operator+ (difference_type n) const;
		reverse_iterator& operator+=(difference_type n);
		reverse_iterator  operator- (difference_type n) const;
		reverse_iterator& operator-=(difference_type n);

	protected:
		Iterator current;
	//private:
	//	Iterator deref_tmp  // exposition only
	};


	// operator function
	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator++() {
		--current;
		return *this;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>:: operator++(int) {
		Iterator tem = *this;
		--*this;
		return tem;
	}
	
	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator--() {
		++current;
		return *this;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>:: operator--(int) {
		Iterator tem = *this;
		++*this;
		return tem;
	};

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+ (difference_type n) const {
		Iterator tem = *this + n;
		return tem;
	}

	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator+=(difference_type n) {
		current += n;
		return *this;
	}

	template <typename Iterator>
	reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(difference_type n) const {
		return this->operator+(-n);
	}
	
	template <typename Iterator>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator-=(difference_type n){
		return this->operator+=(-n);
	}

};



#endif
