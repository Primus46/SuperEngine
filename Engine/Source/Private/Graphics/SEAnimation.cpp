#include "CoreMinimal.h"
#include "Graphics/SEAnimation.h"
#include "Window/Window.h"
#include "Graphics/SETexture.h"

SEAnimation::SEAnimation()
{
	m_SpriteSheet = nullptr;
	FrameTimer = 0.0f;
	CurrentFrame = 0;
}

SEAnimation::~SEAnimation()
{
	m_SpriteSheet = nullptr;
}

bool SEAnimation::InportAnimation(Window* AssignedWindow, SEString PathToFile, SEAnimParams AnimParams)
{
	m_SpriteSheet = AssignedWindow->CreateTexture(PathToFile);

	if (m_SpriteSheet == nullptr) {
		SELog("Animation failed to create texture.");
		return false;
	}

	m_AnimParams = AnimParams;

	if (m_AnimParams.FrameHeight == 0) {
		m_AnimParams.FrameHeight = m_SpriteSheet->GetHeight() / std::max(m_AnimParams.RowCount, 1U);
	}

	if (m_AnimParams.FrameWidth == 0) {
		m_AnimParams.FrameWidth = m_SpriteSheet->GetWidth() / std::max(m_AnimParams.FrameCount, 1U);
	}

	m_SpriteSheet->SetDimensions(m_AnimParams.FrameWidth, m_AnimParams.FrameHeight);

	CurrentFrame = m_AnimParams.StartFrame;

	ClipAnimation();

	return true;
}

void SEAnimation::Update(float DeltaTime)
{
	if (m_SpriteSheet == nullptr) {
		return;
	}
	if (!m_SpriteSheet->GetVisibility()) {
		return;
	}


	FrameTimer += DeltaTime;

	float FPS = 1.0f / m_AnimParams.FrameRate;

	if (FrameTimer >= FPS) {
		FrameTimer = 0.0f;
		CurrentFrame++;
	}

	if (CurrentFrame > m_AnimParams.EndFrame) {
		CurrentFrame = m_AnimParams.StartFrame;
	}
	// set the clip for the texture to make sure we are on the correct frame
	ClipAnimation();
	
}

void SEAnimation::SetPosition(int X, int Y)
{
	m_SpriteSheet->SetPosition(X, Y);
}

void SEAnimation::SetScale(int W, int H)
{
	m_SpriteSheet->SetScale(W, H);
}

void SEAnimation::SetRotation(float NewRot)
{
	m_SpriteSheet->SetRotation(static_cast<double>(NewRot));
}

void SEAnimation::SetVisibility(bool IsVisible)
{
	m_SpriteSheet->SetVisibility(IsVisible);
}

void SEAnimation::ClipAnimation()
{
	// set the clip for the texture to make sure we are on the correct frame
	m_SpriteSheet->SetClip(
		m_AnimParams.FrameWidth * CurrentFrame,
		m_AnimParams.FrameHeight * m_AnimParams.Row,
		m_AnimParams.FrameWidth,
		m_AnimParams.FrameHeight
	);
}
