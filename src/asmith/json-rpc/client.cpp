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

#include "asmith/json-rpc/client.hpp"

namespace asmith { namespace rpc {
	// client

	client::~client() {

	}

	serial::value client::send_request(const std::string& aName, const serial::value& aParams) {
		request request;
		request.jsonrpc = "2.0";
		request.id = generate_request_id();
		request.method = aName;
		request.params = aParams;
		
		const response response = send_request_implementation(request);
		if(response.error.get_type() != serial::value::NULL_T) {
			const error e = serial::deserialise<error>(response.error);
			throw std::runtime_error(e.message);
		}
		return response.result;
	}

	void client::send_notification(const std::string& aName, const serial::value& aParams) {
		request request;
		request.jsonrpc = "2.0";
		request.id = NOTIFICATION_ID;
		request.method = aName;
		request.params = aParams;

		send_notification_implementation(request);
	}
}}