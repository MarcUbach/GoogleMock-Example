#ifndef MOCK_PASSWORD_ENCODER_H
#define MOCK_PASSWORD_ENCODER_H

#include "PasswordEncoder.h"

class MockPasswordEncoder : public PasswordEncoder
{
public:
    MOCK_METHOD(std::string, Encode, (const std::string&), (override));
};

#endif //MOCK_PASSWORD_ENCODER_H
