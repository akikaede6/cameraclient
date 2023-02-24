project (dds)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-unused-parameter")

file(GLOB SUBSCRIBER ${CMAKE_CURRENT_SOURCE_DIR}/DdsSubscriber/src/*.cpp)
file(GLOB SUBSCRIBERQOS ${CMAKE_CURRENT_SOURCE_DIR}/DdsSubscriber/src/QosUnion/*.cpp)

# Find requirements
add_library(${PROJECT_NAME}
        ${SUBSCRIBER}
        ${SUBSCRIBERQOS}
)

target_link_libraries(${PROJECT_NAME}  fastcdr fastrtps pthread)

add_library(framework::dds ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
        PUBLIC 
        ${PROJECT_SOURCE_DIR}
)
