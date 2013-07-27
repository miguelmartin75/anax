#include "lest.hpp"

#include "anax/detail/ClassTypeId.hpp"

const lest::test specification[] =
{
	"Incremental IDs for types (succeed)", []
	{
		using anax::detail;

		EXPECT(ClassTypeId<bool>::GetTypeId() == 0);
		EXPECT(ClassTypeId<char>::GetTypeId() == 1);
		EXPECT(ClassTypeId<unsigned char>::GetTypeId() == 2);
		EXPECT(ClassTypeId<short>::GetTypeId() == 3);
		EXPECT(ClassTypeId<unsigned short>::GetTypeId() == 4);
		EXPECT(ClassTypeId<int>::GetTypeId() == 5);
		EXPECT(ClassTypeId<unsigned int>::GetTypeId() == 6);
		EXPECT(ClassTypeId<float>::GetTypeId() == 7);
		EXPECT(ClassTypeId<double>::GetTypeId() == 8);
	}
};

int main()
{
	return lest::run(specification);
}