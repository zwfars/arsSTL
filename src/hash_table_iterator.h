#ifndef HASH_TABLE_ITERATER_H
#define HASH_TABLE_ITERATER_H

#include<allocators>
#include"list.h"
#include"vector.h"

namespace arsSTL {
	template<typename T,typename Ref,typename Ptr,typename Key, typename Extract_key,typename Hash = std::hash<key>,
		typename KeyEqual = std::equal<Key>, typename Allocator=std::allocator<T>>
	struct hash_table_iterator{
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = Ptr;
		using reference =  Ref;
		using iterator_category = forward_iterator_tag;
		using iterator = hash_table_iterator<T, T&, T*, Key, Extract_key, Hash,KeyEqual,Allocator>;
		using const_iterator = hash_table_iterator<T, const T&, const T*, Key, Extract_key, Hash, KeyEqual, Allocator>;
		using size_type = size_t;
		using local_iterator = typename arsSTL::list<T>::iterator;
		using bucket_pointer = arsSTL::vector<arsSTL::list<T,Allocator>>*;
        
		//construct function
		hash_table_iterator() = default;
		hash_table_iterator(bucket_pointer x_buck, size_type x_index, local_iterator x_cur) :bucket(x_buck),
			index(x_index), cur(x_cur) {};
		hash_table_iterator(const iterator& x) :bucket(x.bucket), index(x.index), cur(x.cur) {}

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
				while (cur == (*bucket)[index].end() && ++index < bucket->size()) {
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

	template<typename T, typename Ref,typename Ptr, typename Key, typename Hash, typename KeyEqual, typename Extract_key, typename Allocator>
		bool operator==(const hash_table_iterator<T,Ref,Ptr, Key, Hash, KeyEqual, Extract_key, Allocator>& lhs,
			const hash_table_iterator<T,Ref,Ptr,Key, Hash, KeyEqual, Extract_key, Allocator>& rhs) {
		return lhs.cur == rhs.cur;
	}

	template<typename T,typename Ref,typename Ptr, typename Key, typename Hash, typename KeyEqual,typename Extract_key, typename Allocator>
		bool operator!=(const hash_table_iterator<T,Ref,Ptr, Key, Hash, KeyEqual, Extract_key, Allocator>& lhs,
			const hash_table_iterator<T,Ref,Ptr, Key, Hash, KeyEqual, Extract_key, Allocator>& rhs) {
		return !(lhs == rhs);
	}

}

#endif
