/**
 *   \file tib.c
 *   \brief A Documented file.
 *
 *  Detailed description
 *
 */

#include "forth/tib.h"
/* Terminal Input Buffer FIFO cycle */
uint8_t terminal_buffer[TIB_SIZE];
uint8_t terminal_buffer_get_index;
uint8_t terminal_buffer_insert_index;
uint8_t pad[PAD_SIZE];

uint8_t TIBGetIndex(){
  while (terminal_buffer_get_index == terminal_buffer_insert_index) {
    pause();
  }
  return terminal_buffer_get_index;
}
bool TIBEmpty(){
  return (terminal_buffer_get_index == terminal_buffer_insert_index)
}
uint8_t *TIBGetAddrs(){
  return &terminal_buffer[TIBGetIndex()];
}
void TIBIncrementIndex(){
  terminal_buffer_get_index = ++terminal_buffer_get_index & (TIB_SIZE - 1);
}
inline char TIBReadChar(){
  uint8_t index = TIBGetValidIndex();
  TIBIncrementIndex();
  return terminal_buffer[index];
}
void TIBFlush(){
  terminal_buffer_get_index = terminal_buffer_insert_index;
}



