#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include<allocators>
#include"list.h"
#include"vector.h"
#include"hash_table_iterator.h"

namespace arsSTL {
	template<typename T, typename Key, typename Hash = std::hash<key>, typename KeyEqual = std::equal<Key>,
		typename Extract_key, typename Allocator = std::allocator<T >>
	class hash_table {
	public:
		using value_type = T;
		using reference = value_type&; ;
		using const_reference = const value_type&;
		using key_type = Key;
		using value_type = T;
		using hasher = Hash;
		using key_equal = KeyEqual;
		using pointer = T *;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using local_iterator = typename arsSTL::list<T>::iterator;
		using iterator = hash_table_iterator<T, Key, Hash, KeyEqual, Extract_key, Allocator>;

		const static size_type prime_sz = 28;
		const static size_type prime[prime_sz];

	private:
		hasher hash;
		Extract_key get_key;
		KeyEqual equal;
		Allocator alloc;
		arsSTL::vector<arsSTL::list<T>,Allocator> buckets;
		size_type sz;
		float max_load_factor;


	};


	/*template<typename T, typename Key, typename Hash, typename KeyEqual,typename Extract_key, typename Allocator>
	const size_t hash_table<T, Key, Hash, KeyEqual, Extract_key, Allocator>::prime[prime_sz] = {
		53u, 97u, 193u, 389u, 769u, 1543u, 3079u, 6151u, 
		12289u, 24593u, 49157u,98317u, 196613u, 393241u, 
		786433u, 1572869u, 3145739u, 6291469u, 12582917u,
		25165843u, 50331653u, 100663319u, 201326611u, 402653189u, 
		805306457u, 1610612741u, 3221225473u, 4294967291u,
	}*/


}
#endif
