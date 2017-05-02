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

#ifndef ASMITH_JSON_RPC_RESPONSE_HPP
#define ASMITH_JSON_RPC_RESPONSE_HPP

#include "asmith/serial/value.hpp"
#include "asmith/serial/serialiser.hpp"
#include "rpc.hpp"

namespace asmith { namespace rpc {
	enum {
		// Specification defined
		PARSE_ERROR			= -32700,
		INVALID_REQUEST		= -32600,
		METHOD_NOT_FOUND	= -32601,
		INVALID_PARAMS		= -32602,
		INTERNAL_ERROR		= -32603,
		SERVER_ERROR_MIN	= -32000,
		SERVER_ERROR_MAX	= -32099,

		// Implementation defined
		EXCEPTION_THROWN = SERVER_ERROR_MIN
	};

	struct error {
		serial::value data;
		std::string message;
		int64_t code;
	};

	struct response {
		error error;
		serial::value result;
		std::string jsonrpc;
		uint64_t id;
	};
}}

template<>
struct asmith::serial::serialiser<asmith::rpc::error> {
	typedef const asmith::rpc::error& input_t;
	typedef asmith::rpc::error output_t;

	static inline value serialise(input_t aValue) throw() {
		JSON_RPC_SERIALISE_BEGIN;
		JSON_RPC_SERIALISE_MEMBER(data);
		JSON_RPC_SERIALISE_MEMBER(message);
		JSON_RPC_SERIALISE_MEMBER(jsonrpc);
		JSON_RPC_SERIALISE_MEMBER(code);
		JSON_RPC_SERIALISE_END;
	}

	static inline output_t deserialise(const value& aValue) throw() {
		JSON_RPC_DESERIALISE_BEGIN;
		JSON_RPC_DESERIALISE_MEMBER(data);
		JSON_RPC_DESERIALISE_MEMBER(message);
		JSON_RPC_DESERIALISE_MEMBER(jsonrpc);
		JSON_RPC_DESERIALISE_MEMBER(code);
		JSON_RPC_DESERIALISE_END;
	}
};

template<>
struct asmith::serial::serialiser<asmith::rpc::response> {
	typedef const asmith::rpc::response& input_t;
	typedef asmith::rpc::response output_t;

	static inline value serialise(input_t aValue) throw() {
		JSON_RPC_SERIALISE_BEGIN;
		JSON_RPC_SERIALISE_MEMBER(error);
		JSON_RPC_SERIALISE_MEMBER(result);
		JSON_RPC_SERIALISE_MEMBER(id);
		JSON_RPC_SERIALISE_END;
	}

	static inline output_t deserialise(const value& aValue) throw() {
		JSON_RPC_DESERIALISE_BEGIN;
		JSON_RPC_DESERIALISE_MEMBER(error);
		JSON_RPC_DESERIALISE_MEMBER(result);
		JSON_RPC_DESERIALISE_MEMBER(id);
		JSON_RPC_DESERIALISE_END;
	}
};

#endif