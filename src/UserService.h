#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <memory>
#include <utility>

#include "User.h"
#include "UserRepository.h"
#include "PasswordEncoder.h"

class UserService
{
public:
    UserService(std::shared_ptr<UserRepository> userRepository, std::shared_ptr<PasswordEncoder> passwordEncoder)
        : userRepository_(std::move(userRepository)), passwordEncoder_(std::move(passwordEncoder)) {}

    bool IsValidUser(const std::string& id, const std::string& password)
    {
        User user = userRepository_->FindByID(id);
        return IsEnabledUser(user) && IsValidPassword(user, password);
    }

private:
    bool IsEnabledUser(User user)
    {
        return user.IsEnabled();
    }

    bool IsValidPassword(User user, const std::string& password)
    {
        std::string encodedPassword = passwordEncoder_->Encode(password);
        return encodedPassword == user.GetPasswordHash();
    }

    std::shared_ptr<UserRepository> userRepository_;
    std::shared_ptr<PasswordEncoder> passwordEncoder_;
};

#endif /* USER_SERVICE_H */
