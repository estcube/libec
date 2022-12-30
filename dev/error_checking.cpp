#include "error.hpp"

int main(){
  // The error code as bytes
  // AA is the MSByte (HAL error)
  // DD is the LSByte (Application error)
  uint32_t error_code = 0xAABBCCDD;

  // From full error code
  ec::error from_full = ec::error(error_code);
  if(static_cast<uint32_t>(from_full) != error_code){
    while(1);
  }

  // Initializing an error with an error code and an argument.
  ec::error from_code_and_arg = ec::error(0xDD, 0xAABBCC);
  if(static_cast<uint32_t>(from_code_and_arg) != error_code){
    while(1);
  }

  // Constructor for initializing an error with an error code and another error as an argument.
  // NOTE: 8 MSBs of the argument error will be lost.
  ec::error from_another_error = ec::error(0xFF, from_full);
  if(static_cast<uint32_t>(from_another_error) != 0xBBCCDDFF){
    while(1);
  }

  // Copy constructor
  ec::error from_copy = ec::error(from_full);
  if(static_cast<uint32_t>(from_copy) != error_code) {
    while(1);
  }

  // Test the comparison operator for ec::error
  if ( !(from_copy == from_full) ) {
    while(1);
  }

  // Test the negative comparison operator for ec::error
  if (from_copy != from_full) {
    while(1);
  }

  while(1);
}
