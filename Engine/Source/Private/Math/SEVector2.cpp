#include "CoreMinimal.h"
#include "Math/SEVector2.h"

SEVector2::SEVector2()
{
	x = y = 0.0f;
}

SEVector2::SEVector2(float z)
{
	x = y = z;
}

SEVector2::SEVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool SEVector2::operator==(SEVector2 Other)
{
	return x == Other.x && y == Other.y;
}

bool SEVector2::operator!=(SEVector2 Other)
{
	return x != Other.x || y != Other.y;
}

SEVector2 SEVector2::operator+(SEVector2 Other)
{
	return SEVector2(x + Other.x, y + Other.y);
}

SEVector2& SEVector2::operator+=(SEVector2 Other)
{
	x += Other.x;
	y += Other.y;

	return *this;
}

SEVector2 SEVector2::operator-(SEVector2 Other)
{
	return SEVector2(x - Other.x, y - Other.y);
}

SEVector2& SEVector2::operator-=(SEVector2 Other)
{
	x -= Other.x;
	y -= Other.y;
	
	return *this;
}

SEVector2 SEVector2::operator*(SEVector2 Other)
{
	return SEVector2(x * Other.x, y * Other.y);
}

SEVector2& SEVector2::operator*=(SEVector2 Other)
{
	x *= Other.x;
	y *= Other.y;

	return *this;
}

SEVector2 SEVector2::operator/(SEVector2 Other)
{
	SEVector2 Result;

	if (Other.x == 0) {
		SELog("Attempting to divide by 0.");
	}
	else {
		Result.x = x / Other.x;
	}
	if (Other.y == 0) {
		SELog("Attempting to divide by 0.");
	}
	else {
		Result.y = y / Other.y;
	}

	return Result;
}

SEVector2& SEVector2::operator/=(SEVector2 Other)
{
	if (Other.x == 0) {
		SELog("Attempting to divide by 0.");
	}
	else {
		x / Other.x;
	}
	if (Other.y == 0) {
		SELog("Attempting to divide by 0.");
	}
	else {
		y / Other.y;
	}

	return *this;
}

SEVector2 SEVector2::operator*(float Scalar)
{
	return SEVector2(x * Scalar,  y * Scalar);
}

SEVector2& SEVector2::operator*=(float Scalar)
{
	x *= Scalar;
	y *= Scalar;
	
	return *this;
}

SEVector2 SEVector2::operator/(float Scalar)
{
	SEVector2 Result;

	if (Scalar == 0.0f) {
		SELog("Attempting to divide by 0.");
		return Result;
	}

	Result.x = x / Scalar;
	Result.y = y / Scalar;

	return *this;
}

SEVector2& SEVector2::operator/=(float Scalar)
{
	if (Scalar == 0.0f) {
		SELog("Attempting to divide by 0.");
	}

	x /= Scalar;
	y /= Scalar;

	return *this;
}

void SEVector2::Log()
{

}

void SEVector2::LogLength()
{

}

float SEVector2::Length()
{
	return sqrtf((x*x) + (y * y));
}

SEVector2& SEVector2::Normalise()
{
	if (Length() != 0.0f) {
		*this /= Length();
	}

	return *this;

}

SEVector2 SEVector2::Normal()
{
	SEVector2 Result;

	if (Length() != 0.0f) {
		Result /= Length();
	}

	return Result;
}

float SEVector2::Distance(SEVector2& v1, SEVector2& v2)
{
	return (v1 - v2).Length();
}

SEVector2 SEVector2::Zero()
{
	return SEVector2(0.0f);
}
