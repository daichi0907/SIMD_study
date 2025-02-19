﻿// libgeom.cpp : スタティック ライブラリ用の関数を定義します。
//
#include "pch.h"
#include <intrin.h>
#include "../include/libgeom.h"

// 4つのfloat が num個の配列をsrcからdstにコピー
void copy_vector4_array(float* dst, const float* src, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	// （追記）ほとんど解説を見て実行したものです。
	for (int i = 0; i < num; i++) 
	{
		__m128 ps = _mm_load_ps(src + 4 * i);
		_mm_store_ps((dst + 4 * i), ps);
	}
	
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = ps[0];
		pd[1] = ps[1];
		pd[2] = ps[2];
		pd[3] = ps[3];

		pd += 4;
		ps += 4;
	}
#endif
}

// 4つのfloat が num個の配列 src0, src1を足してdstに出力
void add_vector4_array(float* dst, const float* src0, const float* src1, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	// （追記）ほとんど解説を見て実行したものです。
	for (int i = 0; i < num; i++)
	{
		__m128 ps0 = _mm_load_ps(&src0[4 * i]);
		__m128 ps1 = _mm_load_ps(&src1[4 * i]);

		__m128 ps = _mm_add_ps(ps0, ps1);

		_mm_store_ps(reinterpret_cast<float*>(&dst[4 * i]), ps);
	}

	
#else
	float* pd = dst;
	const float* ps0 = src0;
	const float* ps1 = src1;

	for (int i = 0; i < num; i++) {
		pd[0] = ps0[0] + ps1[0];
		pd[1] = ps0[1] + ps1[1];
		pd[2] = ps0[2] + ps1[2];
		pd[3] = ps0[3] + ps1[3];

		pd += 4;
		ps0 += 4;
		ps1 += 4;
	}
#endif
}

// 4つのfloat に num個の配列 src にmatrix[4][4] の行列を掛けてdstに出力
void apply_matrix_vector4_array(float* dst, const float* src, const float* matrix, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	// （追記）ほとんど解説を見て実行したものです。
	__m128 mat0 = _mm_load_ps(&matrix[4 * 0]);
	__m128 mat1 = _mm_load_ps(&matrix[4 * 1]);
	__m128 mat2 = _mm_load_ps(&matrix[4 * 2]);
	__m128 mat3 = _mm_load_ps(&matrix[4 * 3]);
	_MM_TRANSPOSE4_PS(mat0, mat1, mat2, mat3);
	for (int i = 0; i < num; i++)
	{
		__m128 v0 = _mm_load_ps(&src[4 * i]);
		__m128 v = _mm_mul_ps(mat0, _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(0, 0, 0, 0)));
		v = _mm_fmadd_ps(mat1, _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(1, 1, 1, 1)), v);
		v = _mm_fmadd_ps(mat2, _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(2, 2, 2, 2)), v);
		v = _mm_fmadd_ps(mat3, _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(3, 3, 3, 3)), v);
		_mm_store_ps(&dst[4 * i], v);
	}

	
	
#else
	float* pd = dst;
	const float* ps = src;

	for (int i = 0; i < num; i++) {
		pd[0] = matrix[4*0+0]*ps[0] + matrix[4*0+1]*ps[1] + matrix[4*0+2]*ps[2] + matrix[4*0+3]*ps[3];
		pd[1] = matrix[4*1+0]*ps[0] + matrix[4*1+1]*ps[1] + matrix[4*1+2]*ps[2] + matrix[4*1+3]*ps[3];
		pd[2] = matrix[4*2+0]*ps[0] + matrix[4*2+1]*ps[1] + matrix[4*2+2]*ps[2] + matrix[4*2+3]*ps[3];
		pd[3] = matrix[4*3+0]*ps[0] + matrix[4*3+1]*ps[1] + matrix[4*3+2]*ps[2] + matrix[4*3+3]*ps[3];

		pd += 4;
		ps += 4;
	}
#endif
}
