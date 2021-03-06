// -----------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2019, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2019, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/seqan3/blob/master/LICENSE.md
// -----------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <seqan3/alphabet/concept.hpp>
#include <seqan3/alphabet/exception.hpp>
#include <seqan3/core/concept/core_language.hpp>
#include <seqan3/test/pretty_printing.hpp>

using namespace seqan3;

template <typename T>
using alphabet_ = ::testing::Test;

constexpr size_t max_iterations = 65536u;

TYPED_TEST_CASE_P(alphabet_);

TYPED_TEST_P(alphabet_, concept_check)
{
    EXPECT_TRUE(alphabet<TypeParam>);
    EXPECT_TRUE(alphabet<TypeParam &>);
    EXPECT_TRUE(alphabet<TypeParam const>);
    EXPECT_TRUE(alphabet<TypeParam const &>);

    EXPECT_TRUE(writable_alphabet<TypeParam>);
    EXPECT_TRUE(writable_alphabet<TypeParam &>);
    EXPECT_FALSE(writable_alphabet<TypeParam const>);
    EXPECT_FALSE(writable_alphabet<TypeParam const &>);
}

TYPED_TEST_P(alphabet_, global_assign_char_to)
{
    using char_t = alphabet_char_t<TypeParam>;
    if constexpr(std::integral<char_t>)
    {
        char_t i = std::numeric_limits<char_t>::min();
        char_t j = std::numeric_limits<char_t>::max();

        TypeParam t0;
        for (size_t k = 0; i < j && k < max_iterations; ++i, ++k)
            seqan3::assign_char_to(i, t0);

        EXPECT_TRUE((std::is_same_v<decltype(seqan3::assign_char_to(0, t0)), TypeParam &>));
        EXPECT_TRUE((std::is_same_v<decltype(seqan3::assign_char_to(0, TypeParam{})), TypeParam>));
    }
}

TYPED_TEST_P(alphabet_, global_char_is_valid_for) // only test negative example for most; more inside specialised tests
{
    if constexpr (alphabet_size<TypeParam> < 255) // includes most of our alphabets, but not the adaptations!
    {
        EXPECT_FALSE((char_is_valid_for<TypeParam>(0))); // for none of our alphabets char{0} is valid
    }
}

TYPED_TEST_P(alphabet_, global_assign_char_strictly_to)
{
    using char_t = alphabet_char_t<TypeParam>;
    if constexpr(std::integral<char_t>)
    {
        char_t i = std::numeric_limits<char_t>::min();
        char_t j = std::numeric_limits<char_t>::max();

        for (size_t k = 0; i < j && k < max_iterations; ++i, ++k)
        {
            if (char_is_valid_for<TypeParam>(i))
                EXPECT_NO_THROW(seqan3::assign_char_strictly_to(i, TypeParam{}));
            else
                EXPECT_THROW(seqan3::assign_char_strictly_to(i, TypeParam{}), invalid_char_assignment);
        }
    }
}

TYPED_TEST_P(alphabet_, global_to_char)
{
    TypeParam t0;
    EXPECT_TRUE((std::is_same_v<decltype(seqan3::to_char(t0)), alphabet_char_t<TypeParam>>));

    // more elaborate tests are done in specific alphabets

}

REGISTER_TYPED_TEST_CASE_P(alphabet_,
                           concept_check,
                           global_assign_char_to,
                           global_char_is_valid_for,
                           global_assign_char_strictly_to,
                           global_to_char);
