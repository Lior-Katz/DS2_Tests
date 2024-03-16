# DS2_Tests
Unit Tests for DS2 using the GoogleTest framework.

## Black-box Testing
Unit tests that only test the API (public interface). These tests require minimal adjustments to the code and no adjustments for Olympics.

## White-box Testing
Unit tests that check the internal state and functionality of the code. These tests will provide more rigorous functionality coverage but might require some work to adjust for your implementation. This may include refactoring the test cases to call the correct functions (in case of naming differences), removing some tests (tests that check non-existent members or functions), and adding member function/friend class declarations to your code.

## Set-up
1.  To add this repo as a git submodule (enables pulling future changes), use `git submodule add <repo URL>` in your main project directory. For the repo URL, head to the `Code` section of this repository, click the green `Code` button, and select `Copy URL to clipboard`. Otherwise, you can simply download this repo as a zip and extract it into your project.
2.  Inside the `DS2_Tests` directory, open a new directory called `lib`.
3.  Go to the [GoogleTest Repo](https://github.com/google/googletest) and download the library as a zip file.
4.  Extract the contents of the file into `lib`. Make sure the contents are directly in `lib`, and not in a sub-directory.
5.  In the project's main `CMakeLists.txt` file, add the line `add_subdirectory(DS2_Tests)`  
6.  In `DS2_Tests`, create a `CMakeLists.txt` file with the following text:
  ```
  project(Google_tests)
  add_subdirectory(lib)
  add_subdirectory(Blackbox_Testing)
  add_subdirectory(Whitebox_Testing)

  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable(Google_Tests_run)

  target_link_libraries(Google_Tests_run gtest gtest_main)
  ```
  Add all additional files that need to be compiled to the list in `add_executable(...)` (test files and source files)

  ## Running Tests
  To run all tests, build and run the `Google_Tests_run` executable. Breakpoints can be added for debugging.  
  Individual tests can be run/debugged by using the green arrow icon next to the test function in the test file.
