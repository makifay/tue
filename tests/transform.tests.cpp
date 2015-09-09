//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//     Please report any bugs, typos, or suggestions to
//         https://github.com/Cincinesh/tue/issues

#include <tue/transform.hpp>
#include <mon/test_case.hpp>

#include <tue/math.hpp>
#include <tue/quat.hpp>
#include <tue/vec.hpp>

namespace
{
    using namespace tue;

    TEST_CASE(rotation_vec_to_axis_angle)
    {
        const ivec3 rv1(1, 2, 3);
        const auto aa1 = transform::axis_angle(rv1);
        test_assert(aa1.xyz() == math::normalize(rv1));
        test_assert(aa1.a() == math::length(rv1));

        const ivec3 rv2(0, 0, 0);
        const auto aa2 = transform::axis_angle(rv2);
        test_assert(aa2.xyz() == dvec3::z_axis());
        test_assert(aa2.a() == 0.0);

        const auto aa3 = transform::axis_angle(1, 2, 3);
        test_assert(aa3.xyz() == math::normalize(rv1));
        test_assert(aa3.a() == math::length(rv1));

        const auto aa4 = transform::axis_angle(0, 0, 0);
        test_assert(aa4.xyz() == dvec3::z_axis());
        test_assert(aa4.a() == 0.0);
    }

    TEST_CASE(axis_angle_to_rotation_vec)
    {
        CONST_OR_CONSTEXPR auto rv1 =
            transform::rotation_vec(dvec3(1.2, 3.4, 5.6), 7.8);
        test_assert(rv1 == dvec3(1.2, 3.4, 5.6) * 7.8);

        CONST_OR_CONSTEXPR auto rv2 =
            transform::rotation_vec(1.2, 3.4, 5.6, 7.8);
        test_assert(rv2 == dvec3(1.2, 3.4, 5.6) * 7.8);

        CONST_OR_CONSTEXPR auto rv3 =
            transform::rotation_vec(dvec4(1.2, 3.4, 5.6, 7.8));
        test_assert(rv3 == dvec3(1.2, 3.4, 5.6) * 7.8);
    }

    TEST_CASE(axis_angle_to_rotation_quat)
    {
        const auto rq1 = transform::rotation_quat(ivec3(1, 2, 3), 5);
        test_assert(rq1.v() == ivec3(1, 2, 3) * math::sin(5/2.0));
        test_assert(rq1.s() == math::cos(5/2.0));

        const auto rq2 = transform::rotation_quat(1, 2, 3, 5);
        test_assert(rq2.v() == ivec3(1, 2, 3) * math::sin(5/2.0));
        test_assert(rq2.s() == math::cos(5/2.0));

        const auto rq3 = transform::rotation_quat(ivec4(1, 2, 3, 5));
        test_assert(rq3.v() == ivec3(1, 2, 3) * math::sin(5/2.0));
        test_assert(rq3.s() == math::cos(5/2.0));
    }

    TEST_CASE(rotation_vec_to_rotation_quat)
    {
        const auto rq1 = transform::rotation_quat(ivec3(1, 2, 3));
        test_assert(rq1 ==
            transform::rotation_quat(transform::axis_angle(1, 2, 3)));

        const auto rq2 = transform::rotation_quat(ivec3(0, 0, 0));
        test_assert(rq2 == dquat::identity());

        const auto rq3 = transform::rotation_quat(1, 2, 3);
        test_assert(rq3 ==
            transform::rotation_quat(transform::axis_angle(1, 2, 3)));

        const auto rq4 = transform::rotation_quat(0, 0, 0);
        test_assert(rq4 == dquat::identity());
    }

