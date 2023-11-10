#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SDL2/SDL.h"

typedef std::string SEString;

template <typename T>
using TArray = std::vector<T>;

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

template <typename T>
using TSharedArray = TArray<TSharedPtr<T>>;

typedef uint32_t SEUint;

typedef uint8_t SEUint8;

template <typename T, typename... Params>
TSharedPtr<T> TMakeShared(Params&&... params) {
	return std::make_shared<T>(std::forward<Params>(params)...);
}

static void SELog(SEString Message) {
	std::cout << Message << std::endl;
}

struct SEAnimParams {
	SEAnimParams() {
		StartFrame = 0;
		EndFrame = 0;
		FrameCount = 0;
		FrameWidth = 0;
		FrameHeight = 0;
		RowCount = 1;
		Row = 0;
		FrameRate = 24.0f;
	}

	SEUint StartFrame;
	SEUint EndFrame;
	SEUint FrameCount;
	SEUint FrameWidth, FrameHeight;
	SEUint RowCount, Row;
	float FrameRate;

};

struct SESpriteParams {
	SESpriteParams() {
		Frame = 0;
		FrameCount = 0;
		FrameWidth = 0;
		FrameHeight = 0;
		RowCount = 1;
		Row = 0;
	}

	SEUint Frame;
	SEUint FrameCount;
	SEUint FrameWidth, FrameHeight;
	SEUint RowCount, Row;
};
