project(sampleselection)

cmake_minimum_required(VERSION 2.8)

find_package(OTB REQUIRED)
#find_package(Boost REQUIRED COMPONENTS filesystem)

include(${OTB_USE_FILE})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-missing-field-initializers -flto -mno-avx -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-missing-field-initializers")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_definitions(-DVCL_CAN_STATIC_CONST_INIT_FLOAT=0)

otb_create_application(
  NAME           SampleSelectionAgri
  SOURCES        SampleSelection.cpp
  LINK_LIBRARIES ${OTB_LIBRARIES})
#                ${Boost_LIBRARIES})




install(TARGETS otbapp_SampleSelectionAgri DESTINATION /sen2agri/distrib/Sen2Agri-System-master/sen2agri-processors)
