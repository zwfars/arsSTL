#ifndef HASH_TABLE_ITERATER_H
#define HASH_TABLE_ITERATER_H

#include<allocators>
#include"list.h"
#include"vector.h"

namespace arsSTL {
	template<typename T,typename Key,typename Hash = std::hash<key>,typename KeyEqual = std::equal<Key>,
	typename Extract_key, typename Allocator=std::allocator<T>>
	struct hash_table_iterator{
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = forward_iterator_tag;

		using size_type = size_t;
		using local_iterator = typename arsSTL::list<T>::iterator;
		using bucket_pointer = arsSTL::vector<arsSTL::list<T>>*;
        
		//construct function
		hash_table_iterator() = default;
		hash_table_iterator(bucket_pointer x_buck, size_type x_index, local_iterator x_cur) :bucket(x_buck)
			index(x_index), cur(x_cur);
		hash_table_iterator(const hast_table_iterator& x) = default;

		//operator function
		reference operator*() {
			return *cur;
		}
		
		pointer operator->() {
			return &(operator*());
		}
		
		hash_table_iterator& operator++() {
			++cur;
			if (cur == (*bucket)[index].end()) {
				while (cur == (*bucket)[index].end() && ++index < bucket.size()) {
					cur = (*bucket)[index].begin();
				}
			}
			return *this;
		}

		hash_table_iterator& operator++(int) {
			hash_table_iterator old = *this;
			++*this;
			return old;
		}

		//struct member
		bucket_pointer bucket;
		size_type index;
		local_iterator cur;
	
	
	};

	template<typename T, typename Key, typename Hash, typename KeyEqual, typename Extract_key, typename Allocator>
		bool operator==(const hash_table_iterator<T, Key, Hash, KeyEqual, Extract_key, Allocator>& lhs,
			const hash_table_iterator<T, Key, Hash, KeyEqual, Extract_key, Allocator>& rhs) {
		return lhs.cur == rhs.cur;
	}

	template<typename T, typename Key, typename Hash, typename KeyEqual,typename Extract_key, typename Allocator>
		bool operator!=(const hash_table_iterator<T, Key, Hash, KeyEqual, Extract_key, Allocator>& lhs,
			const hash_table_iterator<T, Key, Hash, KeyEqual, Extract_key, Allocator>& rhs) {
		return !(lhs == rhs);
	}
}

#endif
