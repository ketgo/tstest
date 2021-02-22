# TSTest

TSTest (Thread Safety Test) is a thread-safety testing utility providing convenient classes and macros for writing tests in C++ projects.


## Install

The utility is a header-only library and can thus be installed by simply copying all the header files (see `tstest/include` folder) to your desired location.

The recommended way of installing is by using git submodules and CMake:
1. Create a submodule in your project 
    ```bash
    # From your project root
    $ git submodule add https://github.com/ketgo/tstest.git third_party/tstest
    ```
2. Add the following in your CMakeLists.txt file
    ```
    add_subdirectory(third_party/tstest)
    ```

## Usage

The following usage example use the googletest testing library. However, TSTest can be used with any C++ testing framework.

```c++
#include <tstest/tstest.hpp>

using namespace tstest;

class TSTestTestFixture : public ::testing::Test {
protected:
    std::unique_ptr<Assertor> assertor;
    std::unique_ptr<Runner> runner;
        
    void SetUp() override {
        // Setup assertor
        assertor = std::make_unique<Assertor>();
        // Setup runner
        runner = std::make_unique<Runner>();
    }
        
    void TearDown() override {}
};

TEST_F(TSTestTestFixture, TestEndToEnd) {
    bool flag = false; //<- test flag

    // Inserting thread function a
    THREAD((*runner), "test-thread-a") {
        int i;
        OPERATION("test_operation-a", i = 1);
    };

    // Inserting thread function b
    THREAD((*runner), "test-thread-b") {
        OPERATION("test_operation-b", flag = true);
    };

    // Inserting assertion function for different outcomes
    assertor->Insert(
        {
            {"test_operation-b", Event::Type::BEGIN},
            {"test_operation-b", Event::Type::END},
            {"test_operation-a", Event::Type::BEGIN},
            {"test_operation-a", Event::Type::END},
        },
        [&]() { 
            SUCCEED();
        }
    );
    assertor->Insert(
        {
            {"test_operation-a", Event::Type::BEGIN},
            {"test_operation-b", Event::Type::BEGIN},
            {"test_operation-b", Event::Type::END},
            {"test_operation-a", Event::Type::END},
        },
        [&]() { 
            FAIL();
        }
    );

    // Running thread functions
    runner->Run();
    // Assert outcomes
    assertor->Assert(runner->GetEventLog());
}
```

## Build

The CMake build system is required to build the project. Run the following command to trigger the build:
```bash
    $ mkdir build && cd build
    $ cmake ..
    $ make
```

The above command will create a DEBUG build. For running code quality, coverage, and sanitization checks, provide the following options to the above `cmake`:
```bash
    $ cmake .. -DCPPCHECK=ON -DCODE_COVERAGE=ON -DUSE_SANITIZER=Thread
```
CMake will now create targets for coverage with the naming convention `ccov-persist_test`. Moreover, the cppCheck tool will print code quality notifications when the source code file is getting compiled. The sanitizers are compiler provided tools that perform checks during a program runtime and return any detected issue. Different compiler flags are set depending on the value set for `USE_SANITIZER`. The possible values are:

- `Address`
- `Memory`
- `MemoryWithOrigins`
- `Undefined`
- `Thread`
- `Address;Undefined`
- `Undefined;Address`
- `Leak`

## License

The source code is under MIT license.

## Contributions

Code review, pull requests, and/or bug reports greatly welcomed! :)

If you have feature requests or suggestions to improve TSTest, feel free to open an Issue or reach me on my [email](ketangoyal1988@gmail.com).
