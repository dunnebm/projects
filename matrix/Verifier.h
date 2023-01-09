#ifndef VERIFIER_H
#define VERIFIER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstddef>
#include <string>

struct sockaddr_in;
template <typename Num> class matrix;

class Verifier
{
  char* buffer;
  std::size_t capacity;
  int sock_fd;
  bool failed_to_construct = false;
  
public:
  Verifier(std::size_t buffer_size);
  Verifier(const Verifier& verifier) = delete;
  ~Verifier();

  std::string send_request(const std::string& str);

  bool failed() const { return failed_to_construct; }
};

#endif