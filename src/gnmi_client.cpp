#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include "gnmi_client.hpp"
#include "types.hpp"
#include "logger.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using gnmi::gNMI;

using namespace std;
using namespace ydk;

typedef vector<string> StringVec;


gNMIClient::gNMIClient(shared_ptr<Channel> channel) {
    YLOG_INFO("Connected to {} channel using grpc", channel);
}

int gNMIClient::connect() {
    grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    init_capabilities();
    return EXIT_SUCCESS;
}

void gNMIClient::init_capabilities() {
    const char* cas = {"ietf-netconf-monitoring.yang"};
    while (cas != NULL) {
    	capabilities.push_back(cas);
    }
}

StringVec gNMIClient::get_capabilities() {
    return capabilities;
}

gNMIClient::~gNMIClient() {
    YLOG_INFO("Disconnected from device");
}

