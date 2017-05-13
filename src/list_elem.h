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
	};


	template<typename T>
	struct list_iterator{
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = bidirectional_iterator_tag;
	};
}



#endif
