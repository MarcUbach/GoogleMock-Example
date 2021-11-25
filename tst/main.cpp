#include "gtest/gtest.h"
#include "gmock/gmock.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::FLAGS_gmock_verbose = "verbose";
    return RUN_ALL_TESTS();
}
