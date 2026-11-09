cmake_minimum_required(VERSION 3.20)
project(ecc_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

option(ECC_BUILD_GUI        "Build Qt 6 GUI"            ON)
option(ECC_BUILD_TESTS      "Build Catch2/RapidCheck tests" ON)
option(ECC_BUILD_BENCH      "Build Google Benchmark targets" OFF)
option(ECC_BUILD_FUZZ       "Build libFuzzer targets (clang)" OFF)

# ---- external libraries (adjust to your setup / vcpkg / Conan) ----
find_package(Threads REQUIRED)
# find_package(GMP REQUIRED)
# find_package(Boost REQUIRED)
# find_package(OpenSSL REQUIRED)
# find_package(nlohmann_json REQUIRED)
# find_package(spdlog REQUIRED)

# ---- core library ----
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS src/core/*.cpp)
add_library(ecc_core STATIC ${CORE_SOURCES})
target_include_directories(ecc_core PUBLIC src)
target_link_libraries(ecc_core PUBLIC Threads::Threads)
# target_link_libraries(ecc_core PUBLIC gmp gmpxx OpenSSL::Crypto nlohmann_json::nlohmann_json spdlog::spdlog)

# ---- CLI ----
file(GLOB CLI_SOURCES CONFIGURE_DEPENDS src/cli/*.cpp)
add_executable(ecc_cli ${CLI_SOURCES})
target_link_libraries(ecc_cli PRIVATE ecc_core)

# ---- GUI ----
if(ECC_BUILD_GUI)
  find_package(Qt6 COMPONENTS Widgets Charts QUIET)
  if(Qt6_FOUND)
    file(GLOB_RECURSE GUI_SOURCES CONFIGURE_DEPENDS src/gui/*.cpp)
    add_executable(ecc_gui ${GUI_SOURCES})
    target_link_libraries(ecc_gui PRIVATE ecc_core Qt6::Widgets Qt6::Charts)
  endif()
endif()

# ---- tests ----
if(ECC_BUILD_TESTS)
  enable_testing()
  find_package(Catch2 3 QUIET)
  if(Catch2_FOUND)
    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
    add_executable(ecc_tests ${TEST_SOURCES})
    target_link_libraries(ecc_tests PRIVATE ecc_core Catch2::Catch2WithMain)
    # target_link_libraries(ecc_tests PRIVATE rapidcheck)
    add_test(NAME ecc_tests COMMAND ecc_tests)
  endif()
endif()

# ---- benchmarks ----
if(ECC_BUILD_BENCH)
  find_package(benchmark REQUIRED)
  file(GLOB BENCH_SOURCES CONFIGURE_DEPENDS benchmarks/*.cpp)
  add_executable(ecc_bench ${BENCH_SOURCES})
  target_link_libraries(ecc_bench PRIVATE ecc_core benchmark::benchmark_main)
endif()

# ---- fuzzers ----
if(ECC_BUILD_FUZZ)
  foreach(f fuzz_point_deserialization fuzz_key_deserialization)
    add_executable(${f} fuzz/${f}.cpp)
    target_link_libraries(${f} PRIVATE ecc_core)
    target_compile_options(${f} PRIVATE -fsanitize=fuzzer,address)
    target_link_options(${f} PRIVATE -fsanitize=fuzzer,address)
  endforeach()
endif()
