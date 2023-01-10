#ifndef VERIFIER_H
#define VERIFIER_H

#include <cstddef>
#include <string>

struct sockaddr_in;
template <typename Num> class matrix;

class Verifier
{
  char* buffer;
  size_t capacity;
  int sock_fd;
  bool failed_to_construct = false;
  
public:
  Verifier(size_t buffer_size);
  Verifier(const Verifier& verifier) = delete;
  ~Verifier();

  std::string send_request(const std::string& str);

  bool failed() const { return failed_to_construct; }
};

#endif