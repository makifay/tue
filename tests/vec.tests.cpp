//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//     Please report any bugs, typos, or suggestions to
//         https://github.com/Cincinesh/tue/issues

#include <tue/vec.hpp>
#include <mon/test_case.hpp>

namespace
{
    using namespace tue;

    TEST_CASE(default_constructor)
    {
        fvec4 v;
    }

    TEST_CASE(scalar_constructor)
    {
        CONST_OR_CONSTEXPR fvec4 v(1.2);
        test_assert(v[0] == 1.2f);
        test_assert(v[1] == 1.2f);
        test_assert(v[2] == 1.2f);
        test_assert(v[3] == 1.2f);
    }
}
