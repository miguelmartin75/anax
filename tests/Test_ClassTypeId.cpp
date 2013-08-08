#include "lest.hpp"

#include <anax/detail/ClassTypeId.hpp>

struct Type {};

const lest::test specification[] =
{
	"Incremental IDs for types", []
	{
		using namespace anax::detail;

		EXPECT(ClassTypeId<Type>::GetTypeId<bool>() == 0);
		EXPECT(ClassTypeId<Type>::GetTypeId<char>() == 1);
		EXPECT(ClassTypeId<Type>::GetTypeId<unsigned char>() == 2);
		EXPECT(ClassTypeId<Type>::GetTypeId<short>() == 3);
		EXPECT(ClassTypeId<Type>::GetTypeId<unsigned short>() == 4);
		EXPECT(ClassTypeId<Type>::GetTypeId<int>() == 5);
		EXPECT(ClassTypeId<Type>::GetTypeId<unsigned int>() == 6);
		EXPECT(ClassTypeId<Type>::GetTypeId<float>() == 7);
		EXPECT(ClassTypeId<Type>::GetTypeId<double>() == 8);
	}
};

int main()
{
	return lest::run(specification);
}