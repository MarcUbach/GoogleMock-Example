#ifndef MOCK_USER_REPOSITORY_H
#define MOCK_USER_REPOSITORY_H

#include "UserRepository.h"

class MockUserRepository : public UserRepository
{
public:
    MOCK_METHOD(User, FindByID, (std::string), (override));
};

#endif //MOCK_USER_REPOSITORY_H
