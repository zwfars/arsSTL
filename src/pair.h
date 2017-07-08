#ifndef PAIR_H
#define PAIR_H

namespace arsSTL{
	template<typename T1,typename T2>
	struct pair {
		using first_type = T1;
		using second_type = T2;
		
		constexpr pair() :first(), second() {}
		constexpr pair(const T1& val1, const T2& val2) : first(val1), second(val2) {}
		pair(const pair& x) :first(x.first), second(x.second) {}
		pair(const pair&& x) :first(std::move(x.first)), second(std::move(x.second)) {}
		template< class U1, class U2 >
		pair(U1&& x, U2&& y) : first(std::forward<U1>(x)), second(std::forward<U2>(y)) {}
		template<typename other1,typename other2>
		pair(const pair<other1, other2>& x) :first(x.first), second(x.second) {}
		//member
		first_type first;
		second_type second;

		pair& operator=(const pair& x) {
			first = x.first;
			second = x.second;
			return *this;
		}

		template< class U1, class U2 >
		pair& operator=(const pair<U1, U2>& other) {
			first = other.first;
			second = other.second;
			return *this;
		}

		template< class U1, class U2 >
		pair& operator=(pair<U1, U2>&& other) {
			first = other.first;
			second = other.second;
			return *this;
		}
		
	};

	//some function
	template<typename T1, typename T2>
	pair<T1,T2> make_pair(T1&& val1, T2&& val2) {
		return pair<T1,T2>(std::forward<T1>(val1), std::forward<T2>(val2));
	}

	template< class T1, class T2 >
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs.first == rhs.first) && (lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first ? 1 : (lhs.first == rhs.first&&lhs.second < rhs.second);
	}
	template< class T1, class T2 >
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return rhs<lhs;
	}

	template< class T1, class T2 >
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs > rhs);
	}
	
	template< class T1, class T2 >
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}
	

}


#endif
