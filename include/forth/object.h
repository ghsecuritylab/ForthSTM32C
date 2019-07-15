/**
 *   \file object.h
 *   \brief A Documented file.
 *
 *  Copyright (c) 2019 Islam Omar (io1131@fayoum.edu.eg)
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"

#define FORTH_IS_FIXNUM_VAL(x) (x <= INT32_MAX && x >= INT_LEAST32_MAX)
#define FORTH_IS_BIGNUM_VAL(x) (x <= INT64_MAX && x >= INT_LEAST64_MAX)
#define FORTH_TYPE_MASK(t) ((ForthFixNum)(t)&kTypeMask)
#define FORTH_FLAG_MASK(t) ((ForthFixNum)(t) & !kTypeMask)
#define FORTH_IS_IMMEDIATE(o) (FORTH_TYPE_MASK(o.type) == kFixNum)
#define FORTH_IS_CONS(o) (FORTH_TYPE_MASK(o.type) == kCons)
#define FORTH_IS_CMPO(o) ((FORTH_FLAG_MASK(o.type) & kCompileOnly) != 0)
#define FORTH_IS_FLASH(o) ((FORTH_FLAG_MASK(o.type) & kFlash) != 0)
#define FORTH_IS_CODE(o) ((FORTH_FLAG_MASK(o.type) & kExecutable) != 0)

ForthData ForthCreateData(ForthType t);
ForthObject ForthCreateEmptyObject(ForthType t);
ForthObject ForthCreateCons(ForthObject a, ForthObject b);
ForthObject ForthCreateNull();
ForthObject ForthCreateFixNum(ForthFixNum x);
ForthObject ForthCreateBigNum(ForthBigNum x);
ForthObject ForthCreateSingleFloat(float x);
ForthObject ForthCreateDoubleFloat(double x);
ForthObject ForthCreateLongDoubleFloat(long double x);
ForthObject ForthCreateEmptyVector();
ForthObject ForthCreateVector(ForthObject x);
void ForthAddToVector(ForthObject x, ForthVector *v);
ForthObject ForthCreateObject(ForthData x, ForthType t);
void ForthRemoveObject(ForthObject obj);
void ForthRemoveFreeObject(ForthObject obj);

#define FORTH_CONS_CAR(x) (((ForthCons *)x)->car)
#define FORTH_CONS_CDR(x) (((ForthCons *)x)->cdr)
#define CONS(a, d) ForthCreateCons((a), (d))
#define ACONS(a, b, c) ForthCreateCons(ForthCreateCons((a), (b)), (c))
#define FORTH_FIXNUM(x) ((ForthFixNum)(x))
#define FORTH_BIGNUM(x) ((ForthBigNum)(*x))
#define FORTH_SFLOAT(x) ((float)(*x))
#define FORTH_DFLOAT(x) ((double)(*x))
#define FORTH_LDFLOAT(x) ((long double)(*x))
#define FORTH_CFUN(x) ((ForthFuncPtr)(*x))

static inline ForthObject ForthCar(ForthObject x) {
  if (x.data == NULL) return x;
  x = FORTH_CONS_CAR(x.data);
  return x;
}

static inline ForthObject ForthCdr(ForthObject x) {
  if (x.data == NULL) return x;
  x = FORTH_CONS_CDR(x);
  return x;
}

void execute() {
  ForthType t = tos.type;
  if (FORTH_IS_IMMEDIATE(t)) {
    tos = tos.data;
  } else {
    switch (FORTH_TYPE_MASK(t)) {
      case kCFun: {
        (*(ForthFuncPtr)(tos.data))();
        break;
      }
      case kByteCode: {
        static ForthVector *x;
        static uint8_t i;
        x = (ForthVector *)(tos.data);
        PopTOS();
        for (i = 0; i < x->size; i++) {
          execute(x->word);
        }
        break;
      }
      default:
        ForthError("CANNOT EXECUTE WORD", itoa(tos.data, 16));
        break;
    }
  }
}

#endif /* OBJECT_H */
