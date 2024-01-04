#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <auth/msg/msg_auth.hpp>
#include <types/playeraccount.hpp>

PlayerAccount * authenticate(AuthMsg& authmsg);

#endif