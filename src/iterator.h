#ifndef ITERATOR_H
#define ITERATOR_H

#include<stddef.h>

namespace arsSTL {
	// Iterator tags
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};

	//class iterator
	template<typename category,typename T,typename Distance = ptrdiff_t,typename Pointer = T*,typename Reference = T&>
	struct iterator {
		using value_type = T;
		using difference_type = Distance;
		using pointer = Pointer;
		using reference = Reference;
		using iterator_category = category;
	};

	//class iterator_traits
	template<typename Iterator>
	struct iterator_traits{
		using value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;
		using iterator_category = typename Iterator::iterator_category;
	};

	// iterator_traits--- pointer
	template<typename T>
	struct iterator_traits<T*>{
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = random_access_iterator_tag;
	};

	//iterator_traits --- const pointer
	template<typename T>
	struct iterator_traits<const T*> {
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = random_access_iterator_tag;
	};	

}


#endif