    TEST_CASE(translation_mat_2d)
    {
        CONST_OR_CONSTEXPR auto m1 =
            transform::translation_mat(1.2, 3.4);
        test_assert(m1[0] == dvec4(1.0, 0.0, 0.0, 1.2));
        test_assert(m1[1] == dvec4(0.0, 1.0, 0.0, 3.4));
        test_assert(m1[2] == dvec4(0.0, 0.0, 1.0, 0.0));
        test_assert(m1[3] == dvec4(0.0, 0.0, 0.0, 1.0));

        CONST_OR_CONSTEXPR auto m2 =
            transform::translation_mat<double, 2, 3>(1.2, 3.4);
        test_assert(m2[0] == dvec3(1.0, 0.0, 1.2));
        test_assert(m2[1] == dvec3(0.0, 1.0, 3.4));

        CONST_OR_CONSTEXPR auto m3 =
            transform::translation_mat(dvec2(1.2, 3.4));
        test_assert(m3[0] == dvec4(1.0, 0.0, 0.0, 1.2));
        test_assert(m3[1] == dvec4(0.0, 1.0, 0.0, 3.4));
        test_assert(m3[2] == dvec4(0.0, 0.0, 1.0, 0.0));
        test_assert(m3[3] == dvec4(0.0, 0.0, 0.0, 1.0));

        CONST_OR_CONSTEXPR auto m4 =
            transform::translation_mat<double, 2, 3>(dvec2(1.2, 3.4));
        test_assert(m4[0] == dvec3(1.0, 0.0, 1.2));
        test_assert(m4[1] == dvec3(0.0, 1.0, 3.4));
    }

    TEST_CASE(translation_mat_3d)
    {
        CONST_OR_CONSTEXPR auto m1 =
            transform::translation_mat(1.2, 3.4, 5.6);
        test_assert(m1[0] == dvec4(1.0, 0.0, 0.0, 1.2));
        test_assert(m1[1] == dvec4(0.0, 1.0, 0.0, 3.4));
        test_assert(m1[2] == dvec4(0.0, 0.0, 1.0, 5.6));
        test_assert(m1[3] == dvec4(0.0, 0.0, 0.0, 1.0));

        CONST_OR_CONSTEXPR auto m2 =
            transform::translation_mat<double, 3, 4>(1.2, 3.4, 5.6);
        test_assert(m2[0] == dvec4(1.0, 0.0, 0.0, 1.2));
        test_assert(m2[1] == dvec4(0.0, 1.0, 0.0, 3.4));
        test_assert(m2[2] == dvec4(0.0, 0.0, 1.0, 5.6));

        CONST_OR_CONSTEXPR auto m3 =
            transform::translation_mat(dvec3(1.2, 3.4, 5.6));
        test_assert(m3[0] == dvec4(1.0, 0.0, 0.0, 1.2));
        test_assert(m3[1] == dvec4(0.0, 1.0, 0.0, 3.4));
        test_assert(m3[2] == dvec4(0.0, 0.0, 1.0, 5.6));
        test_assert(m3[3] == dvec4(0.0, 0.0, 0.0, 1.0));

        CONST_OR_CONSTEXPR auto m4 =
            transform::translation_mat<double, 3, 4>(dvec3(1.2, 3.4, 5.6));
        test_assert(m4[0] == dvec4(1.0, 0.0, 0.0, 1.2));
        test_assert(m4[1] == dvec4(0.0, 1.0, 0.0, 3.4));
        test_assert(m4[2] == dvec4(0.0, 0.0, 1.0, 5.6));
    }

    TEST_CASE(rotation_mat_2d)
    {
        const auto m = transform::rotation_mat(12);
        test_assert(m[0] == dvec4(math::cos(12), -math::sin(12), 0.0, 0.0));
        test_assert(m[1] == dvec4(math::sin(12),  math::cos(12), 0.0, 0.0));
        test_assert(m[2] == dvec4(          0.0,            0.0, 1.0, 0.0));
        test_assert(m[3] == dvec4(          0.0,            0.0, 0.0, 1.0));
    }

    TEST_CASE(rotation_mat_3d)
    {
        const auto m = transform::rotation_mat(12, 34, 56, 78);
        double s, c;
        math::sincos(78, s, c);
        test_assert(m[0][0] == 12*12*(1-c) + c);
        test_assert(m[0][1] == 12*34*(1-c) - 56*s);
        test_assert(m[0][2] == 12*56*(1-c) + 34*s);
        test_assert(m[0][3] == 0.0);
        test_assert(m[1][0] == 12*34*(1-c) + 56*s);
        test_assert(m[1][1] == 34*34*(1-c) + c);
        test_assert(m[1][2] == 34*56*(1-c) - 12*s);
        test_assert(m[1][3] == 0.0);
        test_assert(m[2][0] == 12*56*(1-c) - 34*s);
        test_assert(m[2][1] == 34*56*(1-c) + 12*s);
        test_assert(m[2][2] == 56*56*(1-c) + c);
        test_assert(m[2][3] == 0.0);
        test_assert(m[3] == dvec4(0.0, 0.0, 0.0, 1.0));
    }
}
