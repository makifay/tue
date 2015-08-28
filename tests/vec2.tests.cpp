//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//     Please report any bugs, typos, or suggestions to
//         https://github.com/Cincinesh/tue/issues

#include <tue/vec.hpp>
#include <mon/test_case.hpp>

#include <type_traits>
#include <tue/unused.hpp>

namespace
{
    using namespace tue;

    TEST_CASE(size)
    {
        test_assert(sizeof(fvec2) == sizeof(float) * 2);
        test_assert(sizeof(dvec2) == sizeof(double) * 2);
        test_assert(sizeof(ivec2) == sizeof(int) * 2);
        test_assert(sizeof(uvec2) == sizeof(unsigned int) * 2);
        test_assert(sizeof(bvec2) == sizeof(bool) * 2);
    }

    TEST_CASE(alignment)
    {
        test_assert(alignof(fvec2) == alignof(float));
        test_assert(alignof(dvec2) == alignof(double));
        test_assert(alignof(ivec2) == alignof(int));
        test_assert(alignof(uvec2) == alignof(unsigned int));
        test_assert(alignof(bvec2) == alignof(bool));
    }

    TEST_CASE(component_type)
    {
        test_assert((
            std::is_same<typename vec2<float>::component_type, float>::value));
        test_assert((
            std::is_same<typename fvec2::component_type, float>::value));
        test_assert((
            std::is_same<typename dvec2::component_type, double>::value));
        test_assert((
            std::is_same<typename ivec2::component_type, int>::value));
        test_assert((
            std::is_same<typename uvec2::component_type, unsigned int>::value));
        test_assert((
            std::is_same<typename bvec2::component_type, bool>::value));
    }

    TEST_CASE(component_count)
    {
        test_assert(vec2<float>::component_count == 2);
        test_assert(fvec2::component_count == 2);
        test_assert(dvec2::component_count == 2);
        test_assert(ivec2::component_count == 2);
        test_assert(uvec2::component_count == 2);
        test_assert(bvec2::component_count == 2);
    }

    TEST_CASE(default_constructor)
    {
        fvec2 v;
        unused(v);
    }

    TEST_CASE(scalar_constructor)
    {
        CONST_OR_CONSTEXPR fvec2 v(1.2);
        test_assert(v[0] == 1.2f);
        test_assert(v[1] == 1.2f);
    }

    TEST_CASE(individual_components_constructor)
    {
        CONST_OR_CONSTEXPR dvec2 v = { 1.2, 3.4 };
        test_assert(v[0] == 1.2);
        test_assert(v[1] == 3.4);
    }

    TEST_CASE(truncate_vec3_constructor)
    {
        CONST_OR_CONSTEXPR dvec2 v(dvec3(1.2, 3.4, 5.6));
        test_assert(v[0] == 1.2);
        test_assert(v[1] == 3.4);
    }

    TEST_CASE(truncate_vec4_constructor)
    {
        CONST_OR_CONSTEXPR dvec2 v(dvec4(1.2, 3.4, 5.6, 7.8));
        test_assert(v[0] == 1.2);
        test_assert(v[1] == 3.4);
    }

    TEST_CASE(explicit_conversion_constructor)
    {
        CONST_OR_CONSTEXPR dvec2 dv(1.2, 3.4);
        CONST_OR_CONSTEXPR fvec2 fv(dv);
        test_assert(fv[0] == 1.2f);
        test_assert(fv[1] == 3.4f);
    }

    TEST_CASE(implicit_conversion_operator)
    {
        CONST_OR_CONSTEXPR fvec2 fv(1.2f, 3.4f);
        CONST_OR_CONSTEXPR dvec2 dv = fv;
        test_assert(dv[0] == 1.2f);
        test_assert(dv[1] == 3.4f);
    }

    TEST_CASE(zero)
    {
        CONST_OR_CONSTEXPR auto v = fvec2::zero();
        test_assert(v == fvec2(0.0f, 0.0f));
    }

