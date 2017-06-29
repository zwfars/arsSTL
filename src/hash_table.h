#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include<allocators>
#include"list.h"
#include"vector.h"
#include"hash_table_iterator.h"

namespace arsSTL {
	template<typename T, typename Key, typename Extract_key, typename Hash = std::hash<Key>, 
		typename KeyEqual = std::equal_to<Key>, typename Allocator = std::allocator<T>>
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
		using const_local_iterator = typename arsSTL::list<T>::const_iterator;
		using iterator = hash_table_iterator<T, Key, Extract_key, Hash, KeyEqual, Allocator>;
		using const_iterator = iterator;
		//using hash_alloc = typename Allocator::template rebind<arsSTL::list<T>>::other;

		const static size_type prime_sz = 28;
		const static size_type prime[prime_sz];

	public:
		//construct function
		hash_table():sz(0), maximum_load_factor(1.0),buckets(get_next_prime(0)){}


		hash_table(hasher xhf,Extract_key xget_key,KeyEqual xequal,size_type n,Allocator a): sz(n),max_load_factor(1.0), 
				hash_func(xhf),get_key(xget_key),equal(xequal),alloc(a),buckets(get_next_prime(n)){}


	public:
		// size and capacity
		bool      empty() const noexcept {
			return sz == 0;
		}
		size_type size() const noexcept {
			return sz;
		}
		size_type max_size() const noexcept {
			return prime[prime_sz - 1];
		}

		
		//// iterators
		iterator       begin() noexcept {
			for (size_type i = 0; i < bucket_count(); ++i) {
				if (buckets[i].begin() != buckets[i].end())
					return iterator(&buckets, i, buckets[i].begin());
			}
			return end();
		}
		const_iterator begin() const noexcept {
			return const_cast<hash_table *>(this)->begin();
		}
		iterator       end() noexcept {
			size_type tem = bucket_count() - 1;
			return iterator(&buckets, tem, buckets[tem].end());
		}
		const_iterator end() const noexcept {
			const_cast<hash_table*>(this)->begin();
		}
		const_iterator cbegin() const noexcept {
			return begin();
		}
		const_iterator cend() const noexcept {
			return end();
		}

		//// modifiers
		template <class... Args> arsSTL::pair<iterator, bool> emplace(Args&&... args) {
			if (load_factor() > max_load_factor()) {
				rehash(bucket_count() + 1);
			}
			T tem(std::forward<Args>(args)...);
			if (find(get_key(tem)) == end()) {
				++sz;
				size_type pos = bucket(get_key(tem));
				buckets[pos].emplace_back(get_key(tem));
				auto tt = --buckets[pos].end();
				return arsSTL::pair<iterator, bool>(iterator(&buckets, pos, tt),true);
			}
			else {
				return arsSTL::pair<iterator, bool>(find(get_key(tem)),false);
			}
		}
		template <class... Args> 
		iterator emplace_hint(const_iterator position, Args&&... args) {
			if (load_factor() > maximum_load_factor) {
				rehash(bucket_count() + 1);
			}
			T tem(std::forward<Args>(args)...);
			size_type pos = bucket(get_key(tem));
			if (position.index != pos) {
				auto tem_pair = emplace(tem);
				return tem_pair.first;
			}
			else {
				auto tem_iter = buckets[pos].insert(position.cur, tem);
				return iterator(&buckets, pos, tem_iter);
			}
		}
		
		pair<iterator, bool> insert(const value_type& obj) {
			return emplace(obj);
		}
		
		pair<iterator, bool> insert(value_type&& obj) {
			return emplace(std::forward<value_type>(obj));
		}
		
		iterator insert(const_iterator hint, const value_type& obj) {
			return emplace_hint()
		}
		//iterator insert(const_iterator hint, value_type&& obj);
		//template <class InputIterator> void insert(InputIterator first, InputIterator last);
		//void insert(initializer_list<value_type>);

		//iterator erase(const_iterator position);
		//size_type erase(const key_type& k);
		//iterator erase(const_iterator first, const_iterator last);
		//void clear() noexcept;

		//void swap(unordered_set&);

		//// observers
		//hasher hash_function() const;
		//key_equal key_eq() const;

		//// lookup
		iterator       find(const key_type& k) {
			size_type pos = bucket(k);
			for (auto iter = buckets[pos].begin(); iter != buckets[pos].end(); ++iter) {
				if (equal(*iter, k))
					return iterator(&buckets, pos, iter);
			}
			return end();
		}
		//const_iterator find(const key_type& k) const;
		//size_type count(const key_type& k) const;
		//std::pair<iterator, iterator> equal_range(const key_type& k);
		//std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

		//// bucket interface
		size_type bucket_count() const noexcept {
			return buckets.size();
		}

		//size_type max_bucket_count() const noexcept;
		size_type bucket_size(size_type n) const {
			return buckets[n].size();
		}
		size_type bucket(const key_type& k) const {
			return hash_func(k) % bucket_count();
		}
		local_iterator begin(size_type n) {
			return buckets[n].begin();
		}
		const_local_iterator begin(size_type n) const {
			return buckets[n].begin();
		}
		local_iterator end(size_type n) {
			return buckets[n].end();
		}
		const_local_iterator end(size_type n) const {
			return buckets[n].end();
		}
		const_local_iterator cbegin(size_type n) const {
			return buckets[n].begin();
		}
		const_local_iterator cend(size_type n) const {
			return buckets[n].end();
		}

		//// hash policy
		float load_factor() const noexcept {
			return sz / static_cast<float>(bucket_count());
		}
		float max_load_factor() const noexcept {
			return maximum_load_factor;
		}
		void max_load_factor(float z) {
			maximum_load_factor = z;
		}
		void rehash(size_type n) {
			size_type num = get_next_prime(n);
			buckets.resize(n);
		}
		//void reserve(size_type n);


		// observers
		hasher hash_function() const {
			return hash_func;
		}
		key_equal key_eq() const {
			return equal;
		}
	private:
		//aux function
		size_type get_next_prime(size_type n) {
			for (auto i = 0; i < prime_sz; ++i)
				if (prime[i]>n)
					return prime[i];
		}
	private:
		hasher hash_func;
		Extract_key get_key;
		KeyEqual equal;
		Allocator alloc;
		arsSTL::vector<arsSTL::list<T,Allocator>> buckets;
		size_type sz;
		float maximum_load_factor;
	};

	template<typename T, typename Key, typename Extract_key, typename Hash, typename KeyEqual, typename Allocator>
	const size_t hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>::prime[prime_sz] = {
		3u, 97u, 193u, 389u, 769u, 1543u, 3079u, 6151u, 12289u, 
		24593u, 49157u,98317u, 196613u, 393241u, 786433u, 1572869u, 
		3145739u, 6291469u, 12582917u,25165843u, 50331653u, 100663319u, 
		201326611u, 402653189u, 805306457u,1610612741u, 3221225473u, 4294967291u,
	};
}
#endif
