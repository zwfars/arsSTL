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

	// the member of list_iterator
		node_pointer cur;
	// construct function
		list_iterator(node_pointer x=nullptr) :cur(x) {}
		
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
		node_pointer cur;
		list_const_iterator(node_pointer x = nullptr) :cur(x) {}
		list_const_iterator(list_iterator<T> x) :cur(x.cur) {}

		my_iterator operator++() {
			cur = cur->next;
			return *this;
		}
		my_iterator operator--() {
			cur = cur->prev;
			return *this;
		}

	};
}



#endif
