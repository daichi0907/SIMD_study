// libgeom.cpp : スタティック ライブラリ用の関数を定義します。
//
#include "pch.h"
#include <intrin.h>
#include "../include/libgeom.h"

// 4つのfloat が num個の配列をsrcからdstにコピー
void copy_vector4_array(float* dst, const float* src, int num)
{
#if 1
	// ToDo: SIMD計算を使って実装して下さい
	__m256 sum = { 0 };
	
	for (int i = 0; i < num; i++) 
	{
		__m256 pd = _mm256_load_ps(reinterpret_cast<const float*>(&dst[i]));
		__m256 ps = _mm256_load_ps(reinterpret_cast<const float*>(&src[i]));
		
		sum = ps;
		_mm256_store_ps(&dst[i], sum);
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
	__m256 sum = { 0 };
	for (int i = 0; i < num; i++)
	{
		__m256 pd = _mm256_load_ps(reinterpret_cast<const float*>(&dst[i]));
		__m256 ps0 = _mm256_load_ps(reinterpret_cast<const float*>(&src0[i]));
		__m256 ps1 = _mm256_load_ps(reinterpret_cast<const float*>(&src1[i]));

		sum = _mm256_add_ps(ps0, ps1);
		_mm256_store_ps(&dst[i], sum);
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
	__m256 sum = { 0 };
	for (int i = 0; i < num; i++)
	{
		__m256 pd = _mm256_load_ps(reinterpret_cast<const float*>(&dst[i]));

		__m256 mul0 = _mm256_mul_ps(_mm256_load_ps(reinterpret_cast<const float*>(&matrix[4 * i])),
			_mm256_load_ps(reinterpret_cast<const float*>(&src[0])));
		__m256 mul1 = _mm256_mul_ps(_mm256_load_ps(reinterpret_cast<const float*>(&matrix[4 * i + 1])),
			_mm256_load_ps(reinterpret_cast<const float*>(&src[1])));
		__m256 mul2 = _mm256_mul_ps(_mm256_load_ps(reinterpret_cast<const float*>(&matrix[4 * i + 2])),
			_mm256_load_ps(reinterpret_cast<const float*>(&src[2])));
		__m256 mul3 = _mm256_mul_ps(_mm256_load_ps(reinterpret_cast<const float*>(&matrix[4 * i + 3])),
			_mm256_load_ps(reinterpret_cast<const float*>(&src[3])));
		
		sum = _mm256_add_ps(_mm256_add_ps(_mm256_add_ps(mul0, mul1), mul2), mul3);
		_mm256_store_ps(&dst[i], sum);
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
