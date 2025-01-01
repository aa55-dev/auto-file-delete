
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

set(test_list test_afd test_afdq)
foreach(testname ${test_list})
  add_executable(${testname} ${testname}.cpp ../afd.cpp ../afdq.cpp
                             ../common.cpp)
  add_test(${testname} ${testname})
  target_link_libraries(${testname} Boost::unit_test_framework)
endforeach()

add_executable(fuzz_afd fuzz_afd.cpp ../afd.cpp ../common.cpp)
add_executable(fuzz_afdq fuzz_afdq.cpp ../afdq.cpp ../common.cpp)
