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

#ifndef ASMITH_JSON_RPC_CLIENT_HPP
#define ASMITH_JSON_RPC_CLIENT_HPP

#include "request.hpp"
#include "response.hpp"
#include "function.hpp"

namespace asmith { namespace rpc {
	class client {
	protected:
		virtual uint64_t generate_request_id() = 0;
		virtual response send_request(const response&) = 0;

		serial::value call_serial(const serial::value& aValue);
	public:
		virtual ~client();
	};
}}

#endif