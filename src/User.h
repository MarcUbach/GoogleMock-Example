#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    User(const std::string&  id, const std::string& passwordHash, bool enabled)
        : id_(id), passwordHash_(passwordHash), enabled_(enabled) {}

    std::string GetID() const { return id_ ;}

    void SetID(const std::string& id) { id_ = id; }

    std::string GetPasswordHash() const { return passwordHash_ ;}

    void SetPasswordHash(const std::string& passwordHash) { passwordHash_ = passwordHash; }

    bool IsEnabled() const { return enabled_; }

    void SetEnabled(bool enabled) { enabled_ = enabled; }

private:
    std::string id_;
    std::string passwordHash_;
    bool enabled_;
};

#endif /* USER_H */
