#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <grpc++/grpc++.h>

#include "gnmi.grpc.pb.h"
#include "gnmi_client.hpp"
#include "types.hpp"
//#include "logger.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using gnmi::CapabilityRequest;
using gnmi::CapabilityResponse;
using gnmi::GetRequest;
using gnmi::GetResponse;
using gnmi::gNMI;

using namespace std;
using namespace ydk;
typedef vector<string> StringVec;

//CapabilityRequest MakeCapabilityRequest() {}
gNMIClient::gNMIClient(shared_ptr<Channel> channel) {
	//YLOG_INFO("Connected to {} channel using grpc", channel);
}

int gNMIClient::connect() {
	//grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	init_capabilities();
    return EXIT_SUCCESS;
}

void gNMIClient::init_capabilities()
{
	const char* cas = {"ietf-netconf-monitoring.yang"};
    while (cas != NULL){
    	capabilities.push_back(cas);
    }
}

StringVec gNMIClient::get_capabilities()
{
    return capabilities;
}

gNMIClient::~gNMIClient()
{
	//YLOG_INFO("Disconnected from device");
}

int main(int argc, char** argv) {
	gNMIClient client(grpc::CreateChannel("localhost:50051",
            grpc::InsecureChannelCredentials()));
	std::cout << "---Cap Exchange---\n";
	return 0;
}
