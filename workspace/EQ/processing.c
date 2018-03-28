#include "processing.h"
#include "iir.h"

#define HISTORY_LENGTH 2


void clear_history(Int16* history) {

	int i;

	for (i = 0; i < HISTORY_LENGTH; i++) {
		history[i] = 0;
	}
}

Int16 cut(Int16 variable) {
	if (variable > 32767) {
		variable = 32767;
	}
	else if (variable < -32768) {
		variable = -32768;
	}

	return variable;
}

void calculateShelvingCoeff(float c_alpha, Int16* output)
{
	/* Your code here */
	output[0] = c_alpha * 32767;
	output[1] = -32768;
	output[2] = 32767;
	output[3] = -c_alpha * 32768;
}

void calculatePeekCoeff(float c_alpha, float c_beta, Int16* output)
{
	/* Your code here */
	output[0] = c_alpha * 32767;
	output[1] = -c_beta * (1 + c_alpha) * 32767 / 2;
	output[2] = 32767;
	output[3] = 32767;
	output[4] = -c_beta * (1 + c_alpha) * 32767 / 2;
	output[5] = c_alpha * 32767;
}

void shelvingHP(Int16* input, Int16* output, int input_size, Int16* coeff, Int16* x_history, Int16* y_history, Int16 k)
{
	/* Your code here */
	Int16 input_iir;
	int L;
	Int16 H;
	int i;

	clear_history(x_history);
	clear_history(y_history);

	for (i = 0; i < input_size; i++) {

		input_iir = first_order_IIR(input[i], coeff, x_history, y_history);

		L = (input[i] + input_iir) / 2;
		H = (input[i] - input_iir) / 2;

		L = _smpy(k, (Int16) L);

		L = cut((Int16) L);
		H = cut(H);

		output[i] = cut((Int16)L + H);

	}
}

void shelvingLP(Int16* input, Int16* output, int input_size, Int16* coeff, Int16* x_history, Int16* y_history, Int16 k)
{
	/* Your code here */
	Int16 input_iir;
	int L;
	Int16 H;
	int i;

	clear_history(x_history);
	clear_history(y_history);

	for (i = 0; i < input_size; i++) {

		input_iir = first_order_IIR(input[i], coeff, x_history, y_history);

		L = (input[i] - input_iir) / 2;
		H = (input[i] + input_iir) / 2;

		L = _smpy(k, (Int16) L);

		L = cut((Int16) L);
		H = cut(H);

		output[i] = cut((Int16)L + H);

	}
}

void shelvingPeek(Int16* input, Int16* output, int input_size, Int16* coeff, Int16* x_history, Int16* y_history, Int16 k)
{
	/* Your code here */
	Int16 input_iir;
	int L;
	Int16 H;
	int i;

	clear_history(x_history);
	clear_history(y_history);

	for (i = 0; i < input_size; i++) {

		input_iir = second_order_IIR(input[i], coeff, x_history, y_history);

		L = (input[i] - input_iir) / 2;
		H = (input[i] + input_iir) / 2;

		L = _smpy(k, (Int16) L);

		L = cut((Int16) L);
		H = cut(H);

		output[i] = cut((Int16)L + H);

	}
}
