#include "IRenderer.h"
#include <iostream>

IRenderer::IRenderer(void)
{
}


IRenderer::~IRenderer(void)
{
}

//******************************************************************
//FUNCTION:
void IRenderer::_renderV()
{
//	std::cout<<"IRender render"<<std::endl;
	_loadEffect("Deferred_Shading");
}

