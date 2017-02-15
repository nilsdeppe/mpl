//          Copyright Chiel Douwes 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "../sequence/create.hpp"
#include "../sequence/is_list.hpp"
#include "fold_left.hpp"

namespace kvasir {
	namespace mpl {
		namespace impl {
			namespace generic {
				template <bool list>
				struct flatten;

				template <typename Result, typename Elem>
				using flatten_func =
				typename flatten<impl::is_list<Elem>{}>::template f<Elem, Result>;

				template <>
				struct flatten<true> {
					// the passed element is a list
					template <typename List, typename Result>
					using f = typename impl::fold_left_impl<List>::template f<flatten_func, Result>;
				};

				template <>
				struct flatten<false> {
					// the passed element is not a list
					template <typename Elem, typename Result>
					using f = typename push_back_impl<Elem, Result>::f;
				};
			}

			template <typename Elem, typename Result>
			struct flatten {
				using f = generic::flatten_func<Result, Elem>;
			};
		}

		template <typename List, typename Result = typename impl::create_impl<List>::f>
		using flatten = typename impl::flatten<Result, List>::f;
	}
}
