cmake_minimum_required(VERSION 3.3)
project(ydk_gnmi)

find_package(Protobuf REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(PROTO_PATH "${CMAKE_SOURCE_DIR}/protos")
set(GNMI_PROTO "${PROTO_PATH}/gnmi.proto")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})

set(GNMI_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/gnmi.pb.cc")
set(GNMI_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/gnmi.pb.h")
set(GNMI_GRPC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/gnmi.grpc.pb.cc")
set(GNMI_GRPC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/gnmi.grpc.pb.h")
add_custom_command(
    OUTPUT "${GNMI_PB_H_FILE}"
           "${GNMI_PB_CPP_FILE}"
           "${GNMI_GRPC_PB_H_FILE}"
           "${GNMI_GRPC_PB_CPP_FILE}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--cpp_out=${GENERATED_PROTOBUF_PATH}"
         "${GNMI_PROTO}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--grpc_out=${GENERATED_PROTOBUF_PATH}"
         "--plugin=protoc-gen-grpc=/usr/local/bin/GRPC_CPP_PLUGIN"
         "${GNMI_PROTO}"
    )
set(GENERATED_PROTOBUF_FILES ${GNMI_PB_H_FILE} ${GNMI_PB_CPP_FILE}
    ${GNMI_GRPC_PB_H_FILE} ${GNMI_GRPC_PB_CPP_FILE})

include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

add_library(ydk_gnmi_generated ${GENERATED_PROTOBUF_FILES})
