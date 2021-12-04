# The can be multiple apps
# Add sets of these three commands
# find_library(SECURITY_FRAMEWORK Security)
# message("-->>> ${SECURITY_FRAMEWORK_LIBRARIES}")
# find_library(CORE_FRAMEWORK CoreFoundation)
# message("-->>> ${CORE_FRAMEWORK_LIBRARIES}")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${CMAKE_PROJECT_NAME}
                        PRIVATE
                        aoc_library
                        aoc_core
                    )
