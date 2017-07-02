ifndef UNORDERED_SET
#define UNORDERED_SET

#include<allocators>
#include"hash_table.h"

namespace arsSTL {

	template<typename T>
	struct get_key {
		T operator()(T x) {
			return x;
		}
	};

	template <class Key, class Hash = hash<Key>,
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
		using Container = hash_table<Key, Key, get_key<Key>,Hash, Pred, Allocator>;

		// the syntax
		using iterator =  typename Container::iterator;
		using const_iterator =  typename Container::const_iterator;
		using local_iterator =  typename Container::local_iterator;
		using const_local_iterator = typename Container::const_local_iterator;

		// construct/destroy/copy
		explicit unordered_set(size_type n, const hasher& hf = hasher(), const key_equal& eql = key_equal(),
			const allocator_type& a = allocator_type()) :ht(hf, get_key<Key>(), eql, n, a) {}
		//template <class InputIterator>
		//unordered_set(InputIterator f, InputIterator l,
		//	size_type n,
		//	const hasher& hf = hasher(),
		//	const key_equal& eql = key_equal(),
		//	const allocator_type& a = allocator_type());
		//unordered_set(const unordered_set&);
		//unordered_set(unordered_set&&);
		//explicit unordered_set(const Allocator&);
		//unordered_set(const unordered_set&, const Allocator&);
		//unordered_set(unordered_set&&, const Allocator&);
		//unordered_set(initializer_list<value_type>,
		//	size_type = see below,
		//	const hasher& hf = hasher(),
		//	const key_equal& eql = key_equal(),
		//	const allocator_type& a = allocator_type());
		//~unordered_set();
		//unordered_set& operator=(const unordered_set&);
		//unordered_set& operator=(unordered_set&&);
		//unordered_set& operator=(initializer_list<value_type>);
		//allocator_type get_allocator() const noexcept;

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
		//pair<iterator, bool> insert(value_type&& obj);
		//iterator insert(const_iterator hint, const value_type& obj);
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
		//iterator       find(const key_type& k);
		//const_iterator find(const key_type& k) const;
		//size_type count(const key_type& k) const;
		//std::pair<iterator, iterator> equal_range(const key_type& k);
		//std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

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
		private:
			Container ht;
	};


}

#endif
