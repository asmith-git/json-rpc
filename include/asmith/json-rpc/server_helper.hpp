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

#ifndef ASMITH_JSON_RPC_SERVER_HELPER_HPP
#define ASMITH_JSON_RPC_SERVER_HELPER_HPP

#include <sstream>
#include "asmith/serial/json.hpp"
#include "server.hpp"

namespace asmith { namespace rpc {
	template<class CLIENT_ID>
	class server_helper : public server {
	protected:
		std::map<std::string, function> mFunctions;

		virtual void send_to_client(CLIENT_ID, const char*) = 0;

		void on_recieve_json(CLIENT_ID aClient, const char* aJson) {
			request request;
			response response;
			{
				std::stringstream ss;
				ss << aJson;
				request = serial::json_format().read<rpc::request>(ss);
			}
			if(handle_request(request, response)) {
				std::stringstream ss;
				serial::json_format().write<rpc::response>(response, ss);
				send_to_client(aClient, ss.str().c_str());
			}
		}

		// Inherited from server

		bool get_function(const std::string& aName, function& aFunction) override {
			const auto i = mFunctions.find(aName);
			if (i == mFunctions.end()) return false;
			aFunction = i->second;
			return true;
		}
	public:
		virtual ~server_helper() {

		}

		void add_function(const std::string& aName, const function& aFunction) {
			mFunctions.emplace(aName, aFunction);
		}
	};
}}

#endif