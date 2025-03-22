#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
  try {
    std::cout << "Hello, World!" << std::endl;
  } catch (const std::exception& fatal_error) {
    std::cerr << fatal_error.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}