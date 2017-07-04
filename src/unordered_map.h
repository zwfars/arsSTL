#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include<allocators>
#include"hash_table.h"
#include"pair.h"

namespace arsSTL {
	
	struct map_key {
		template< typename T >
		typename T::first_type const& operator()(const T& x) const{
			return x.first;
		}
	};
	template <class Key,class T,class Hash =  std::hash<Key>,
	class Pred = std::equal_to<Key>, class Allocator = std::allocator<pair<const Key,T>>>
	class unordered_map{
	public:
		// types
		using key_type = Key;
		using value_type = pair<const Key, T>;
		using hasher = Hash;
		using key_equal = Pred;
		using allocator_type = Allocator;
		using pointer = typename allocator_type::pointer;
		using const_poniter = typename allocator_type::const_pointer;
		using reference = typename allocator_type::reference;
		using const_reference = typename allocator_type::const_reference;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using Container = hash_table<pair<const Key, T>, Key, map_key, Hash, Pred, Allocator>;
		using iterator = typename Container::iterator;
		using const_iterator = typename Container::const_iterator;
		using local_iterator = typename Container::local_iterator;
		using const_local_iterator = typename Container::const_local_iterator;
		using mapped_type = T;

		//// construct/destroy/copy
		explicit unordered_map(size_type buck_num = 0, const hasher& hf = hasher(),
			const key_equal& eql = key_equal(), const allocator_type& a = allocator_type()):ht(hf,map_key(), eql, buck_num, a) {}
		template <class InputIterator>
		unordered_map(InputIterator f, InputIterator l,size_type buck_num = 0,
			const hasher& hf = hasher(),const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type()) : ht(hf, map_key(), eql, buck_num, a){
			insert(f, l);
		}
		unordered_map(const unordered_map& x) {
			ht.insert(x.begin(), x.end());
		}
		unordered_map(unordered_map&& x) {
			swap(x);
		}
		explicit unordered_map(const Allocator& a) :ht(hasher(), map_key(), key_equal(), 0, a) {}
		unordered_map(const unordered_map& x, const Allocator& a) :ht(hasher(), map_key(), key_equal(), 0, a) {
			insert(x.begin(), x.end());
		}
		unordered_map(unordered_map&& x, const Allocator& a):ht(hasher(), map_key(), key_equal(), 0, a) {
			swap(x);
		}
		unordered_map(std::initializer_list<value_type> x, size_type buck_num= 0,
			const hasher& hf = hasher(), const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type()) :ht(hf, map_key(), eql, buck_num, a) {
			insert(x.begin(), x.end());
		}
		~unordered_map() = default;
		unordered_map& operator=(const unordered_map& x) {
			clear();
			insert(x.begin(), x.end());
			return *this;
		}
		unordered_map& operator=(unordered_map&& x) {
			clear();
			swap(x);
			return *this;
		}
		unordered_map& operator=(std::initializer_list<value_type> x) {
			clear();
			insert(x.begin(), x.end());
			return *this;
		}
		allocator_type get_allocator() const noexcept {
			return ht.get_allocator();
		}

		//// size and capacity
		bool empty() const noexcept {
			return ht.empty();
		}
		size_type size() const noexcept {
			return ht.size();
		}
		size_type max_size() const noexcept {
			return ht.max_size();
		}

		//// iterators
		iterator       begin() noexcept {
			return ht.begin();
		}
		const_iterator begin() const noexcept {
			return ht.begin();
		}
		iterator       end() noexcept {
			return ht.end();
		}
		const_iterator end() const noexcept {
			return ht.end();
		}
		const_iterator cbegin() const noexcept {
			return ht.cbegin();
		}
		const_iterator cend() const noexcept {
			return ht.cend();
		}

		//// modifiers
		template <class... Args> 
		pair<iterator, bool> emplace(Args&&... args) {
			return ht.emplace(std::forward<Args>(args)...);
		}
		template <class... Args> 
		iterator emplace_hint(const_iterator position, Args&&... args) {
			return ht.emplace_hint(position, std::forward<Args>(args)...);
		}
		pair<iterator, bool> insert(const value_type& obj) {
			return ht.insert(obj);
		}
		template <class P> 
		pair<iterator, bool> insert(P&& obj) {
			return ht.insert(std::forward<P>(obj));
		}
		iterator insert(const_iterator hint, const value_type& obj) {
			return ht.insert(hint, obj);
		}
		template <class P> iterator insert(const_iterator hint, P&& obj) {
			return ht.insert(hint, std::forward<P>(obj));
		}
		template <class InputIterator> 
		void insert(InputIterator first, InputIterator last) {
			ht.insert(first, last);
		}
		void insert(std::initializer_list<value_type> x) {
			ht.insert(x);
		}

		iterator erase(const_iterator position) {
			return ht.erase(position);
		}
		size_type erase(const key_type& k) {
			return ht.erase(k);
		}
		iterator erase(const_iterator first, const_iterator last) {
			return ht.erase(first, last);
		}
		void clear() noexcept {
			ht.clear();
		}

		void swap(unordered_map& x) {
			ht.swap(x.ht);
		}


		// observers
		hasher hash_function() const {
			return ht.hash_function()
		}
		key_equal key_eq() const {
			return ht.key_eq();
		}

		//// lookup
		iterator find(const key_type& k) {
			return ht.find(k);
		}
		const_iterator find(const key_type& k) const {
			return ht.find(k);
		}
		size_type count(const key_type& k) const {
			return ht.count(k);
		}
		std::pair<iterator, iterator> equal_range(const key_type& k) {
			return ht.equal_range(k);
		}
		std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			return ht.equal_range(k);
		}
		mapped_type& operator[](const key_type& k) {
			auto iter = find(k);
			mapped_type tem = mapped_type();
			if (iter == end()) {
				auto tet = insert({ k,tem });
				return tet.first->second;
			}
			return iter->second;
		}
		mapped_type& operator[](key_type&& k) {
			auto iter = find(k);
			mapped_type tem = mapped_type();
			if (iter == end()) {
				auto tet = insert({std::move(k),tem });
				return tet.first->second;
			}
			return iter->second;
		}
		
		mapped_type& at(const key_type& k) {
			return this->operator[](k);
		}
		const mapped_type& at(const key_type& k) const {
			return this->operator[](k);
		}

		//// bucket interface
		size_type bucket_count() const noexcept {
			return ht.bucket_count();
		}
		size_type max_bucket_count() const noexcept {
			return ht.max_bucket_count();
		}
		size_type bucket_size(size_type n) const {
			return ht.bucket_size();
		}
		size_type bucket(const key_type& k) const {
			return ht.bucket(k);
		}
		local_iterator begin(size_type n) {
			return ht.begin(n);
		}
		const_local_iterator begin(size_type n) const {
			return ht.begin(n);
		}
		local_iterator end(size_type n) {
			return ht.end(n);
		}
		const_local_iterator end(size_type n) const {
			return ht.end(n);
		}
		const_local_iterator cbegin(size_type n) const {
			return ht.cbegin(n);
		}
		const_local_iterator cend(size_type n) const {
			return ht.cenc(n);
		}
		//// hash policy
		float load_factor() const noexcept {
			return ht.load_factor();
		}
		float max_load_factor() const noexcept {
			return ht.max_load_factor();
		}
		void max_load_factor(float z) {
			ht.max_load_factor(z);
		}
		void rehash(size_type n) {
			ht.rehash(n);
		}
		void reserve(size_type n) {
			ht.reserve(n);
		}
		private:
			Container ht;

	};
}

#endif
