cmake_minimum_required(VERSION 3.16)

project(auto-file-delete LANGUAGES CXX)

include(CTest)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(ENABLE_ASAN "Enable address sanitizer" OFF)
option(ENABLE_MSAN "Enable memory sanitizer" OFF)
option(ENABLE_CLANG_TIDY "Enable clang tidy" OFF)

if(ENABLE_ASAN AND ENABLE_MSAN)
  message(FATAL_ERROR "Both sanitizers cannot be enabled at same time")
endif()

if(ENABLE_ASAN)
  message("Building with ASAN")
  add_compile_options(-fsanitize=address)
  add_compile_options(-fsanitize=undefined)
  add_compile_options(-fno-sanitize-recover=all)
  add_compile_options(-fsanitize=float-divide-by-zero)
  add_compile_options(-fsanitize=float-cast-overflow)
  add_compile_options(-fno-sanitize=null)
  add_compile_options(-fno-sanitize=alignment)
  add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

if(ENABLE_MSAN)
  message("Building with MSAN")
  add_compile_options(-fsanitize=memory -fno-omit-frame-pointer)
  add_link_options(-fsanitize=memory)
endif()

if (ENABLE_CLANG_TIDY)
set(CMAKE_CXX_CLANG_TIDY
    "clang-tidy;-checks=*,-llvmlibc-restrict-system-libc-headers,\
    -llvmlibc-implementation-in-namespace,\
    -llvmlibc-callee-namespace,\
    -misc-use-anonymous-namespace,\
    -modernize-use-trailing-return-type,\
    -fuchsia-default-arguments-calls,\
    -cppcoreguidelines-avoid-magic-numbers,\
    -readability-magic-numbers,\
    -readability-implicit-bool-conversion,\
    -clang-diagnostic-unknown-warning-option,\
    -readability-identifier-length,\
    -llvm-header-guard,\
    -readability-avoid-const-params-in-decls,\
    -altera-unroll-loops;-warnings-as-errors=*;-header-filter=.")
endif()

add_compile_options($<$<CONFIG:Release>:-Wunused>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-pedantic>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Werror=logical-not-parentheses>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wall>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wextra>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wctor-dtor-privacy>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wno-comment>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wsign-promo>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wcast-align>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wcast-qual>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wdisabled-optimization>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wformat=2>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wmissing-declarations>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wmissing-include-dirs>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wredundant-decls>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wshadow>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wsign-conversion>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wstrict-overflow=2>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wswitch-default>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wundef>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Werror>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Werror=return-type>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Werror=uninitialized>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wstrict-aliasing=2>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wno-unknown-warning-option>)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wnoexcept>)
  add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wlogical-op>)
  add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-Wstrict-null-sentinel>)
endif()


add_executable(afd afd_main.cpp afd.cpp afd.hpp common.cpp common.hpp)
add_executable(afdq afdq_main.cpp afdq.cpp common.hpp common.cpp)
add_executable(afdd afdd.cpp common.hpp common.cpp)

add_subdirectory(tests)

include(GNUInstallDirs)
install(
  TARGETS afd
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(
  TARGETS afdq
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(
  TARGETS afdd
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
