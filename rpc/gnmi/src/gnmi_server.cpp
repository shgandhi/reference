#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "gnmi.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using gnmi::CapabilityRequest;
using gnmi::CapabilityResponse;
using gnmi::GetRequest;
using gnmi::GetResponse;
using gnmi::gNMI;

// Logic and data behind the server's behavior.
class gNMIImpl final : public gNMI::Service {
	Status Capabilities(ServerContext* context, const CapabilityRequest* request,
			CapabilityResponse* response) override {
		return Status::OK;
	}
	Status Get(ServerContext* context, const GetRequest* request, GetResponse*
			response) override {
		return Status::OK;
	}
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  gNMIImpl service();
  
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
