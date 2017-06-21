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
		using iterator = deque_iterator<T, T&, T*>;
		using const_iterator = deque_iterator<T, const T&, const T*>;
		

		//construct functions
		deque_iterator() :cur(0), first(0), last(0), parent(0) {}
		
		//convert iterator to const_iterator
		deque_iterator(map_pointer xmap, T* xcur) :cur(xcur), first(*xmap), last(*xmap + chunk_sz(sizeof(T))), parent(xmap) {}
		deque_iterator(const iterator &x) :cur(x.cur), first(x.first), last(x.last), parent(x.parent) {};
	    
	//operator functions
		self& operator++() {
			++cur;
			if (cur == last) {
				set_node(parent + 1);
				cur = first;
			}
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
				//int total = -n - (cur - first);
				if (cur - first >= -n)
					cur = cur + n;
				else {
					size_type total = -n - (cur - first);
					set_node(parent - 1 - total / chunk_sz(sizeof(T)));
					cur = last - total % chunk_sz(sizeof(T));
				}
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
		
		// < ,==
		bool operator==(const self& other) {
			return cur == other.cur;
		}

		bool operator!=(const self& other) {
			return !(*this == other);
		}

		bool operator<(const self&other) {
			return parent == other.parent ? (cur < other.cur) : (parent < other.parent);
		}

		reference operator*() {return *cur;}


	//some auxiliary functions
		void set_node(map_pointer other);
	
    //remove const property
		iterator remove_const() const {
			//iterator tem(parent, cur);
			return iterator(parent,cur);
		}

	//struct member
		T* cur;
		T* first;
		T* last;
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

	template<typename T, typename Ref, typename Ptr,typename oRef,typename oPtr>
	typename deque_iterator<T, Ref, Ptr>::difference_type operator-(const deque_iterator<T, Ref, Ptr>& lhs, const deque_iterator<T, oRef, oPtr>& rhs) {
		return (lhs.parent - rhs.parent - 1)*chunk_sz(sizeof(T)) +
			(rhs.last - rhs.cur) + (lhs.cur - lhs.first);
	}
}



#endif
