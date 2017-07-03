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
		template<typename other1,typename other2>
		pair(const pair<other1, other2>& x) :first(x.first), seconde(x.second) {}
		//member
		first_type first;
		second_type second;

		pair& operator=(const pair& x) {
			first = x.first;
			second = x.second;
			return *this;
		}
	};

	//some function
	template<typename T1, typename T2>
	pair<T1,T2> make_pair(T1&& val1, T2&& val2) {
		return pair<T1,T2>(std::forward<T1>(val1), std::forward<T2>(val2));
	}

}


#endif
