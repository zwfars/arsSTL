#ifndef UNORDERED_SET
#define UNORDERED_SET

#include<allocators>
#include"hash_table.h"
namespace arsSTL {
	template <class Key,
	class Hash = hash<Key>,
	class Pred = std::equal_to<Key>,
	class Allocator = std::allocator<Key> >
	class unordered_set
	{
	public:
		// types
		typedef Key                                         key_type;
		typedef Key                                         value_type;
		typedef Hash                                        hasher;
		typedef Pred                                        key_equal;
		typedef Allocator                                   allocator_type;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef typename allocator_type::reference          reference;
		typedef typename allocator_type::const_reference    const_reference;
		typedef /*implementation-defined*/                  size_type;
		typedef /*implementation-defined*/                  difference_type;

		typedef /*implementation-defined*/                  iterator;
		typedef /*implementation-defined*/                  const_iterator;
		typedef /*implementation-defined*/                  local_iterator;
		typedef /*implementation-defined*/                  const_local_iterator;

		// construct/destroy/copy
		explicit unordered_set(size_type n = implementation - defined,
			const hasher& hf = hasher(),
			const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type());
		template <class InputIterator>
		unordered_set(InputIterator f, InputIterator l,
			size_type n = see below,
			const hasher& hf = hasher(),
			const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type());
		unordered_set(const unordered_set&);
		unordered_set(unordered_set&&);
		explicit unordered_set(const Allocator&);
		unordered_set(const unordered_set&, const Allocator&);
		unordered_set(unordered_set&&, const Allocator&);
		unordered_set(initializer_list<value_type>,
			size_type = see below,
			const hasher& hf = hasher(),
			const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type());
		~unordered_set();
		unordered_set& operator=(const unordered_set&);
		unordered_set& operator=(unordered_set&&);
		unordered_set& operator=(initializer_list<value_type>);
		allocator_type get_allocator() const noexcept;

		// size and capacity
		bool      empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;

		// iterators
		iterator       begin() noexcept;
		const_iterator begin() const noexcept;
		iterator       end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;

		// modifiers
		template <class... Args> pair<iterator, bool> emplace(Args&&... args);
		template <class... Args> iterator emplace_hint(const_iterator position, Args&&... args);
		pair<iterator, bool> insert(const value_type& obj);
		pair<iterator, bool> insert(value_type&& obj);
		iterator insert(const_iterator hint, const value_type& obj);
		iterator insert(const_iterator hint, value_type&& obj);
		template <class InputIterator> void insert(InputIterator first, InputIterator last);
		void insert(initializer_list<value_type>);

		iterator erase(const_iterator position);
		size_type erase(const key_type& k);
		iterator erase(const_iterator first, const_iterator last);
		void clear() noexcept;

		void swap(unordered_set&);

		// observers
		hasher hash_function() const;
		key_equal key_eq() const;

		// lookup
		iterator       find(const key_type& k);
		const_iterator find(const key_type& k) const;
		size_type count(const key_type& k) const;
		std::pair<iterator, iterator> equal_range(const key_type& k);
		std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

		// bucket interface
		size_type bucket_count() const noexcept;
		size_type max_bucket_count() const noexcept;
		size_type bucket_size(size_type n) const;
		size_type bucket(const key_type& k) const;
		local_iterator begin(size_type n);
		const_local_iterator begin(size_type n) const;
		local_iterator end(size_type n);
		const_local_iterator end(size_type n) const;
		const_local_iterator cbegin(size_type n) const;
		const_local_iterator cend(size_type n) const;

		// hash policy
		float load_factor() const noexcept;
		float max_load_factor() const noexcept;
		void max_load_factor(float z);
		void rehash(size_type n);
		void reserve(size_type n);
	};
}

#endif
