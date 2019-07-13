/**
 *   \file aux.h
 *   \brief A Documented file.
 *
 *  Detailed description
 *
 */

#ifndef PARSE_H
#define PARSE_H

#include "global.h"

ForthObject StrToForthObj(const char* s);
char* itoa(int val, int base);
void ForthError(const char* err_message, const char* word);
void ForthWarning(const char* err_message, const char* word);

#endif /* PARSE_H */