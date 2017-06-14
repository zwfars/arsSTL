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
    //
		size_type chunk_sz() {
			return 16 / sizeof(value_type) > 1 ? 16 / sizeof(value_type) : size_type(1);
		}
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
		self& operator--(int) {
			self old = *this;
			--*this;
			return old;
		}
	


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
		last = first + chunk_sz();
	}
}



#endif
