/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.lslboost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_04052005_1132)
#define FUSION_BEGIN_04052005_1132

#include <lslboost/blank.hpp>
#include <lslboost/utility/enable_if.hpp>
#include <lslboost/mpl/if.hpp>
#include <lslboost/fusion/sequence/intrinsic_fwd.hpp>
#include <lslboost/fusion/support/tag_of.hpp>
#include <lslboost/fusion/support/is_sequence.hpp>
#include <lslboost/fusion/support/is_segmented.hpp>
#include <lslboost/fusion/sequence/intrinsic/detail/segmented_begin.hpp>

namespace lslboost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag; // iterator facade tag
    struct lslboost_tuple_tag; // lslboost::tuples::tuple tag
    struct lslboost_array_tag; // lslboost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct begin_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_begin<Sequence>
                  , blank
                >::type
            {};
        };

        template <>
        struct begin_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template begin<Sequence> {};
        };

        template <>
        struct begin_impl<lslboost_tuple_tag>;

        template <>
        struct begin_impl<lslboost_array_tag>;

        template <>
        struct begin_impl<mpl_sequence_tag>;

        template <>
        struct begin_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct begin
            : extension::begin_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq)
    {
        return result_of::begin<Sequence>::call(seq);
    }

    template <typename Sequence>
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq)
    {
        return result_of::begin<Sequence const>::call(seq);
    }
}}

#endif
