#include "CoreMinimal.h"
#include "GameObjects/SETextObject.h"
#include "Graphics/SEText.h"
#include "Window/Window.h"

SETextObject::SETextObject(SEString DefaultName, Window* AssignedWindow)
	: SEGameObject(DefaultName, AssignedWindow)
{
	m_Text = nullptr;
}

void SETextObject::LoadFont(SEString PathToFile)
{
	m_Text = GetWindow()->CreateText(PathToFile);

	if (m_Text == nullptr) {
		Destroy();
	}
}

void SETextObject::Update(float DeltaTime)
{
	SEGameObject::Update(DeltaTime);

	if (m_Text == nullptr) {
		return;
	}

	m_Text->SetPosition(
		GetTransform()->Position.x,
		GetTransform()->Position.y
	);

	m_Text->SetRotation(GetTransform()->Rotation);

	m_Text->SetScale(
		GetTransform()->Scale.x,
		GetTransform()->Scale.y
	);
}


int SETextObject::GetWidth() const
{
	if (m_Text == nullptr) {
		return 0;
	}

	return m_Text->GetWidth();
}

int SETextObject::GetHeight() const
{
	if (m_Text == nullptr) {
		return 0;
	}

	return m_Text->GetHeight();
}

void SETextObject::SetText(SEString Text)
{
	if (m_Text == nullptr) {
		return;
	}

	m_Text->SetText(Text);
}

void SETextObject::SetFontSize(int Size)
{
	if (m_Text == nullptr) {
		return;
	}

	m_Text->SetFontSize(Size);
}

void SETextObject::OnDestroy()
{
	GetWindow()->RemoveTexture(m_Text);

	m_Text = nullptr;
}
