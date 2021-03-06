// pitagorasv0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cmath>

float X[4] = { 1, 2, 3, 4 };
float Y[4] = { 1, 2, 3, 4 };
float Z[4];
float A[4];
void coutNumbers() {
	for (int i = 0; i < 4; i++) {
		if (A[i] == 0) {
			std::cout << X[i] << "^2 + " << Y[i] << "^2 = " << Z[i] << "^2" << std::endl;
		}
	}
}

int main()
{
	float Backup[4] = { 1, 2, 3, 4 };
	float Inc[4] = { 1, 1, 1, 1 };
	int i = 0, j = 0;

	_asm {
		push eax
		push ebx
		push ecx
		push edx
		//-------------------
		movups xmm0, [X]
		movups xmm1, [Y]
		movups xmm2, [Inc]

		cycle_i:
		cmp i, 1000
			jge end_cycle_i
			//----cycle_i-------{

			mov j, 0
			movups xmm1, [Backup]

			cycle_j:
		cmp j, 1000
			jge end_cycle_j
			//----cycle_j-------{
			movups[Y], xmm1	//assign xmm1 to Y array
			movups[X], xmm0	//assign xmm0 to X array

			movups xmm3, xmm0
			mulps xmm3, xmm3	//raise x in power of 2
			movups xmm4, xmm1
			mulps xmm4, xmm4	//raise y in power of 2

			addps xmm3, xmm4	//x^2 + y^2
			sqrtps xmm4, xmm3	//xmm4 = sqrt(xmm3)

			movups[Z], xmm4	//assign values of z to Z array

			roundps xmm4, xmm4, 1	//xmm3 = round(xmm4)
			mulps xmm4, xmm4	//xmm4^2

			subps xmm3, xmm4	//xmm3 - xmm4 - should get 0 if number inside was pithagoras triple

			movups[A], xmm3	//assign diferences between roots to A array
			call offset coutNumbers //call this function for numbers writing to console
			movups xmm0, [X]
			movups xmm1, [Y]
			movups xmm2, [Inc]

			addps xmm1, xmm2	//increase xmm1
		//----cycle_j-------}
			inc j
			jmp cycle_j
			end_cycle_j :

		addps xmm0, xmm2	//increase xmm0 by 4
			addps xmm0, xmm2
			addps xmm0, xmm2
			addps xmm0, xmm2
			//----cycle_i-------}
			inc i	//increase i by 4
			inc i
			inc i
			inc i
			jmp cycle_i
			end_cycle_i :


		pop eax
			pop ebx
			pop ecx
			pop edx
			//----------------------
	}

	return 0;
}