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

#include "asmith/json-rpc/server.hpp"

namespace asmith { namespace rpc {
	// server

	server::~server() {

	}

	void server::handle_request(const request& aRequest) {
		response response;
		response.id = aRequest.id;

		function function;
		try {
			function = get_function(aRequest.method);
		}catch (...) {
			response.error.code = METHOD_NOT_FOUND;
			response.error.message = "Method not found";
			response.error.data.set_string() = aRequest.method;
			send_response(response);
			return;
		}
		try {
			function = get_function(aRequest.method);
			response.result = function(aRequest.params);
		}catch(std::exception& e) {
			response.id = aRequest.id;
			response.error.code = EXCEPTION_THROWN;
			response.error.message = e.what();
			send_response(response);
			return;
		}catch(...) {
			response.id = aRequest.id;
			response.error.code = EXCEPTION_THROWN;
			response.error.message = "Unknown type thrown by method";
			send_response(response);
			return;
		}
		send_response(response);

	}
}}