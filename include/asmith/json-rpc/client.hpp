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
	private:
		template<class P1>
		static serial::value serialise_params(P1 p1) {
			serial::value val;
			serial::value::array_t& params = val.set_array();
			params.push_back(serial::serialise<P1>(p1));
			return val;
		}

		template<class P1, class P2>
		static serial::value serialise_params(P1 p1, P2 p2) {
			serial::value val;
			serial::value::array_t& params = val.set_array();
			params.push_back(serial::serialise<P1>(p1));
			params.push_back(serial::serialise<P2>(p2));
			return val;
		}

		template<class P1, class P2, class P3>
		static serial::value serialise_params(P1 p1, P2 p2, P3 p3) {
			serial::value val;
			serial::value::array_t& params = val.set_array();
			params.push_back(serial::serialise<P1>(p1));
			params.push_back(serial::serialise<P2>(p2));
			params.push_back(serial::serialise<P3>(p3));
			return val;
		}

		template<class P1, class P2, class P3, class P4>
		static serial::value serialise_params(P1 p1, P2 p2, P3 p3, P4 p4) {
			serial::value val;
			serial::value::array_t& params = val.set_array();
			params.push_back(serial::serialise<P1>(p1));
			params.push_back(serial::serialise<P2>(p2));
			params.push_back(serial::serialise<P3>(p3));
			params.push_back(serial::serialise<P4>(p4));
			return val;
		}

		template<class P1, class P2, class P3, class P4, class P5>
		static serial::value serialise_params(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
			serial::value val;
			serial::value::array_t& params = val.set_array();
			params.push_back(serial::serialise<P1>(p1));
			params.push_back(serial::serialise<P2>(p2));
			params.push_back(serial::serialise<P3>(p3));
			params.push_back(serial::serialise<P4>(p4));
			params.push_back(serial::serialise<P5>(p5));
			return val;
		}

		template<class P1, class P2, class P3, class P4, class P5, class P6>
		static serial::value serialise_params(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
			serial::value val;
			serial::value::array_t& params = val.set_array();
			params.push_back(serial::serialise<P1>(p1));
			params.push_back(serial::serialise<P2>(p2));
			params.push_back(serial::serialise<P3>(p3));
			params.push_back(serial::serialise<P4>(p4));
			params.push_back(serial::serialise<P5>(p5));
			params.push_back(serial::serialise<P6>(p6));
			return val;
		}
	protected:
		virtual uint64_t generate_request_id() = 0;
		virtual response send_request_implementation(const request&) = 0;
		virtual void send_notification_implementation(const request&) = 0;
	public:
		virtual ~client();

		serial::value send_request(const std::string&, const serial::value&);
		void send_notification(const std::string&, const serial::value&);

		template<class R>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName) {
			return serial::deserialise<R>(send_request(aName, serial::value()));
		}

		template<class R>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName) {
			send_notification(aName, serial::value());
		}

		template<class R, class P1>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1) {
			return serial::deserialise<R>(send_request(aName, serialise_params<P1>(p1)));
		}

		template<class R, class P1>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1) {
			send_notification(aName, serialise_params<P1>(p1));
		}

		template<class R, class P1, class P2>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2) {
			return serial::deserialise<R>(send_request(aName, serialise_params<P1, P2>(p1, p2)));
		}

		template<class R, class P1, class P2>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2) {
			send_notification(aName, serialise_params<P1, P2>(p1, p2));
		}

		template<class R, class P1, class P2, class P3>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3) {
			return serial::deserialise<R>(send_request(aName, serialise_params<P1, P2, P3>(p1, p2, p3)));
		}

		template<class R, class P1, class P2, class P3>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3) {
			send_notification(aName, serialise_params<P1, P2, P3>(p1, p2, p3));
		}

		template<class R, class P1, class P2, class P3, class P4>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3, P4 p4) {
			return serial::deserialise<R>(send_request(aName, serialise_params<P1, P2, P3, P4>(p1, p2, p3, p4)));
		}

		template<class R, class P1, class P2, class P3, class P4>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3, P4 p4) {
			send_notification(aName, serialise_params<P1, P2, P3, P4>(p1, p2, p3, p4));
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
			return serial::deserialise<R>(send_request(aName, serialise_params<P1, P2, P3, P4, P5>(p1, p2, p3, p4, p5)));
		}

		template<class R, class P1, class P2, class P3, class P4, class P5>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
			send_notification(aName, serialise_params<P1, P2, P3, P4, P5>(p1, p2, p3, p4, p5));
		}

		template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
		typename std::enable_if<!std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
			return serial::deserialise<R>(send_request(aName, serialise_params<P1, P2, P3, P4, P5, P6>(p1, p2, p3, p4, p5, p6)));
		}

		template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
		typename std::enable_if<std::is_same<R, void>::value, R>::type call(const std::string& aName, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
			send_notification(aName, serialise_params<P1,P2,P3,P4,P5,P6>(p1,p2,p3,p4,p5,p6));
		}
	};
}}

#endif