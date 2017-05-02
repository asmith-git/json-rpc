//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.

#ifndef ASMITH_JSON_RPC_FUNCTION_HPP
#define ASMITH_JSON_RPC_FUNCTION_HPP

#include <functional>
#include "asmith/serial/value.hpp"

namespace asmith { namespace rpc {

	typedef std::function<serial::value(const serial::value&)> function;

	namespace implementation {
		template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
		struct function_6 {
			template<class F>
			static function wrap(const F& aFunction) {
				return [=aFunction](const serial::value& aParams) {
					return serial::serialise<R>( aFunction(
						serial::deserialise<P1>(aParams[0]),
						serial::deserialise<P2>(aParams[1]),
						serial::deserialise<P3>(aParams[2]),
						serial::deserialise<P4>(aParams[3]),
						serial::deserialise<P5>(aParams[4]),
						serial::deserialise<P6>(aParams[5])
					));
				};
			}
		};

		template<class P1, class P2, class P3, class P4, class P5, class P6>
		struct function_6<void, P1, P2, P3, P4, P5, P6> {
			template<class F>
			static function wrap(const F& aFunction) {
				return [=aFunction](const serial::value& aParams) {
					aFunction(
						serial::deserialise<P1>(aParams[0]),
						serial::deserialise<P2>(aParams[1]),
						serial::deserialise<P3>(aParams[2]),
						serial::deserialise<P4>(aParams[3]),
						serial::deserialise<P5>(aParams[4]),
						serial::deserialise<P6>(aParams[5])
					);
					return serial::value();
				};
			}
		};
	}


}}
#endif