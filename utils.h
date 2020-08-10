#pragma once

#define PI 3.14159f
#define PI2 PI * 2

#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

// 실수의 가장 작은 단위
#define FLOAT_EPSILON 0.001f
// 두 실수가 같은지 비교
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)
// 실수형->정수형 변환
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON)

namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float x1, float y1, float x2, float y2);
	void drawLine(HDC hdc, float startX, float startY, float endX, float endY);
}