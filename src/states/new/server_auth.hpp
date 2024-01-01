#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "msg_auth.hpp"
#include "database/textdatabase.hpp"

PlayerAccount * authenticate(AuthMsg& authmsg);

#endif