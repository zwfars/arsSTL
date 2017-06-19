#ifndef DEQUE_ITERATOR_H
#define DEQUE_ITERATOR_H

#include "iterator.h"

namespace arsSTL {
	template<typename T,typename Refer,typename Ptr>
	struct deque_iterator {
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = Ptr;
		using reference = Refer;
		using iterator_category = random_access_iterator_tag;
		using size_type = size_t;
		using map_pointer = T**;
		using self = deque_iterator;
	
    
	//operator functions
		self& operator++() {
			if (cur == last) {
				set_node(parent + 1);
				cur = first;
			}
			else
				++cur;
			return *this;
		}
		
		self operator++(int) {
			self old = *this;
			++*this;
			return old;
		}
		
		self& operator--() {
			if (cur == first) {
				set_node(parent - 1);
				cur = last;
			}
			else
				--cur;
			return *this;
		}
		
		self operator--(int) {
			self old = *this;
			--*this;
			return old;
		}

		self& operator+=(difference_type n) {
			if (n >= 0){
				size_type total = cur - first + n;
				set_node(parent + total / chunk_sz(sizeof(T)));
				cur = first + total % chunk_sz(sizeof(T));
			}
			else {
				size_type total = -n - (cur - first);
				set_node(parent - total / chunk_sz(sizeof(T)));
				cur = last - total % chunk_sz(sizeof(T));
			}
			return *this;
		}

		self& operator-= (difference_type n) {
			return *this += (-n);
		}

		self operator+(difference_type n) {
			self tem = *this;
			tem += n;
			return tem;
		}

		self operator-(difference_type n) {
			self tem = *this;
			tem -= n;
			return tem;
		}



		reference operator*() {return *cur;}


	//some auxiliary functions
		void set_node(map_pointer other);

	//struct member
		pointer cur;
		pointer first;
		pointer last;
		map_pointer parent;
		
	};
	template<typename T, typename Refer, typename Ptr>
	void deque_iterator<T, Refer, Ptr>::set_node(map_pointer other) {
		parent = other;
		first = *parent;
		last = first + chunk_sz(sizeof(T));
	}
	
	// some non-member functions
	size_t chunk_sz(size_t sz) {
		return 16 / sz > 1 ? 16 / sz : size_t(1);
	}

	template<typename T,typename Ref,typename Ptr>
	typename deque_iterator<T,Ref,Ptr>::difference_type operator-(const deque_iterator<T,Ref,Ptr>& lhs, const deque_iterator<T,Ref,Ptr>& rhs) {
		return (lhs.parent - rhs.parent - 1)*chunk_sz(sizeof(T)) +
			(rhs.last - rhs.cur ) + (lhs.cur - lhs.first);
	}
}



#endif