    TEST_CASE(x_axis)
    {
        CONST_OR_CONSTEXPR auto v = fvec2::x_axis();
        test_assert(v == fvec2(1.0f, 0.0f));
    }

    TEST_CASE(y_axis)
    {
        CONST_OR_CONSTEXPR auto v = fvec2::y_axis();
        test_assert(v == fvec2(0.0f, 1.0f));
    }

    TEST_CASE(x_y_z)
    {
        CONST_OR_CONSTEXPR dvec2 v(1.2, 3.4);
        CONST_OR_CONSTEXPR auto x = v.x();
        CONST_OR_CONSTEXPR auto y = v.y();
        test_assert(x == 1.2);
        test_assert(y == 3.4);
    }

    TEST_CASE(r_g_b)
    {
        CONST_OR_CONSTEXPR dvec2 v(1.2, 3.4);
        CONST_OR_CONSTEXPR auto r = v.r();
        CONST_OR_CONSTEXPR auto g = v.g();
        test_assert(r == 1.2);
        test_assert(g == 3.4);
    }

    TEST_CASE(xy_rg)
    {
        CONST_OR_CONSTEXPR dvec2 v(1.2, 3.4);
        CONST_OR_CONSTEXPR auto xy = v.xy();
        CONST_OR_CONSTEXPR auto rg = v.rg();
        test_assert(xy == dvec2(1.2, 3.4));
        test_assert(rg == dvec2(1.2, 3.4));
    }

    TEST_CASE(set_x_y)
    {
        dvec2 v(1.2, 3.4);
        v.set_x(5.6);
        v.set_y(7.8);
        test_assert(v[0] == 5.6);
        test_assert(v[1] == 7.8);
    }

    TEST_CASE(set_r_g)
    {
        dvec2 v(1.2, 3.4);
        v.set_r(5.6);
        v.set_g(7.8);
        test_assert(v[0] == 5.6);
        test_assert(v[1] == 7.8);
    }

    TEST_CASE(set_xy)
    {
        dvec2 v(1.2, 3.4);
        
        v.set_xy(5.6, 7.8);
        test_assert(v[0] == 5.6);
        test_assert(v[1] == 7.8);

        v.set_xy(dvec2(9.10, 11.12));
        test_assert(v[0] == 9.10);
        test_assert(v[1] == 11.12);
    }

    TEST_CASE(set_rg)
    {
        dvec2 v(1.2, 3.4);
        
        v.set_rg(5.6, 7.8);
        test_assert(v[0] == 5.6);
        test_assert(v[1] == 7.8);

        v.set_rg(dvec2(9.10, 11.12));
        test_assert(v[0] == 9.10);
        test_assert(v[1] == 11.12);
    }

    TEST_CASE(data)
    {
        const dvec2 cv(1.2);
        test_assert(cv.data() == static_cast<const void*>(&cv));

        dvec2 v;
        test_assert(v.data() == static_cast<void*>(&v));
    }

    TEST_CASE(subscript_operator)
    {
        CONST_OR_CONSTEXPR dvec2 cev(1.2, 3.4);
        CONST_OR_CONSTEXPR auto cev0 = cev[0];
        CONST_OR_CONSTEXPR auto cev1 = cev[1];
        test_assert(cev0 == 1.2);
        test_assert(cev1 == 3.4);

        const auto cv = cev;
        const auto& cv0 = cv[0];
        const auto& cv1 = cv[1];
        test_assert(&cv0 == cv.data() + 0);
        test_assert(&cv1 == cv.data() + 1);

        auto v = cev;
        auto& v0 = v[0];
        auto& v1 = v[1];
        test_assert(&v0 == v.data() + 0);
        test_assert(&v1 == v.data() + 1);
    }

    TEST_CASE(pre_increment_operator)
    {
        ivec2 v(1, 2);
        test_assert(&(++v) == &v);
        test_assert(v[0] == 2);
        test_assert(v[1] == 3);
    }

    TEST_CASE(post_increment_operator)
    {
        ivec2 v(1, 2);
        test_assert(v++ == ivec2(1, 2));
        test_assert(v[0] == 2);
        test_assert(v[1] == 3);
    }

