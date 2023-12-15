#include <iostream>
#include <string>
#include <type_traits>	// underlying_type
#include <memory>		// unique_ptr

#include "msg_format.hpp"

using namespace std;

string BaseMsg::toString() const {
	return	to_string(static_cast<underlying_type<MsgType>::type>(msg_type))
		+ ":" + to_string(msg_length)
		+ ":" + debugPrint();
}

