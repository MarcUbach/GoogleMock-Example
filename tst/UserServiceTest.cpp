#include "gmock/gmock.h"

#include "UserService.h"
#include "User.h"
#include "MockUserRepository.h"
#include "MockPasswordEncoder.h"

using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;

class WhenCheckingUserCredentials : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_UserRepository = std::make_shared<MockUserRepository>();
        p_PasswordEncoder = std::make_shared<MockPasswordEncoder>();
        ENABLED_USER = std::make_shared<User>(m_ValidID, m_ValidHash, true);
        DISABLED_USER = std::make_shared<User>(m_InvalidID, m_InvalidHash, false);
    }

    const std::string m_ValidID = "user_id";
    const std::string m_ValidHash = "hash";
    const std::string m_InvalidID = "invalid_user_id";
    const std::string m_InvalidHash = "invalid_hash";
    const std::string m_ValidPassword = "password";
    const std::string m_InvalidPassword = "invalid_password";

    std::shared_ptr<MockUserRepository> m_UserRepository;
    std::shared_ptr<MockPasswordEncoder> p_PasswordEncoder;
    std::shared_ptr<User> ENABLED_USER;
    std::shared_ptr<User> DISABLED_USER;
};

class UserCredentialsInvalid : public WhenCheckingUserCredentials
{
protected:
    void SetUp()
    {
        WhenCheckingUserCredentials::SetUp();

        m_UserService = std::make_shared<UserService>(m_UserRepository, p_PasswordEncoder);
    }

    std::shared_ptr<UserService> m_UserService;

    const std::string m_InvalidUserID = "invalid user id";
};

TEST_F(UserCredentialsInvalid, ShouldBeInvalidForInvalidID)
{
    {
        InSequence correctSequence;

        EXPECT_CALL(*m_UserRepository, FindByID(m_InvalidUserID))
                .Times(1)
                .WillOnce(Return(*DISABLED_USER));
        EXPECT_CALL(*p_PasswordEncoder, Encode(m_ValidPassword))
                .Times(0);
    }

    bool isUserValid = m_UserService->IsValidUser(m_InvalidUserID, m_ValidPassword);
    ASSERT_FALSE(isUserValid);
}

TEST_F(UserCredentialsInvalid, ShouldBeInvalidForInvalidPassword)
{
    {
        InSequence correctSequence;

        EXPECT_CALL(*m_UserRepository, FindByID(m_ValidID))
                .Times(1)
                .WillOnce(Return(*ENABLED_USER));
        EXPECT_CALL(*p_PasswordEncoder, Encode(m_InvalidPassword))
                .Times(1)
                .WillOnce(Return(m_InvalidHash));
    }

    bool isUserValid = m_UserService->IsValidUser(ENABLED_USER->GetID(), m_InvalidPassword);
    ASSERT_FALSE(isUserValid);
}

TEST_F(UserCredentialsInvalid, ShouldBeInvalidForInvalidUser)
{
    {
        InSequence correctSequence;

        EXPECT_CALL(*m_UserRepository, FindByID(DISABLED_USER->GetID()))
                .Times(1)
                .WillOnce(Return(*DISABLED_USER));
        EXPECT_CALL(*p_PasswordEncoder, Encode(m_ValidPassword))
                .Times(0);
    }

    bool isUserValid = m_UserService->IsValidUser(DISABLED_USER->GetID(), m_ValidPassword);
    ASSERT_FALSE(isUserValid);
}

class UserCredentialsValid : public WhenCheckingUserCredentials
{
protected:
    void SetUp()
    {
        WhenCheckingUserCredentials::SetUp();

        m_UserService = std::make_shared<UserService>(m_UserRepository, p_PasswordEncoder);
    }

    std::shared_ptr<UserService> m_UserService;
};

TEST_F(UserCredentialsValid, ShouldBeValidForValidCredentials)
{
    EXPECT_CALL(*m_UserRepository, FindByID(_))
            .Times(1)
            .WillOnce(Return(*ENABLED_USER));

    EXPECT_CALL(*p_PasswordEncoder, Encode(m_ValidPassword))
            .Times(1)
            .WillOnce(Return(m_ValidHash));

    bool isUserValid = m_UserService->IsValidUser(ENABLED_USER->GetID(), m_ValidPassword);
    ASSERT_TRUE(isUserValid);
}