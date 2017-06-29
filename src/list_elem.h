#ifndef LIST_ELEM_H
#define LIST_ELEM_H

// list_node and list_iterator

#include"iterator.h"
#include<stddef.h>


namespace arsSTL {
	template<typename T>
	struct list_node {
		list_node* prev;
		list_node* next;
		T val;
		template<typename ...Arg>
		list_node(Arg&&...arg) :val(std::forward<Arg>(arg)...) {}
	};

	template<typename T>
	struct list_iterator{
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = bidirectional_iterator_tag;
		using node_pointer = list_node<T>*;
		using my_iterator = list_iterator<T>;
		struct const_list_iterator;
	// the member of list_iterator
		node_pointer cur;
	// construct function
		list_iterator(node_pointer x = nullptr) :cur(x) {}

		//operator function	
		my_iterator& operator++() {
			cur = cur->next;
			return *this;
		}
		my_iterator& operator--() {
			cur = cur->prev;
			return *this;
		}
		my_iterator operator++(int) {
			my_iterator old = *this;
			++*this;
			return old;
		}
		my_iterator operator--(int) {
			my_iterator old = *this;
			--*this;
			return old;
		}
		T& operator*() {
			return cur->val;
		}

	};
	template<typename T>
	struct list_const_iterator {
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = bidirectional_iterator_tag;
		using node_pointer = list_node<T>*;
		using my_iterator = list_const_iterator <T>;

		//the member of list_const_iterator
		node_pointer cur;
		list_const_iterator(node_pointer x = nullptr) :cur(x) {}
		list_const_iterator(list_iterator<T> x) :cur(x.cur) {}

		my_iterator& operator++() {
			cur = cur->next;
			return *this;
		}
		my_iterator& operator--() {
			cur = cur->prev;
			return *this;
		}
		my_iterator operator++(int) {
			my_iterator old = *this;
			++*this;
			return old;
		}
		my_iterator operator--(int) {
			my_iterator old = *this;
			--*this;
			return old;
		}

		reference operator*() {
			return cur->val;
		}


	};

	// non-member function 
	template<typename T>
	bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs) { 
		return lhs.cur == rhs.cur; 
	}
	template<typename T>
	bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs) { 
		return !(lhs == rhs); 
	}

	template<typename T>
	bool operator==(const list_const_iterator<T>& lhs, const list_const_iterator<T>& rhs) { 
		return lhs.cur == rhs.cur; 
	}
	template<typename T>
	bool operator!=(const list_const_iterator<T>& lhs, const list_const_iterator<T>& rhs) { 
		return !(lhs == rhs); 
	}
}



#endif
