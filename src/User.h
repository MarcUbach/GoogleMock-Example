#ifndef USER_H
#define USER_H

#include <string>
#include <utility>

class User
{
public:
    User(std::string p_Id, std::string p_PasswordHash, bool p_Enabled)
        : m_Id(std::move(p_Id)), m_PasswordHash(std::move(p_PasswordHash)), m_Enabled(p_Enabled)
    {
    }

    std::string GetID() const { return m_Id; }

    void SetID(const std::string& p_Id) { m_Id = p_Id; }

    std::string GetPasswordHash() const { return m_PasswordHash; }

    void SetPasswordHash(const std::string& p_PasswordHash) { m_PasswordHash = p_PasswordHash; }

    bool IsEnabled() const { return m_Enabled; }

    void SetEnabled(bool p_Enabled) { m_Enabled = p_Enabled; }

private:
    std::string m_Id;
    std::string m_PasswordHash;
    bool m_Enabled;
};

#endif // USER_H
