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
        test_assert(sizeof(fvec3) == sizeof(float) * 3);
        test_assert(sizeof(dvec3) == sizeof(double) * 3);
        test_assert(sizeof(ivec3) == sizeof(int) * 3);
        test_assert(sizeof(uvec3) == sizeof(unsigned int) * 3);
        test_assert(sizeof(bvec3) == sizeof(bool) * 3);
    }

    TEST_CASE(alignment)
    {
        test_assert(alignof(fvec3) == alignof(float));
        test_assert(alignof(dvec3) == alignof(double));
        test_assert(alignof(ivec3) == alignof(int));
        test_assert(alignof(uvec3) == alignof(unsigned int));
        test_assert(alignof(bvec3) == alignof(bool));
    }

    TEST_CASE(component_type)
    {
        test_assert((
            std::is_same<typename vec3<float>::component_type, float>::value));
        test_assert((
            std::is_same<typename fvec3::component_type, float>::value));
        test_assert((
            std::is_same<typename dvec3::component_type, double>::value));
        test_assert((
            std::is_same<typename ivec3::component_type, int>::value));
        test_assert((
            std::is_same<typename uvec3::component_type, unsigned int>::value));
        test_assert((
            std::is_same<typename bvec3::component_type, bool>::value));
    }

    TEST_CASE(component_count)
    {
        test_assert(vec3<float>::component_count == 3);
        test_assert(fvec3::component_count == 3);
        test_assert(dvec3::component_count == 3);
        test_assert(ivec3::component_count == 3);
        test_assert(uvec3::component_count == 3);
        test_assert(bvec3::component_count == 3);
    }

    TEST_CASE(default_constructor)
    {
        fvec3 v;
        unused(v);
    }

    TEST_CASE(scalar_constructor)
    {
        CONST_OR_CONSTEXPR fvec3 v(1.2);
        test_assert(v[0] == 1.2f);
        test_assert(v[1] == 1.2f);
        test_assert(v[2] == 1.2f);
    }

    TEST_CASE(individual_components_constructor)
    {
        CONST_OR_CONSTEXPR dvec3 v = { 1.2, 3.4, 5.6 };
        test_assert(v[0] == 1.2);
        test_assert(v[1] == 3.4);
        test_assert(v[2] == 5.6);
    }

    TEST_CASE(extend_vec2_constructor)
    {
        CONST_OR_CONSTEXPR dvec3 v = { { 1.2, 3.4 }, 5.6 };
        test_assert(v[0] == 1.2);
        test_assert(v[1] == 3.4);
        test_assert(v[2] == 5.6);
    }

    TEST_CASE(truncate_vec4_constructor)
    {
        CONST_OR_CONSTEXPR dvec3 v(dvec4(1.2, 3.4, 5.6, 7.8));
        test_assert(v[0] == 1.2);
        test_assert(v[1] == 3.4);
        test_assert(v[2] == 5.6);
    }

    TEST_CASE(explicit_conversion_constructor)
    {
        CONST_OR_CONSTEXPR dvec3 dv(1.2, 3.4, 5.6);
        CONST_OR_CONSTEXPR fvec3 fv(dv);
        test_assert(fv[0] == 1.2f);
        test_assert(fv[1] == 3.4f);
        test_assert(fv[2] == 5.6f);
    }

    TEST_CASE(implicit_conversion_operator)
    {
        CONST_OR_CONSTEXPR fvec3 fv(1.2f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 dv = fv;
        test_assert(dv[0] == 1.2f);
        test_assert(dv[1] == 3.4f);
        test_assert(dv[2] == 5.6f);
    }

    TEST_CASE(zero)
    {
        CONST_OR_CONSTEXPR auto v = fvec3::zero();
        test_assert(v == fvec3(0.0f, 0.0f, 0.0f));
    }

    TEST_CASE(x_axis)
    {
        CONST_OR_CONSTEXPR auto v = fvec3::x_axis();
        test_assert(v == fvec3(1.0f, 0.0f, 0.0f));
    }

    TEST_CASE(y_axis)
    {
        CONST_OR_CONSTEXPR auto v = fvec3::y_axis();
        test_assert(v == fvec3(0.0f, 1.0f, 0.0f));
    }

    TEST_CASE(z_axis)
    {
        CONST_OR_CONSTEXPR auto v = fvec3::z_axis();
        test_assert(v == fvec3(0.0f, 0.0f, 1.0f));
    }

    TEST_CASE(x_y_z)
    {
        CONST_OR_CONSTEXPR dvec3 v(1.2, 3.4, 5.6);
        CONST_OR_CONSTEXPR auto x = v.x();
        CONST_OR_CONSTEXPR auto y = v.y();
        CONST_OR_CONSTEXPR auto z = v.z();
        test_assert(x == 1.2);
        test_assert(y == 3.4);
        test_assert(z == 5.6);
    }

    TEST_CASE(r_g_b)
    {
        CONST_OR_CONSTEXPR dvec3 v(1.2, 3.4, 5.6);
        CONST_OR_CONSTEXPR auto r = v.r();
        CONST_OR_CONSTEXPR auto g = v.g();
        CONST_OR_CONSTEXPR auto b = v.b();
        test_assert(r == 1.2);
        test_assert(g == 3.4);
        test_assert(b == 5.6);
    }

    TEST_CASE(xy_rg)
    {
        CONST_OR_CONSTEXPR dvec3 v(1.2, 3.4, 5.6);
        CONST_OR_CONSTEXPR auto xy = v.xy();
        CONST_OR_CONSTEXPR auto rg = v.rg();
        test_assert(xy == dvec2(1.2, 3.4));
        test_assert(rg == dvec2(1.2, 3.4));
    }

    TEST_CASE(xyz_rgb)
    {
        CONST_OR_CONSTEXPR dvec3 v(1.2, 3.4, 5.6);
        CONST_OR_CONSTEXPR auto xyz = v.xyz();
        CONST_OR_CONSTEXPR auto rgb = v.rgb();
        test_assert(xyz == dvec3(1.2, 3.4, 5.6));
        test_assert(rgb == dvec3(1.2, 3.4, 5.6));
    }

    TEST_CASE(set_x_y_z)
    {
        dvec3 v(1.2, 3.4, 5.6);
        v.set_x(7.8);
        v.set_y(9.10);
        v.set_z(11.12);
        test_assert(v[0] == 7.8);
        test_assert(v[1] == 9.10);
        test_assert(v[2] == 11.12);
    }

    TEST_CASE(set_r_g_b)
    {
        dvec3 v(1.2, 3.4, 5.6);
        v.set_r(7.8);
        v.set_g(9.10);
        v.set_b(11.12);
        test_assert(v[0] == 7.8);
        test_assert(v[1] == 9.10);
        test_assert(v[2] == 11.12);
    }

    TEST_CASE(set_xy)
    {
        dvec3 v(1.2, 3.4, 5.6);
        
        v.set_xy(7.8, 9.10);
        test_assert(v[0] == 7.8);
        test_assert(v[1] == 9.10);
        test_assert(v[2] == 5.6);

        v.set_xy(dvec2(11.12, 13.14));
        test_assert(v[0] == 11.12);
        test_assert(v[1] == 13.14);
        test_assert(v[2] == 5.6);
    }

    TEST_CASE(set_rg)
    {
        dvec3 v(1.2, 3.4, 5.6);
        
        v.set_rg(7.8, 9.10);
        test_assert(v[0] == 7.8);
        test_assert(v[1] == 9.10);
        test_assert(v[2] == 5.6);

        v.set_rg(dvec2(11.12, 13.14));
        test_assert(v[0] == 11.12);
        test_assert(v[1] == 13.14);
        test_assert(v[2] == 5.6);
    }

    TEST_CASE(set_xyz)
    {
        dvec3 v(1.2, 3.4, 5.6);
        
        v.set_xyz(7.8, 9.10, 11.12);
        test_assert(v[0] == 7.8);
        test_assert(v[1] == 9.10);
        test_assert(v[2] == 11.12);

        v.set_xyz(dvec2(13.14, 15.16), 17.18);
        test_assert(v[0] == 13.14);
        test_assert(v[1] == 15.16);
        test_assert(v[2] == 17.18);

        v.set_xyz(dvec3(19.20, 21.22, 23.24));
        test_assert(v[0] == 19.20);
        test_assert(v[1] == 21.22);
        test_assert(v[2] == 23.24);
    }

    TEST_CASE(set_rgb)
    {
        dvec3 v(1.2, 3.4, 5.6);
        
        v.set_rgb(7.8, 9.10, 11.12);
        test_assert(v[0] == 7.8);
        test_assert(v[1] == 9.10);
        test_assert(v[2] == 11.12);

        v.set_rgb(dvec2(13.14, 15.16), 17.18);
        test_assert(v[0] == 13.14);
        test_assert(v[1] == 15.16);
        test_assert(v[2] == 17.18);

        v.set_rgb(dvec3(19.20, 21.22, 23.24));
        test_assert(v[0] == 19.20);
        test_assert(v[1] == 21.22);
        test_assert(v[2] == 23.24);
    }

    TEST_CASE(data)
    {
        const dvec3 cv(1.2);
        test_assert(cv.data() == static_cast<const void*>(&cv));

        dvec3 v;
        test_assert(v.data() == static_cast<void*>(&v));
    }

    TEST_CASE(subscript_operator)
    {
        CONST_OR_CONSTEXPR dvec3 cev(1.2, 3.4, 5.6);
        CONST_OR_CONSTEXPR auto cev0 = cev[0];
        CONST_OR_CONSTEXPR auto cev1 = cev[1];
        CONST_OR_CONSTEXPR auto cev2 = cev[2];
        test_assert(cev0 == 1.2);
        test_assert(cev1 == 3.4);
        test_assert(cev2 == 5.6);

        const auto cv = cev;
        const auto& cv0 = cv[0];
        const auto& cv1 = cv[1];
        const auto& cv2 = cv[2];
        test_assert(&cv0 == cv.data() + 0);
        test_assert(&cv1 == cv.data() + 1);
        test_assert(&cv2 == cv.data() + 2);

        auto v = cev;
        auto& v0 = v[0];
        auto& v1 = v[1];
        auto& v2 = v[2];
        test_assert(&v0 == v.data() + 0);
        test_assert(&v1 == v.data() + 1);
        test_assert(&v2 == v.data() + 2);
    }

    TEST_CASE(pre_increment_operator)
    {
        ivec3 v(1, 2, 3);
        test_assert(&(++v) == &v);
        test_assert(v[0] == 2);
        test_assert(v[1] == 3);
        test_assert(v[2] == 4);
    }

    TEST_CASE(post_increment_operator)
    {
        ivec3 v(1, 2, 3);
        test_assert(v++ == ivec3(1, 2, 3));
        test_assert(v[0] == 2);
        test_assert(v[1] == 3);
        test_assert(v[2] == 4);
    }

    TEST_CASE(pre_decrement_operator)
    {
        ivec3 v(1, 2, 3);
        test_assert(&(--v) == &v);
        test_assert(v[0] == 0);
        test_assert(v[1] == 1);
        test_assert(v[2] == 2);
    }

    TEST_CASE(post_decrement_operator)
    {
        ivec3 v(1, 2, 3);
        test_assert(v-- == ivec3(1, 2, 3));
        test_assert(v[0] == 0);
        test_assert(v[1] == 1);
        test_assert(v[2] == 2);
    }

    TEST_CASE(addition_assignment_operator)
    {
        dvec3 v1(1.2, 3.4, 5.6);
        test_assert(&(v1 += 7) == &v1);
        test_assert(v1[0] == 1.2 + 7);
        test_assert(v1[1] == 3.4 + 7);
        test_assert(v1[2] == 5.6 + 7);

        dvec3 v2(1.2, 3.4, 5.6);
        test_assert(&(v2 += ivec3(7, 8, 9)) == &v2);
        test_assert(v2[0] == 1.2 + 7);
        test_assert(v2[1] == 3.4 + 8);
        test_assert(v2[2] == 5.6 + 9);
    }

    TEST_CASE(subtraction_assignment_operator)
    {
        dvec3 v1(1.2, 3.4, 5.6);
        test_assert(&(v1 -= 7) == &v1);
        test_assert(v1[0] == 1.2 - 7);
        test_assert(v1[1] == 3.4 - 7);
        test_assert(v1[2] == 5.6 - 7);

        dvec3 v2(1.2, 3.4, 5.6);
        test_assert(&(v2 -= ivec3(7, 8, 9)) == &v2);
        test_assert(v2[0] == 1.2 - 7);
        test_assert(v2[1] == 3.4 - 8);
        test_assert(v2[2] == 5.6 - 9);
    }

    TEST_CASE(multiplication_assignment_operator)
    {
        dvec3 v1(1.2, 3.4, 5.6);
        test_assert(&(v1 *= 7) == &v1);
        test_assert(v1[0] == 1.2 * 7);
        test_assert(v1[1] == 3.4 * 7);
        test_assert(v1[2] == 5.6 * 7);

        dvec3 v2(1.2, 3.4, 5.6);
        test_assert(&(v2 *= ivec3(7, 8, 9)) == &v2);
        test_assert(v2[0] == 1.2 * 7);
        test_assert(v2[1] == 3.4 * 8);
        test_assert(v2[2] == 5.6 * 9);
    }

    TEST_CASE(division_assignment_operator)
    {
        dvec3 v1(1.2, 3.4, 5.6);
        test_assert(&(v1 /= 7) == &v1);
        test_assert(v1[0] == 1.2 / 7);
        test_assert(v1[1] == 3.4 / 7);
        test_assert(v1[2] == 5.6 / 7);

        dvec3 v2(1.2, 3.4, 5.6);
        test_assert(&(v2 /= ivec3(7, 8, 9)) == &v2);
        test_assert(v2[0] == 1.2 / 7);
        test_assert(v2[1] == 3.4 / 8);
        test_assert(v2[2] == 5.6 / 9);
    }

    TEST_CASE(modulo_assignment_operator)
    {
        vec3<long long> v1(10LL, 21LL, 32LL);
        test_assert(&(v1 %= 9) == &v1);
        test_assert(v1[0] == 10LL % 9);
        test_assert(v1[1] == 21LL % 9);
        test_assert(v1[2] == 32LL % 9);

        vec3<long long> v2(10LL, 21LL, 32LL);
        test_assert(&(v2 %= ivec3(9, 8, 7)) == &v2);
        test_assert(v2[0] == 10LL % 9);
        test_assert(v2[1] == 21LL % 8);
        test_assert(v2[2] == 32LL % 7);
    }

    TEST_CASE(bitwise_and_assignment_operator)
    {
        vec3<long long> v1(12LL, 34LL, 56LL);
        test_assert(&(v1 &= 78) == &v1);
        test_assert(v1[0] == (12LL & 78));
        test_assert(v1[1] == (34LL & 78));
        test_assert(v1[2] == (56LL & 78));

        vec3<long long> v2(12LL, 34LL, 56LL);
        test_assert(&(v2 &= ivec3(78, 910, 1112)) == &v2);
        test_assert(v2[0] == (12LL & 78));
        test_assert(v2[1] == (34LL & 910));
        test_assert(v2[2] == (56LL & 1112));
    }

    TEST_CASE(bitwise_or_assignment_operator)
    {
        vec3<long long> v1(12LL, 34LL, 56LL);
        test_assert(&(v1 |= 78) == &v1);
        test_assert(v1[0] == (12LL | 78));
        test_assert(v1[1] == (34LL | 78));
        test_assert(v1[2] == (56LL | 78));

        vec3<long long> v2(12LL, 34LL, 56LL);
        test_assert(&(v2 |= ivec3(78, 910, 1112)) == &v2);
        test_assert(v2[0] == (12LL | 78));
        test_assert(v2[1] == (34LL | 910));
        test_assert(v2[2] == (56LL | 1112));
    }

    TEST_CASE(bitwise_xor_assignment_operator)
    {
        vec3<long long> v1(12LL, 34LL, 56LL);
        test_assert(&(v1 ^= 78) == &v1);
        test_assert(v1[0] == (12LL ^ 78));
        test_assert(v1[1] == (34LL ^ 78));
        test_assert(v1[2] == (56LL ^ 78));

        vec3<long long> v2(12LL, 34LL, 56LL);
        test_assert(&(v2 ^= ivec3(78, 910, 1112)) == &v2);
        test_assert(v2[0] == (12LL ^ 78));
        test_assert(v2[1] == (34LL ^ 910));
        test_assert(v2[2] == (56LL ^ 1112));
    }

    TEST_CASE(bitwise_shift_left_assignment_operator)
    {
        vec3<long long> v1(12LL, 34LL, 56LL);
        test_assert(&(v1 <<= 1) == &v1);
        test_assert(v1[0] == (12LL << 1));
        test_assert(v1[1] == (34LL << 1));
        test_assert(v1[2] == (56LL << 1));

        vec3<long long> v2(12LL, 34LL, 56LL);
        test_assert(&(v2 <<= ivec3(1, 2, 3)) == &v2);
        test_assert(v2[0] == (12LL << 1));
        test_assert(v2[1] == (34LL << 2));
        test_assert(v2[2] == (56LL << 3));
    }

    TEST_CASE(bitwise_shift_right_assignment_operator)
    {
        vec3<long long> v1(12LL, 34LL, 56LL);
        test_assert(&(v1 >>= 1) == &v1);
        test_assert(v1[0] == (12LL >> 1));
        test_assert(v1[1] == (34LL >> 1));
        test_assert(v1[2] == (56LL >> 1));

        vec3<long long> v2(12LL, 34LL, 56LL);
        test_assert(&(v2 >>= ivec3(1, 2, 3)) == &v2);
        test_assert(v2[0] == (12LL >> 1));
        test_assert(v2[1] == (34LL >> 2));
        test_assert(v2[2] == (56LL >> 3));
    }

    TEST_CASE(unary_plus_operator)
    {
        CONST_OR_CONSTEXPR auto v = +dvec3(1.2, 3.4, 5.6);
        test_assert(v == dvec3(+1.2, +3.4, +5.6));
    }

    TEST_CASE(unary_minus_operator)
    {
        CONST_OR_CONSTEXPR auto v = -dvec3(1.2, 3.4, 5.6);
        test_assert(v == dvec3(-1.2, -3.4, -5.6));
    }

    TEST_CASE(bitwise_not_operator)
    {
        CONST_OR_CONSTEXPR auto v = ~ivec3(1, 2, 3);
        test_assert(v == ivec3(~1, ~2, ~3));
    }

    TEST_CASE(logical_not_operator)
    {
        CONST_OR_CONSTEXPR auto v = !ivec3(0, 1, 0);
        test_assert(v == bvec3(!0, !1, !0));
    }

    TEST_CASE(addition_operator)
    {
        CONST_OR_CONSTEXPR auto v1 = 1 + dvec3(2.3, 4.5, 6.7);
        test_assert(v1[0] == 1 + 2.3);
        test_assert(v1[1] == 1 + 4.5);
        test_assert(v1[2] == 1 + 6.7);

        CONST_OR_CONSTEXPR auto v2 = dvec3(1.2, 3.4, 5.6) + 7;
        test_assert(v2[0] == 1.2 + 7);
        test_assert(v2[1] == 3.4 + 7);
        test_assert(v2[2] == 5.6 + 7);

        CONST_OR_CONSTEXPR auto v3 = dvec3(1.2, 3.4, 5.6) + ivec3(7, 8, 9);
        test_assert(v3[0] == 1.2 + 7);
        test_assert(v3[1] == 3.4 + 8);
        test_assert(v3[2] == 5.6 + 9);
    }

    TEST_CASE(equality_operator)
    {
        CONST_OR_CONSTEXPR fvec3 v1(1.2f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 v2(1.2f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 v3(1.2f, 3.4f, 0.0f);
        CONST_OR_CONSTEXPR dvec3 v4(1.2f, 0.0f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 v5(0.0f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR auto result1 = (v1 == v2);
        CONST_OR_CONSTEXPR auto result2 = (v1 == v3);
        CONST_OR_CONSTEXPR auto result3 = (v1 == v4);
        CONST_OR_CONSTEXPR auto result4 = (v1 == v5);
        test_assert(result1 == true);
        test_assert(result2 == false);
        test_assert(result3 == false);
        test_assert(result4 == false);
    }

    TEST_CASE(inequality_operator)
    {
        CONST_OR_CONSTEXPR fvec3 v1(1.2f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 v2(1.2f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 v3(1.2f, 3.4f, 0.0f);
        CONST_OR_CONSTEXPR dvec3 v4(1.2f, 0.0f, 5.6f);
        CONST_OR_CONSTEXPR dvec3 v5(0.0f, 3.4f, 5.6f);
        CONST_OR_CONSTEXPR auto result1 = (v1 != v2);
        CONST_OR_CONSTEXPR auto result2 = (v1 != v3);
        CONST_OR_CONSTEXPR auto result3 = (v1 != v4);
        CONST_OR_CONSTEXPR auto result4 = (v1 != v5);
        test_assert(result1 == false);
        test_assert(result2 == true);
        test_assert(result3 == true);
        test_assert(result4 == true);
    }
}
