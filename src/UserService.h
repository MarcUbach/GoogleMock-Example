#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <memory>
#include <utility>

#include "PasswordEncoder.h"
#include "User.h"
#include "UserRepository.h"

class UserService
{
public:
    UserService(std::shared_ptr<UserRepository> p_UserRepository, std::shared_ptr<PasswordEncoder> p_PasswordEncoder)
        : m_UserRepository(std::move(p_UserRepository)), m_PasswordEncoder(std::move(p_PasswordEncoder))
    {
    }

    bool IsValidUser(const std::string& p_Id, const std::string& p_Password)
    {
        User user = m_UserRepository->FindByID(p_Id);
        return IsEnabledUser(user) && IsValidPassword(user, p_Password);
    }

private:
    bool IsEnabledUser(const User& p_User) { return p_User.IsEnabled(); }

    bool IsValidPassword(const User& p_User, const std::string& p_Password)
    {
        std::string encodedPassword = m_PasswordEncoder->Encode(p_Password);
        return encodedPassword == p_User.GetPasswordHash();
    }

    std::shared_ptr<UserRepository> m_UserRepository;
    std::shared_ptr<PasswordEncoder> m_PasswordEncoder;
};

#endif // USER_SERVICE_H
