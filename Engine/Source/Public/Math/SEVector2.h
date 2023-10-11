#pragma once

struct SEVector2 {
	SEVector2();
	SEVector2(float z);
	SEVector2(float x, float y);

	bool operator==(SEVector2 Other);
	bool operator!=(SEVector2 Other);

	SEVector2 operator+(SEVector2 Other);
	SEVector2& operator+=(SEVector2 Other);

	SEVector2 operator-(SEVector2 Other);
	SEVector2& operator-=(SEVector2 Other);

	SEVector2 operator*(SEVector2 Other);
	SEVector2& operator*=(SEVector2 Other);

	SEVector2 operator/(SEVector2 Other);
	SEVector2& operator/=(SEVector2 Other);

	// Scalar operations
	SEVector2 operator*(float Scalar);
	SEVector2& operator*=(float Scalar);

	SEVector2 operator/(float Scalar);
	SEVector2& operator/=(float Scalar);

	//debug log
	void Log();
	//quick debug tool
	void LogLength();

	float Length();
	//normalises the vector
	SEVector2& Normalise();
	//returns normal of a vector
	SEVector2 Normal();
	// get the distance between 2 vectors
	static float Distance(SEVector2& v1, SEVector2& v2);
	//returns sero vector
	static SEVector2 Zero();

	float x, y;
};
