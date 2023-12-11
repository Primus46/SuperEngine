#pragma once
#include "SEGameObject.h"

class SEText;

class SETextObject :
    public SEGameObject
{
public:
    SETextObject(SEString DefaultName, Window* AssignedWindow);

    void LoadFont(SEString PathToFile);

    virtual void Update(float DeltaTime) override;

    int GetWidth() const;

    int GetHeight() const;

    void SetText(SEString Text);

    void SetFontSize(int Size);


protected:
    void OnDestroy() override;

protected:
    // store the text object
    TSharedPtr<SEText> m_Text;
};

