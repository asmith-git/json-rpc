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
		function function;
		response response;
		response.id = aRequest.id;
		response.jsonrpc = "2.0";

		if(aRequest.jsonrpc != "2.0") {
			error e;
			e.code = INVALID_REQUEST;
			e.message = "Invalid Request";
			e.data.set_string() = aRequest.jsonrpc;
			response.error = serial::serialise<error>(e);
			if(aRequest.id != NOTIFICATION_ID) send_response(response);
			return;
		}

		try {
			function = get_function(aRequest.method);
		}catch (...) {
			error e;
			e.code = METHOD_NOT_FOUND;
			e.message = "Method not found";
			e.data.set_string() = aRequest.method;
			response.error = serial::serialise<error>(e);
			if (aRequest.id != NOTIFICATION_ID) send_response(response);
			return;
		}

		try {
			function = get_function(aRequest.method);
			response.result = function(aRequest.params);
		}catch(std::exception& e) {
			error e2;
			e2.code = EXCEPTION_THROWN;
			e2.message = e.what();
			response.error = serial::serialise<error>(e2);
			if (aRequest.id != NOTIFICATION_ID) send_response(response);
			return;
		}catch(...) {
			error e;
			e.code = EXCEPTION_THROWN;
			e.message = "Unknown type thrown by method";
			response.error = serial::serialise<error>(e);
			if (aRequest.id != NOTIFICATION_ID) send_response(response);
			return;
		}
		if(aRequest.id != NOTIFICATION_ID) send_response(response);
	}
}}