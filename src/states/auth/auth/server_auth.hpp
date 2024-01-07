#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <auth/msg/msg_auth.hpp>
#include <types/playeraccount.hpp>

PlayerAccount * authenticate(const LoginMsg& msg);
int registeraccount(const RegisterMsg& msg);

#endif