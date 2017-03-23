//          Copyright Chiel Douwes 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "../functional/identity.hpp"
#include "../compatability/dependent_call.hpp"

namespace kvasir {
	namespace mpl {
		/// bind a function object to a type so that it can be returned or stored in a list
		/// this version of bind differs from normal implementations in that it does not take the
		/// parameters for it's execution in the initial call site, thus allowing the function to
		/// be either extracted from the type, or to be processed and used at a later stage.
		/// It is however possible to add parameters to the function before execution, so that
		/// they will be prepended to the function arguments when it is called.
		//template <template <typename...> class Func, typename... Args>
		//struct bind0n { // takes pack of 0-n elements
		//	template <typename... T>
		//	using f = Func<Args..., T...>;
		//};
		//template <template <typename...> class Func, typename... Args>
		//struct bind1 {
		//	template <typename T>
		//	using f = Func<Args..., T>;
		//};
		//template <template <typename...> class Func, typename... Args>
		//struct bind1n { // takes pack of 1-n elements
		//	template <typename T, typename... Ts>
		//	using f = Func<Args..., T, Ts...>;
		//};
		//template <template <typename...> class Func, typename... Args>
		//struct bind2 {
		//	template <typename T, typename U>
		//	using f = Func<Args..., T, U>;
		//};
		//template <template <typename...> class Func, typename... Args>
		//struct bind2n { // takes pack of 2-n elements
		//	template <typename T, typename U, typename... Ts>
		//	using f = Func<Args..., T, U, Ts...>;
		//};
		//template <template <typename...> class F, typename... As>
		//struct bind_t {
		//	template <typename... Ts>
		//	using f = typename F<As..., Ts...>::type;
		//};
		//template <template <typename...> class F>
		//struct lambda {};
		namespace c {
			template<template<typename...> class F, typename C = identity>
			struct cfl {
				template<typename...Ts>
				using f = typename C::template f<typename F<Ts...>::type>;
			};
			template<template<typename...> class F>
			struct cfl<F, identity> {
				template<typename...Ts>
				using f = typename F<Ts...>::type;
			};

			template<template<typename...> class F, typename C = identity>
			struct cfe {
				template<typename...Ts>
				using f = typename C::template f<F<Ts...>>;
			};
			template<template<typename...> class F>
			struct cfe<F, identity> {
				template<typename...Ts>
				using f = typename dcallf<sizeof...(Ts)<1000000>::template f1<F,Ts...>;
			};


			// helper for functions that cannot specialize to detect lambda wrapped types
			// this is handy but will be slower
			//namespace detail {
			//	template <typename T>
			//	struct make_bound : T {};
			//	template <template <typename...> class F>
			//	struct make_bound<lambda<F>> {
			//		template <typename... Ts>
			//		using f = F<Ts...>;
			//	};
			//}
		}
	}
}
