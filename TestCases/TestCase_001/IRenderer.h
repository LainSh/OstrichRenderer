#pragma once
#include "../../Renderer/Renderer/Renderer.h"

class IRenderer : public OST::CRenderer
{
public:
	IRenderer(void);
	virtual ~IRenderer(void);

protected:
	virtual void _renderV() override;

};

