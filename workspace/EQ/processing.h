//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 2
// * Godina: 2018
// *
// * Zadatak: Ekvalizacija audio signala
// * Autor:
// *
// *
/////////////////////////////////////////////////////////////////////////////

#ifndef EQ_PROCESSING_H_
#define EQ_PROCESSING_H_
#include "tistdtypes.h"

void calculateShelvingCoeff(float alpha, Int16* output);

void calculatePeekCoeff(float alpha, float beta, Int16* output);

void shelvingHP(Int16* input, Int16* output, int input_size, Int16* coeff, Int16* x_history, Int16* y_history, Int16 k);

void shelvingLP(Int16* input, Int16* output, int input_size, Int16* coeff, Int16* x_history, Int16* y_history, Int16 k);

void shelvingPeek(Int16* input, Int16* output, int input_size, Int16* coeff, Int16* x_history, Int16* y_history, Int16 k);


#endif /* EQ_PROCESSING_H_ */
