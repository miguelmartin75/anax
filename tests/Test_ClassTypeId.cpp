///
/// anax tests
/// An open source C++ entity system.
///
/// Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///

#include <lest.hpp>

#include <anax/detail/ClassTypeId.hpp>

struct Type {};

const lest::test specification[] =
{
    CASE("Incremental IDs for types")
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

    // TODO: multi-threaded test (how?)
};

int main()
{
    return lest::run(specification);
}
