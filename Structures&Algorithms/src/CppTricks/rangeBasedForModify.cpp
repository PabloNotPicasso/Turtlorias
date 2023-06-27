#include <bits/stdc++.h>
using namespace std;

template <typename Iterator>
class IteratorRange
{
public:
	IteratorRange(const Iterator b, const Iterator e)
		: m_begin(b)
		, m_end(e)
	{}

	Iterator begin() const {
		return m_begin;
	}

	Iterator end() const {
		return m_end;
	}

	Iterator m_begin, m_end;
};

template <typename Container>
auto Head(Container& v, size_t count)
{
	return IteratorRange{
		v.begin(),
		next(v.begin(), min(count, v.size() ) )
	};
}

int main()
{
	const vector<int> v{1,2,3,4,5,6,7};
	for( auto i : Head(v, 3) )
	{
		cout << i << " ";
	}
	return 0;
}