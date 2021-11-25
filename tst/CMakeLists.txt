set(BINARY ${CMAKE_PROJECT_NAME}_tst)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(mocks)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp) #simplified

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
