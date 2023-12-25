include(FetchContent)

set(LIB_NAME "minhook")
message(STATUS "Setting up ${LIB_NAME}")

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        f5485b8454544c2f034c78f8f127c1d03dea3636
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})