    TEST_CASE(pre_decrement_operator)
    {
        ivec2 v(1, 2);
        test_assert(&(--v) == &v);
        test_assert(v[0] == 0);
        test_assert(v[1] == 1);
    }

    TEST_CASE(post_decrement_operator)
    {
        ivec2 v(1, 2);
        test_assert(v-- == ivec2(1, 2));
        test_assert(v[0] == 0);
        test_assert(v[1] == 1);
    }

    TEST_CASE(addition_assignment_operator)
    {
        dvec2 v1(1.2, 3.4);
        test_assert(&(v1 += 5) == &v1);
        test_assert(v1[0] == 1.2 + 5);
        test_assert(v1[1] == 3.4 + 5);

        dvec2 v2(1.2, 3.4);
        test_assert(&(v2 += ivec2(5, 6)) == &v2);
        test_assert(v2[0] == 1.2 + 5);
        test_assert(v2[1] == 3.4 + 6);
    }

    TEST_CASE(subtraction_assignment_operator)
    {
        dvec2 v1(1.2, 3.4);
        test_assert(&(v1 -= 5) == &v1);
        test_assert(v1[0] == 1.2 - 5);
        test_assert(v1[1] == 3.4 - 5);

        dvec2 v2(1.2, 3.4);
        test_assert(&(v2 -= ivec2(5, 6)) == &v2);
        test_assert(v2[0] == 1.2 - 5);
        test_assert(v2[1] == 3.4 - 6);
    }

    TEST_CASE(multiplication_assignment_operator)
    {
        dvec2 v1(1.2, 3.4);
        test_assert(&(v1 *= 5) == &v1);
        test_assert(v1[0] == 1.2 * 5);
        test_assert(v1[1] == 3.4 * 5);

        dvec2 v2(1.2, 3.4);
        test_assert(&(v2 *= ivec2(5, 6)) == &v2);
        test_assert(v2[0] == 1.2 * 5);
        test_assert(v2[1] == 3.4 * 6);
    }

    TEST_CASE(division_assignment_operator)
    {
        dvec2 v1(1.2, 3.4);
        test_assert(&(v1 /= 5) == &v1);
        test_assert(v1[0] == 1.2 / 5);
        test_assert(v1[1] == 3.4 / 5);

        dvec2 v2(1.2, 3.4);
        test_assert(&(v2 /= ivec2(5, 6)) == &v2);
        test_assert(v2[0] == 1.2 / 5);
        test_assert(v2[1] == 3.4 / 6);
    }

    TEST_CASE(modulo_assignment_operator)
    {
        vec2<long long> v1(10LL, 21LL);
        test_assert(&(v1 %= 9) == &v1);
        test_assert(v1[0] == 10LL % 9);
        test_assert(v1[1] == 21LL % 9);

        vec2<long long> v2(10LL, 21LL);
        test_assert(&(v2 %= ivec2(9, 8)) == &v2);
        test_assert(v2[0] == 10LL % 9);
        test_assert(v2[1] == 21LL % 8);
    }

    TEST_CASE(bitwise_and_assignment_operator)
    {
        vec2<long long> v1(12LL, 34LL);
        test_assert(&(v1 &= 56) == &v1);
        test_assert(v1[0] == (12LL & 56));
        test_assert(v1[1] == (34LL & 56));

        vec2<long long> v2(12LL, 34LL);
        test_assert(&(v2 &= ivec2(56, 78)) == &v2);
        test_assert(v2[0] == (12LL & 56));
        test_assert(v2[1] == (34LL & 78));
    }

    TEST_CASE(bitwise_or_assignment_operator)
    {
        vec2<long long> v1(12LL, 34LL);
        test_assert(&(v1 |= 56) == &v1);
        test_assert(v1[0] == (12LL | 56));
        test_assert(v1[1] == (34LL | 56));

        vec2<long long> v2(12LL, 34LL);
        test_assert(&(v2 |= ivec2(56, 78)) == &v2);
        test_assert(v2[0] == (12LL | 56));
        test_assert(v2[1] == (34LL | 78));
    }

