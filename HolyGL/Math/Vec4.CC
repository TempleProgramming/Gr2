
asm
{
_VEC4::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG5[RBP]	// = *dest

//	CVTSD2SS	XMM0, SF_ARG1[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x10;
//	MOVSS		[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x00;

//	CVTSD2SS	XMM0, SF_ARG2[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x18;
//	MOVSS		4[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x40, 0x04;

//	CVTSD2SS	XMM0, SF_ARG3[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x20;
//	MOVSS		8[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x40, 0x08;

//	CVTSD2SS	XMM0, SF_ARG4[RBP]
	DU8			0xF2, 0x0F, 0x5A, 0x45, 0x28;
//	MOVSS		12[RAX], XMM0
	DU8			0xF3, 0x0F, 0x11, 0x40, 0x0C;

	POP			RBP
	RET1		40
}
/**
	@ingroup gfxmath
	@brief Initialize members of a vector with double-precision floats.

	@param[in]     x	X component.
	@param[in]     y	Y component.
	@param[in]     z	Z component.
	@param[in,out] dest	Destination
*/
_extern _VEC4 U0 Vec4(F64 x, F64 y, F64 z, F64 w, CVec4 *dest);

#define VEC4_STR "%n\t%n\t%n\t%n\n\n"

/**
	@ingroup gfxmath
	@brief Print members of a vector.

	@param[in] v	Vector
*/
U0 Vec4Print(CVec4 *v)
{
	U8 reg R15 str = "%n\t%n\t%n\t%n\n\n";
asm
{
	MOV			RAX, SF_ARG1[RBP]	// = *v
	SUB			RSP, 32

//	CVTSS2SD	XMM0, 12[RAX]
	DU8			0xF3, 0x0F, 0x5A, 0x40, 0x0C;
//	MOVSD		24[RSP], XMM0
	DU8			0xF2, 0x0F, 0x11, 0x44, 0x24, 0x18;

//	CVTSS2SD	XMM0, 8[RAX]
	DU8			0xF3, 0x0F, 0x5A, 0x40, 0x08;
//	MOVSD		16[RSP], XMM0
	DU8			0xF2, 0x0F, 0x11, 0x44, 0x24, 0x10;

//	CVTSS2SD	XMM0, 4[RAX]
	DU8			0xF3, 0x0F, 0x5A, 0x40, 0x04;
//	MOVSD		8[RSP], XMM0
	DU8			0xF2, 0x0F, 0x11, 0x44, 0x24, 0x08;

//	CVTSS2SD	XMM0, [RAX]
	DU8			0xF3, 0x0f, 0x5A, 0x00;
//	MOVSD		[RSP], XMM0
	DU8			0xF2, 0x0F, 0x11, 0x04, 0x24;

	PUSH		4					// # of varargs
	PUSH		R15
	CALL		&Print
	ADD			RSP, 48
}
}

asm
{
_VEC4_COPY::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]	// = *src
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]	// = *dest
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		16
}
/**
	@ingroup gfxmath
	@brief Copy all members of a vector to destination.

	@param[in]     src	Source
	@param[in,out] dest	Destination 
*/
_extern _VEC4_COPY U0 Vec4Copy(CVec4 *src, CVec4 *dest);

asm
{
_VEC4_IS_EQUAL::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]	// = *a
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]	// = *b
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//	CMPPS		XMM0, XMM1, 0		// CMPEQPS
	DU8			0x0F, 0xC2, 0xC1, 0x00;

//	PMOVMSKB	RAX, XMM0
	DU8			0x66, 0x0F, 0xD7, 0xC0;

	AND			RAX, 0xFFFF
	CMP			RAX, 0xFFFF
	JNZ			_is_not_equal
	MOV			RAX, 1
	JMP			_return
_is_not_equal:
	MOV			RAX, 0

_return:
	POP			RBP
	RET1		16
}
/**
	@ingroup gfxmath
	@brief Checks if two vectors are equal.

	@param[in] a	Vector 1
	@param[in] b	Vector 2
	@return			TRUE if equal.
*/
_extern _VEC4_IS_EQUAL Bool Vec4IsEqual(CVec4 *a, CVec4 *b);

