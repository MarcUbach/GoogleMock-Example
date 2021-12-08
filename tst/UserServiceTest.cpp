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
        userRepository = std::make_shared<MockUserRepository>();
        passwordEncoder = std::make_shared<MockPasswordEncoder>();
        ENABLED_USER = std::make_shared<User>(validID_, validHash_, true);
        DISABLED_USER = std::make_shared<User>(invalidID_, invalidHash_, false);
    }

    const std::string validID_ = "user_id";
    const std::string validHash_ = "hash";
    const std::string invalidID_ = "invalid_user_id";
    const std::string invalidHash_ = "invalid_hash";
    const std::string validPassword_ = "password";
    const std::string invalidPassword_ = "invalid_password";

    std::shared_ptr<MockUserRepository> userRepository;
    std::shared_ptr<MockPasswordEncoder> passwordEncoder;
    std::shared_ptr<User> ENABLED_USER;
    std::shared_ptr<User> DISABLED_USER;
};

class UserCredentialsInvalid : public WhenCheckingUserCredentials
{
protected:
    void SetUp()
    {
        WhenCheckingUserCredentials::SetUp();

        userService = std::make_shared<UserService>(userRepository, passwordEncoder);
    }

    std::shared_ptr<UserService> userService;

    const std::string invalidUserID = "invalid user id";
};

TEST_F(UserCredentialsInvalid, ShouldBeInvalidForInvalidID)
{
    {
        InSequence correctSequence;

        EXPECT_CALL(*userRepository, FindByID(invalidUserID))
                .Times(1)
                .WillOnce(Return(*DISABLED_USER));
        EXPECT_CALL(*passwordEncoder, Encode(validPassword_))
                .Times(0);
    }

    bool isUserValid = userService->IsValidUser(invalidUserID, validPassword_);
    ASSERT_FALSE(isUserValid);
}

TEST_F(UserCredentialsInvalid, ShouldBeInvalidForInvalidPassword)
{
    {
        InSequence correctSequence;

        EXPECT_CALL(*userRepository, FindByID(validID_))
                .Times(1)
                .WillOnce(Return(*ENABLED_USER));
        EXPECT_CALL(*passwordEncoder, Encode(invalidPassword_))
                .Times(1)
                .WillOnce(Return(invalidHash_));
    }

    bool isUserValid = userService->IsValidUser(ENABLED_USER->GetID(), invalidPassword_);
    ASSERT_FALSE(isUserValid);
}

TEST_F(UserCredentialsInvalid, ShouldBeInvalidForInvalidUser)
{
    {
        InSequence correctSequence;

        EXPECT_CALL(*userRepository, FindByID(DISABLED_USER->GetID()))
                .Times(1)
                .WillOnce(Return(*DISABLED_USER));
        EXPECT_CALL(*passwordEncoder, Encode(validPassword_))
                .Times(0);
    }

    bool isUserValid = userService->IsValidUser(DISABLED_USER->GetID(), validPassword_);
    ASSERT_FALSE(isUserValid);
}

class UserCredentialsValid : public WhenCheckingUserCredentials
{
protected:
    void SetUp()
    {
        WhenCheckingUserCredentials::SetUp();

        userService = std::make_shared<UserService>(userRepository, passwordEncoder);
    }

    std::shared_ptr<UserService> userService;
};

TEST_F(UserCredentialsValid, ShouldBeValidForValidCredentials)
{
    EXPECT_CALL(*userRepository, FindByID(_))
            .Times(1)
            .WillOnce(Return(*ENABLED_USER));

    EXPECT_CALL(*passwordEncoder, Encode(validPassword_))
            .Times(1)
            .WillOnce(Return(validHash_));

    bool isUserValid = userService->IsValidUser(ENABLED_USER->GetID(), validPassword_);
    ASSERT_TRUE(isUserValid);
}