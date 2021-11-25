#ifndef PASSWORD_ENCODER_H
#define PASSWORD_ENCODER_H

#include <string>

class PasswordEncoder
{
public:
    virtual std::string Encode(const std::string& password) = 0;
};

#endif /* PASSWORD_ENCODER_H */