asm
{
_VEC4_ADD::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//	ADDPS		XMM0, XMM1
	DU8			0x0F, 0x58, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Sum of two vectors.

	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_ADD U0 Vec4Add(CVec4 *a, CVec4 *b, CVec4 *dest);

asm
{
_VEC4_ADDS::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
//	MOVSS		XMM1, SF_ARG2[RBP]
	DU8			0xF3, 0x0F, 0x10, 0x4D, 0x18;
//	SHUFPS		XMM1, XMM1, 0
	DU8			0x0F, 0xC6, 0xC9, 0x00;
//	ADDPS		XMM0, XMM1
	DU8			0x0F, 0x58, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Add a scalar to a vector.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_ADDS U0 Vec4AddS(CVec4 *v, I32 *s, CVec4 *dest);

asm
{
_VEC4_SUB::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//	SUBPS		XMM0, XMM1
	DU8			0x0F, 0x5C, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Difference of two vectors.
	
	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_SUB U0 Vec4Sub(CVec4 *a, CVec4 *b, CVec4 *dest);

asm
{
_VEC4_SUBS::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
//	MOVSS		XMM1, SF_ARG2[RBP]
	DU8			0xF3, 0x0F, 0x10, 0x4D, 0x18;
//	SHUFPS		XMM1, XMM1, 0
	DU8			0x0F, 0xC6, 0xC9, 0x00;
//	SUBPS		XMM0, XMM1
	DU8			0x0F, 0x5C, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Subtract a scalar from a vector.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_SUBS U0 Vec4SubS(CVec4 *v, I32 *s, CVec4 *dest);

asm
{
_VEC4_MUL::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//	MULPS		XMM0, XMM1
	DU8			0x0F, 0x59, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Product of two vectors (element multiplication).
	
	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_MUL U0 Vec4Mul(CVec4 *a, CVec4 *b, CVec4 *dest);

asm
{
_VEC4_MULS::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
//	MOVSS		XMM1, SF_ARG2[RBP]
	DU8			0xF3, 0x0F, 0x10, 0x4D, 0x18;
//	SHUFPS		XMM1, XMM1, 0
	DU8			0x0F, 0xC6, 0xC9, 0x00;
//	MULPS		XMM0, XMM1
	DU8			0x0F, 0x59, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Scale a vector by a scalar.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_MULS U0 Vec4MulS(CVec4 *v, I32 *s, CVec4 *dest);


asm
{
_VEC4_DIV::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV			RAX, SF_ARG2[RBP]
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//	DIVPS		XMM0, XMM1
	DU8			0x0F, 0x5E, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Quotient of two vectors.
	
	@param[in]     a	Vector 1
	@param[in]     b	Vector 2
	@param[in,out] dest	Destination
*/
_extern _VEC4_DIV U0 Vec4Div(CVec4 *a, CVec4 *b, CVec4 *dest);

asm
{
_VEC4_DIVS::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
//	MOVSS		XMM1, SF_ARG2[RBP]
	DU8			0xF3, 0x0F, 0x10, 0x4D, 0x18;
//	SHUFPS		XMM1, XMM1, 0
	DU8			0x0F, 0xC6, 0xC9, 0x00;
//	DIVPS		XMM0, XMM1
	DU8			0x0F, 0x5E, 0xC1;
	MOV			RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24
}
/**
	@ingroup gfxmath
	@brief Scale a vector by a scalar.

	@param[in]     v	Vector
	@param[in]     s	Scalar
	@param[in,out] dest	Destination
*/
_extern _VEC4_DIVS U0 Vec4DivS(CVec4 *v, I32 *s, CVec4 *dest);

asm
{
_VEC4_MAX::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS 		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV 		RAX, SF_ARG2[RBP]
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//  MAXPS 		XMM0, XMM1
	DU8			0x0F, 0x5F, 0xC1;
	MOV 		RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24		

}
/**
	@ingroup gfxmath
	@brief Max of two vectors (element-wise).

	@param[in] 		a		Vector 1
	@param[in] 		b		Vector 2
	@param[in,out]	dest	Destination 
*/
_extern _VEC4_MAX U0 Vec4Max(CVec4 *a, CVec4 *b, CVec4 *dest);


asm
{
_VEC4_MIN::
	PUSH		RBP
	MOV			RBP, RSP

	MOV			RAX, SF_ARG1[RBP]
//	MOVAPS 		XMM0, [RAX]
	DU8			0x0F, 0x28, 0x00;
	MOV 		RAX, SF_ARG2[RBP]
//	MOVAPS		XMM1, [RAX]
	DU8			0x0F, 0x28, 0x08;
//  MINPS 		XMM0, XMM1
	DU8			0x0F, 0x5D, 0xC1;
	MOV 		RAX, SF_ARG3[RBP]
//	MOVAPS		[RAX], XMM0
	DU8			0x0F, 0x29, 0x00;

	POP			RBP
	RET1		24	
}

_extern _VEC4_MIN U0 Vec4Min(CVec4 *a, Cvec4 *b, CVec4 *dest);


asm
{
_VEC4_CROSS::
	PUSH	RBP
	MOV		RBP, RSP

	MOV		RAX, SF_ARG1[RBP]
//	MOVAPS	XMM0, [RAX]
	DU8		0x0F, 0x28, 0x00;
	MOV		RAX, SF_ARG2[RBP]
//	MOVAPS	XMM1, SF_ARG2[RBP]
	DU8		0x0F, 0x28, 0x08;			
//	MOVAPS	XMM1, XMM0
	DU8		0x0F, 0x28, 0xC8;
//  SHUFPS	XMM1, XMM0, 0xC9
	DU8		0x0F, 0xC6, 0xC8, 0xC9; // (3, 0, 2,1)
//	MOVAPS 	XMM2, XMM0
	DU8		0x0F, 0x28, 0xD0;
//	SHUFPS  XMM2, XMM0, 0xD2
	DU8		0x0F, 0xC6, 0xD0, 0xD2;	// (3, 1, 0, 2)
//	MOVAPS	XMM3, XMM0
	DU8		0x0F, 0x28, 0xD8;
//	SHUFPS  XMM3, XMM0, 0xC9
	DU8		0x0F, 0xC6, 0xD8, 0xC9; // (3, 0, 2, 1)
//	MOVAPS 	XMM4, XMM0
	DU8		0x0F, 0x28, 0xE0;	
//	SHUFPS	XMM4, XMM0, 0xD2 
	DU8		0x0F, 0xC6, 0xE0, 0xD2; // (3, 1, 0, 2)

//	MULPS		XMM5, XMM1
	DU8		0x0F, 0x59, 0xE9;
//	MULPS		XMM6, XMM2
	DU8		0x0F, 0x59, 0xF2;
//	MULPS		XMM7, XMM3
	DU8		0x0F, 0x59, 0xFB;


	MOV		RAX, SF_ARG3[RBP]
//	MOVAPS	[RAX], XMM5
	DU8		0x0F, 0x29, 0x28;

	POP 	RBP
	RET1	24
}

_extern _VEC4_CROSS U0 Vec4Cross(CMat4 *m, CVec4 *v, CVec4 *dest);

