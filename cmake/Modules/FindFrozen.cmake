find_package(frozen QUIET)

if(NOT frozen_FOUND)
  FetchContent_Declare(
        frozen
        GIT_REPOSITORY https://github.com/serge-sans-paille/frozen
        GIT_TAG master
  )

  FetchContent_MakeAvailable(frozen)

endif()