    TEST_CASE(bitwise_xor_assignment_operator)
    {
        vec2<long long> v1(12LL, 34LL);
        test_assert(&(v1 ^= 56) == &v1);
        test_assert(v1[0] == (12LL ^ 56));
        test_assert(v1[1] == (34LL ^ 56));

        vec2<long long> v2(12LL, 34LL);
        test_assert(&(v2 ^= ivec2(56, 78)) == &v2);
        test_assert(v2[0] == (12LL ^ 56));
        test_assert(v2[1] == (34LL ^ 78));
    }

    TEST_CASE(bitwise_shift_left_assignment_operator)
    {
        vec2<long long> v1(12LL, 34LL);
        test_assert(&(v1 <<= 1) == &v1);
        test_assert(v1[0] == (12LL << 1));
        test_assert(v1[1] == (34LL << 1));

        vec2<long long> v2(12LL, 34LL);
        test_assert(&(v2 <<= ivec2(1, 2)) == &v2);
        test_assert(v2[0] == (12LL << 1));
        test_assert(v2[1] == (34LL << 2));
    }

    TEST_CASE(bitwise_shift_right_assignment_operator)
    {
        vec2<long long> v1(12LL, 34LL);
        test_assert(&(v1 >>= 1) == &v1);
        test_assert(v1[0] == (12LL >> 1));
        test_assert(v1[1] == (34LL >> 1));

        vec2<long long> v2(12LL, 34LL);
        test_assert(&(v2 >>= ivec2(1, 2)) == &v2);
        test_assert(v2[0] == (12LL >> 1));
        test_assert(v2[1] == (34LL >> 2));
    }

    TEST_CASE(unary_plus_operator)
    {
        CONST_OR_CONSTEXPR auto v = +dvec2(1.2, 3.4);
        test_assert(v == dvec2(+1.2, +3.4));
    }

    TEST_CASE(unary_minus_operator)
    {
        CONST_OR_CONSTEXPR auto v = -dvec2(1.2, 3.4);
        test_assert(v == dvec2(-1.2, -3.4));
    }

    TEST_CASE(bitwise_not_operator)
    {
        CONST_OR_CONSTEXPR auto v = ~ivec2(1, 2);
        test_assert(v == ivec2(~1, ~2));
    }

    TEST_CASE(logical_not_operator)
    {
        CONST_OR_CONSTEXPR auto v = !ivec2(0, 1);
        test_assert(v == ivec2(!0, !1));
    }

    TEST_CASE(equality_operator)
    {
        CONST_OR_CONSTEXPR fvec2 v1(1.2f, 3.4f);
        CONST_OR_CONSTEXPR dvec2 v2(1.2f, 3.4f);
        CONST_OR_CONSTEXPR dvec2 v3(1.2f, 0.0f);
        CONST_OR_CONSTEXPR dvec2 v4(0.0f, 3.4f);
        CONST_OR_CONSTEXPR auto result1 = (v1 == v2);
        CONST_OR_CONSTEXPR auto result2 = (v1 == v3);
        CONST_OR_CONSTEXPR auto result3 = (v1 == v4);
        test_assert(result1 == true);
        test_assert(result2 == false);
        test_assert(result3 == false);
    }

    TEST_CASE(inequality_operator)
    {
        CONST_OR_CONSTEXPR fvec2 v1(1.2f, 3.4f);
        CONST_OR_CONSTEXPR dvec2 v2(1.2f, 3.4f);
        CONST_OR_CONSTEXPR dvec2 v3(1.2f, 0.0f);
        CONST_OR_CONSTEXPR dvec2 v4(0.0f, 3.4f);
        CONST_OR_CONSTEXPR auto result1 = (v1 != v2);
        CONST_OR_CONSTEXPR auto result2 = (v1 != v3);
        CONST_OR_CONSTEXPR auto result3 = (v1 != v4);
        test_assert(result1 == false);
        test_assert(result2 == true);
        test_assert(result3 == true);
    }
}
