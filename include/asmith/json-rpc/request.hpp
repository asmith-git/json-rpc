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

#ifndef ASMITH_JSON_RPC_REQUEST_HPP
#define ASMITH_JSON_RPC_REQUEST_HPP

#include "asmith/serial/value.hpp"
#include "asmith/serial/serialiser.hpp"
#include "rpc.hpp"

namespace asmith { namespace rpc {
	//! \todo Notifications
	//! \todo Batches

	struct request {
		uint64_t id;
		serial::value params;
		std::string jsonrpc;
		std::string method;
	};
}}

template<>
struct asmith::serial::serialiser<asmith::rpc::request> {
	typedef const asmith::rpc::request& input_t;
	typedef asmith::rpc::request output_t;

	static inline value serialise(input_t aValue) throw() {
		JSON_RPC_SERIALISE_BEGIN;
		JSON_RPC_SERIALISE_MEMBER(id);
		JSON_RPC_SERIALISE_MEMBER(params);
		JSON_RPC_SERIALISE_MEMBER(jsonrpc);
		JSON_RPC_SERIALISE_MEMBER(method);
		JSON_RPC_SERIALISE_END;
	}

	static inline output_t deserialise(const value& aValue) throw() {
		JSON_RPC_DESERIALISE_BEGIN;
		JSON_RPC_DESERIALISE_MEMBER(id);
		JSON_RPC_DESERIALISE_MEMBER(params);
		JSON_RPC_DESERIALISE_MEMBER(jsonrpc);
		JSON_RPC_DESERIALISE_MEMBER(method);
		JSON_RPC_DESERIALISE_END;
	}
};

#endif