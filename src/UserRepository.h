#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>

class User;

class UserRepository
{
public:
    virtual User FindByID(std::string id) = 0;
};

#endif /* USER_REPOSITORY_H */
