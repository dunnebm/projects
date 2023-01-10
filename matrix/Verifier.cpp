#include "Verifier.h"
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <regex>

Verifier::Verifier(size_t buffer_capacity)
: capacity(buffer_capacity)
{
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    failed_to_construct = true;
    return;
  }

  struct sockaddr_in server{};
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(55555);

  // Connect to server
  if (connect(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0)
  {
    failed_to_construct = true;
    close(sock_fd);
    return;
  }

  buffer = new char[capacity];
}

Verifier::~Verifier()
{
  if (failed_to_construct) return; // nothing to do
  close(sock_fd);
  delete [] buffer;
}

std::string Verifier::send_request(const std::string& xml)
{
  if (send(sock_fd, xml.c_str(), xml.size(), 0) < 0)
  {
    throw "Failed to send data!";
  }

  memset(buffer, 0, capacity);

  int nbytes;
  if ((nbytes = recv(sock_fd, buffer, capacity, 0)) < 0)
  {
    throw "Failed to recv data!";
  }

  return std::string{buffer, static_cast<size_t>(nbytes)};
}