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
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using local_iterator = typename list<T>::iterator;
		using const_local_iterator = typename list<T>::const_iterator;
		using iterator = hash_table_iterator<T, T&,T*,Key, Extract_key, Hash, KeyEqual, Allocator>;
		using const_iterator = hash_table_iterator<T,const T&,const T*, Key, Extract_key, Hash, KeyEqual, Allocator>;

		const static size_type prime_sz = 28;
		const static size_type prime[prime_sz];

	public:
		//construct function
		hash_table():sz(0), maximum_load_factor(1.0),buckets(get_next_prime(0)){}
		hash_table(size_type n) :sz(0), maximum_load_factor(1.0), buckets(get_next_prime(n)) {}
		hash_table(hasher xhf,Extract_key xget_key,KeyEqual xequal,size_type n,Allocator a): sz(0),maximum_load_factor(1.0), 
				hash_func(xhf),get_key(xget_key),hash_equal(xequal),alloc(a),buckets(get_next_prime(n)){}
		~hash_table() = default;
	public:
		Allocator get_allocator() const {
			return alloc;
		}

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
			return const_cast<hash_table*>(this)->end();
		}
		const_iterator cbegin() const noexcept {
			return begin();
		}
		const_iterator cend() const noexcept {
			return end();
		}

		//// modifiers
		template <class... Args> 
		pair<iterator, bool> emplace(Args&&... args) {
			if (load_factor() > max_load_factor()) {
				rehash(bucket_count() + 1);
			}
			T tem(std::forward<Args>(args)...);
			auto tem_iter = find(get_key(tem));
			if ( tem_iter== end()) {
				++sz;
				size_type pos = bucket(get_key(tem));
				buckets[pos].emplace_back(tem);
				auto tt = --buckets[pos].end();
				return pair<iterator, bool>(iterator(&buckets, pos, tt),true);
			}
			else {
				return pair<iterator, bool>(tem_iter,false);
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
			return emplace_hint(hint, obj);
		}
		
		iterator insert(const_iterator hint, value_type&& obj) {
			return emplace_hint(hint, std::forward<value_type>(obj));
		}
		template <class InputIterator> 
		
		void insert(InputIterator first, InputIterator last) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}
		
		void insert(std::initializer_list<value_type> x) {
			insert(x.begin(), x.end());
		}

		iterator erase(const_iterator position) {
			size_type idx = position.index;
			iterator pos(position.bucket,position.index, position.cur);
			auto haha = pos;
			auto next_iter = ++pos;
			if (buckets[idx].begin() != buckets[idx].end()) {
				buckets[idx].erase(haha.cur);
				--sz;
			}
			return next_iter;
		}
		
		size_type erase(const key_type& k) {
			size_type pos = bucket(k);
			size_type cnt = 0;
			for (auto iter = buckets[pos].begin(); iter != buckets[pos].end();) {
				if (hash_equal(get_key(*iter), k)) {
					iter = buckets[pos].erase(iter);
					++cnt;
					--sz;
				}
				else
					++iter;
			}
			return cnt;
		}

		iterator erase(const_iterator first, const_iterator last) {
			iterator tem_iter(first.bucket, first.index, first.cur);
			iterator tem_last(last.bucket, last.index,last.cur);
			while (tem_iter!=tem_last)
				tem_iter = erase(tem_iter);
			return tem_iter;
		}
		
		void clear() noexcept {
			erase(begin(), end());
		}

		void swap(hash_table& x) {
			buckets.swap(x.buckets);
			std::swap(maximum_load_factor, x.maximum_load_factor);
			std::swap(sz, x.sz);
		}

		
		//// lookup
		iterator       find(const key_type& k) {
			size_type pos = bucket(k);
			for (auto iter = buckets[pos].begin(); iter != buckets[pos].end(); ++iter) {
				if (hash_equal(get_key(*iter), k))
					return iterator(&buckets, pos, iter);
			}
			return end();
		}
		
		const_iterator find(const key_type& k) const {
			return const_cast<hash_table*>(this)->find(k);
		}
		
		size_type count(const key_type& k) const {
			if (find(k) == end())
				return 0;
			return 1;
		}
		pair<iterator, iterator> equal_range(const key_type& k) {
			auto tem_iter = find(k);
			if (find(k) == end())
				return pair<iterator, iterator>(end(), end());
			return pair<iterator, iterator>(tem_iter, ++tem_iter);
			
		}

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			return const_cast<hash_table*>(this)->equal_range(k);
		}

		//// bucket interface
		size_type bucket_count() const noexcept {
			return buckets.size();
		}

		size_type max_bucket_count() const noexcept {
			return prime[prime_sz - 1];
		}
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
			if (n <= bucket_count())
				return;
			size_type num = get_next_prime(n);
			hash_table other;
			for (auto iter = begin(); iter != end(); ++iter)
				other.insert(*iter);
			swap(other);
		}
		void reserve(size_type n) {
			buckets.reserve(n);
		}


		// observers
		hasher hash_function() const {
			return hash_func;
		}
		key_equal key_eq() const {
			return hash_equal;
		}
	private:
		//aux function
		size_type get_next_prime(size_type n) {
			for (auto i = 0; i < prime_sz; ++i)
				if (prime[i]>n)
					return prime[i];
			return 0;
		}
	private:
		hasher hash_func;
		Extract_key get_key;
		KeyEqual hash_equal;
		Allocator alloc;
		vector<list<T,Allocator>> buckets;
		size_type sz;
		float maximum_load_factor;
	};

	template<typename T, typename Key, typename Extract_key, typename Hash, typename KeyEqual, typename Allocator>
	bool operator==(const hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>& lhs, 
		const hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return 0;
		auto iter1 = lhs.begin();
		auto iter2 = rhs.begin();
		while (iter1 != lhs.end()) {
			if (*iter1!= *iter2)
				return 0;
			++iter1;
			++iter2;
		}
		return 1;
	}

	template<typename T, typename Key, typename Extract_key, typename Hash, typename KeyEqual, typename Allocator>
	bool operator!=(const hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>& lhs,
		const hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T, typename Key, typename Extract_key, typename Hash, typename KeyEqual, typename Allocator>
	void swap(const hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>& lhs,
		const hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>& rhs) {
		lhs.swap(rhs);
	}


	template<typename T, typename Key, typename Extract_key, typename Hash, typename KeyEqual, typename Allocator>
	const size_t hash_table<T, Key, Extract_key, Hash, KeyEqual, Allocator>::prime[prime_sz] = {
		3u, 97u, 193u, 389u, 769u, 1543u, 3079u, 6151u, 12289u, 
		24593u, 49157u,98317u, 196613u, 393241u, 786433u, 1572869u, 
		3145739u, 6291469u, 12582917u,25165843u, 50331653u, 100663319u, 
		201326611u, 402653189u, 805306457u,1610612741u, 3221225473u, 4294967291u,
	};
}
#endif
