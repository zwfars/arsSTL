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

		//// construct/destroy/copy
		explicit unordered_map(size_type buck_num = 0, const hasher& hf = hasher(),
			const key_equal& eql = key_equal(), const allocator_type& a = allocator_type()):ht(hf,map_key(), eql, buck_num, a) {}
		//template <class InputIterator>
		//unordered_map(InputIterator f, InputIterator l,
		//	size_type n = see below,
		//	const hasher& hf = hasher(),
		//	const key_equal& eql = key_equal(),
		//	const allocator_type& a = allocator_type());
		//unordered_map(const unordered_map&);
		//unordered_map(unordered_map&&);
		//explicit unordered_map(const Allocator&);
		//unordered_map(const unordered_map&, const Allocator&);
		//unordered_map(unordered_map&&, const Allocator&);
		//unordered_map(initializer_list<value_type>,
		//	size_type = see below,
		//	const hasher& hf = hasher(),
		//	const key_equal& eql = key_equal(),
		//	const allocator_type& a = allocator_type());
		//~unordered_map();
		//unordered_map& operator=(const unordered_map&);
		//unordered_map& operator=(unordered_map&&);
		//unordered_map& operator=(initializer_list<value_type>);
		//allocator_type get_allocator() const noexcept;

		//// size and capacity
		bool empty() const noexcept {
			return ht.empty();
		}
		//size_type size() const noexcept;
		//size_type max_size() const noexcept;

		//// iterators
		//iterator       begin() noexcept;
		//const_iterator begin() const noexcept;
		//iterator       end() noexcept;
		//const_iterator end() const noexcept;
		//const_iterator cbegin() const noexcept;
		//const_iterator cend() const noexcept;

		//// modifiers
		//template <class... Args> pair<iterator, bool> emplace(Args&&... args);
		//template <class... Args> iterator emplace_hint(const_iterator position, Args&&... args);
		//pair<iterator, bool> insert(const value_type& obj);
		//template <class P> pair<iterator, bool> insert(P&& obj);
		//iterator insert(const_iterator hint, const value_type& obj);
		//template <class P> iterator insert(const_iterator hint, P&& obj);
		//template <class InputIterator> void insert(InputIterator first, InputIterator last);
		//void insert(initializer_list<value_type>);

		//iterator erase(const_iterator position);
		//size_type erase(const key_type& k);
		//iterator erase(const_iterator first, const_iterator last);
		//void clear() noexcept;

		//void swap(unordered_map&);


		//// observers
		//hasher hash_function() const;
		//key_equal key_eq() const;

		//// lookup
		//iterator find(const key_type& k);
		//const_iterator find(const key_type& k) const;
		//size_type count(const key_type& k) const;
		//std::pair<iterator, iterator>
		//	equal_range(const key_type& k);
		//std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
		//mapped_type& operator[](const key_type& k);
		//mapped_type& operator[](key_type&& k);
		//mapped_type& at(const key_type& k);
		//const mapped_type& at(const key_type& k) const;

		//// bucket interface
		//size_type bucket_count() const noexcept;
		//size_type max_bucket_count() const noexcept;
		//size_type bucket_size(size_type n) const;
		//size_type bucket(const key_type& k) const;
		//local_iterator begin(size_type n);
		//const_local_iterator begin(size_type n) const;
		//local_iterator end(size_type n);
		//const_local_iterator end(size_type n) const;
		//const_local_iterator cbegin(size_type n) const;
		//const_local_iterator cend(size_type n) const;
		//// hash policy
		//float load_factor() const noexcept;
		//float max_load_factor() const noexcept;
		//void max_load_factor(float z);
		//void rehash(size_type n);
		//void reserve(size_type n);
		private:
			Container ht;

	};
}

#endif
