#pragma once
struct SEBoxBounds {
	SEBoxBounds() : x(0.0f), y(0.0f), w(1.0f), h(1.0f) {}
	SEBoxBounds(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

	SEBoxBounds operator+(SEBoxBounds Other) {
		SEBoxBounds Results;

		// this bounds + other bounds
		Results.x = x + Other.x;
		Results.y = y + Other.y;
		Results.w = w + Other.w;
		Results.h = h + Other.h;

		return Results;
	}

	bool IsOverLapping(const SEBoxBounds& Other) {
		return MaxX() > Other.x && x < Other.MaxX()
			&& MaxY() > Other.y && y < Other.MaxY();
	}

	// gives the x value + the width
	float MaxX() const { return x + w; }

	// gives the y value + the height
	float MaxY() const { return y + h; }

	float x, y;
	float w, h;
};