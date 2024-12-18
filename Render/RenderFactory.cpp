#include "RenderFactory.h"

RenderFactory* RenderFactory::g_renderFactory = nullptr;;


RenderFactory::RenderFactory() {

}


RenderFactory::~RenderFactory() {

}

void RenderFactory::InitRender(int renderType) {
	auto factory_render = RenderFactory::GetInstance();
	if (factory_render) {
		factory_render->renderType = renderType;
	}
}

RenderFactory* RenderFactory::GetInstance() {
	if (g_renderFactory) {
		g_renderFactory = new RenderFactory();
	}
	return g_renderFactory;
}

void RenderFactory::Release() {
	if (g_renderFactory) {
		delete g_renderFactory;
		g_renderFactory = nullptr;
	}
}