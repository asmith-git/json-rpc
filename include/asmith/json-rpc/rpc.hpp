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

#ifndef ASMITH_JSON_RPC_HPP
#define ASMITH_JSON_RPC_HPP

namespace asmith {
	#define JSON_RPC_MACRO_JOIN2(a, b) a##b
	#define JSON_RPC_MACRO_JOIN(a, b) JSON_RPC_MACRO_JOIN2(a , b)

	#define JSON_RPC_SERIALISE_BEGIN value tmp; value::object_t& object = tmp.set_object();
	#define JSON_RPC_SERIALISE_END return tmp
	#define JSON_RPC_SERIALISE_MEMBER(name) object.emplace(#name, serial::serialise<decltype(JSON_RPC_MACRO_JOIN(aValue.,name))>(JSON_RPC_MACRO_JOIN(aValue.,name)))

	#define JSON_RPC_DESERIALISE_BEGIN output_t tmp; const value::object_t& object = aValue.get_object();
	#define JSON_RPC_DESERIALISE_END return tmp
	#define JSON_RPC_DESERIALISE_MEMBER(name) JSON_RPC_MACRO_JOIN(tmp.,name) = serial::deserialise<decltype(JSON_RPC_MACRO_JOIN(tmp.,name))>(object.find(#name)->second)
	#define JSON_RPC_DESERIALISE_OPTIONAL_MEMBER(name, value) \
		{\
			const auto i = object.find(#name);\
			JSON_RPC_MACRO_JOIN(tmp., name) = i == object.end() ? value : serial::deserialise<decltype(JSON_RPC_MACRO_JOIN(tmp., name))>(i->second);\
		}
}

#endif