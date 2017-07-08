#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include<allocators>
#include"hash_table.h"

namespace arsSTL {

	struct get_key {
		template<typename T>
		T operator()(T x) {
			return x;
		}
	};

	template <class Key, class Hash = std::hash<Key>,
	class Pred = std::equal_to<Key>,class Allocator = std::allocator<Key> >
	class unordered_set
	{
	public:
		// types
		using key_type = Key;
		using value_type = Key;
		using hasher = Hash;
		using key_equal = Pred;
		using allocator_type = Allocator;
		using pointer = typename allocator_type::pointer;
		using const_pointer =  typename allocator_type::const_pointer;
		using refernece = typename allocator_type::reference;
		using const_reference =  typename allocator_type::const_reference;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using Container = hash_table<Key, Key, get_key,Hash, Pred, Allocator>;

		// the syntax
		using iterator =  typename Container::const_iterator;
		using const_iterator =  typename Container::const_iterator;
		using local_iterator =  typename Container::local_iterator;
		using const_local_iterator = typename Container::const_local_iterator;

		// construct/destroy/copy
		explicit unordered_set(size_type buck_num = 0, const hasher& hf = hasher(), const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type()) :ht(hf, get_key(), eql, buck_num, a) {}
		template <class InputIterator>
		unordered_set(InputIterator f, InputIterator l,size_type buck_num=0,const hasher& hf = hasher(),
			const key_equal& eql = key_equal(), const allocator_type& a = allocator_type()) : ht(hf, get_key(), eql, buck_num, a){
			insert(f, l);
		}
		unordered_set(const unordered_set& x){
			insert(x.begin(), x.end());
		}
		unordered_set(unordered_set&& x) {
			swap(x);
		}
		explicit unordered_set(const Allocator& a) :ht(hasher(), get_key(), key_equal(), 0, a) {}
		unordered_set(const unordered_set& x, const Allocator& a) :ht(hasher(), get_key(), key_equal(), 0, a) {
			insert(x.begin(), x.end());
		}
		unordered_set(unordered_set&& x, const Allocator& a) :ht(hasher(), get_key(), key_equal(), 0, a) {
			swap(x);
		}
		
		unordered_set(std::initializer_list<value_type> x, size_type buck_num = 0, const hasher& hf = hasher(),
			const key_equal& eql = key_equal(), const allocator_type& a = allocator_type()) :
			ht(hf, get_key(), eql, buck_num, a) {
			insert(x.begin(), x.end());
		}

		~unordered_set() = default;

		unordered_set& operator=(const unordered_set& x) {
			clear();
			insert(x.begin(), x.end());
			return *this;
		}
		unordered_set& operator=(unordered_set&& x) {
			clear();
			swap(x);
			return *this;
		}
		unordered_set& operator=(std::initializer_list<value_type> x) {
			clear();
			ht.insert(x.begin(), x.end());
			return *this;
		}
		
		allocator_type get_allocator() const noexcept {
			return ht.get_allocator();
		}

		//// size and capacity
		bool      empty() const noexcept {
			return ht.empty();
		}
		size_type size() const noexcept {
			return ht.size();
		}
		size_type max_size() const noexcept {
			return ht.max_size();
		}

	    //iterators
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
			return ht.emplace(std::forward(Args)(args)...);
		}
		template <class... Args> 
		iterator emplace_hint(const_iterator position, Args&&... args) {
			return ht.emplace_hint(position, std::forward<Args>(args)...);
		}
		pair<iterator, bool> insert(const value_type& obj) {
			return ht.insert(obj);
		}
		pair<iterator, bool> insert(value_type&& obj) {
			return ht.insert(std::forward<value_type>(obj));
		}
		iterator insert(const_iterator hint, const value_type& obj) {
			return ht.insert(hint, obj);
		}
		iterator insert(const_iterator hint, value_type&& obj) {
			return ht.insert(hint, std::forward<value_type>(obj));
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

		void swap(unordered_set& x) {
			ht.swap(x.ht);
		}

		//// observers
		hasher hash_function() const {
			return ht.hash_function();
		}
		key_equal key_eq() const {
			return ht.key_eq();
		}

		//// lookup
		iterator       find(const key_type& k) {
			return ht.find(k);
		}
		const_iterator find(const key_type& k) const {
			return ht.find(k);
		}
		size_type count(const key_type& k) const {
			return ht.count(k);
		}
		pair<iterator, iterator> equal_range(const key_type& k) {
			return ht.equal_range(k);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			return ht.equal_range(k);
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
			return ht.cend();
		}

		//// hash policy
		float load_factor() const noexcept {
			return ht.load_factor();
		}
		float max_load_factor() const noexcept {
			return ht.max_load_factor();
		}
		void max_load_factor(float z) {
			ht.maximum_load_factor(z);
		}
		void rehash(size_type n) {
			ht.rehash(n);
		}
		void reserve(size_type n) {
			ht.reserve(n);
		}
		const Container& get_constainer() const{
			return ht;
		}
		private:
			Container ht;
	};

	template <class Key, class Hash,class Pred , class Allocator>
	bool operator==(const unordered_set<Key, Hash, Pred, Allocator>&lhs, const unordered_set<Key, Hash, Pred, Allocator>&rhs) {
		return lhs.get_constainer() == rhs.get_constainer();
	}
	template <class Key, class Hash, class Pred, class Allocator>
	bool operator!=(const unordered_set<Key, Hash, Pred, Allocator>&lhs, const unordered_set<Key, Hash, Pred, Allocator>&rhs) {
		return !(lhs==rhs);
	}
	template <class Key, class Hash, class Pred, class Allocator>
	void swap(const unordered_set<Key, Hash, Pred, Allocator>&lhs, const unordered_set<Key, Hash, Pred, Allocator>&rhs) {
		lhs.swap(rhs);
	}



}

#endif
