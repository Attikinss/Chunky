#include "GLStateManager.h"
#include "chunky/core/Logger.h"

#include <glad/gl.h>

namespace Chunky
{
	GLCullState GLStateManager::k_CullState;
	GLBlendState GLStateManager::k_BlendState;
	GLDepthState GLStateManager::k_DepthState;

	void GLStateManager::EnableCull()
	{
		k_CullState.Enable();
	}

	void GLStateManager::DisableCull()
	{
		k_CullState.Disable();
	}

	void GLStateManager::CullFace(CullMode mode)
	{
		CullFace((int)mode);
	}

	void GLStateManager::CullFace(int mode)
	{
		k_CullState.Mode = mode;
		glCullFace(mode);
	}

	void GLStateManager::EnableDepthTest()
	{
		k_CullState.Enable();
	}

	void GLStateManager::DisableDepthTest()
	{
		k_CullState.Disable();
	}

	void GLStateManager::DepthFunc(DepthFunction func)
	{
		DepthFunc((int)func);
	}

	void GLStateManager::DepthFunc(int func)
	{
		if (func == k_DepthState.Func)
			return;

		k_DepthState.Func = func;
		glDepthFunc(func);
	}

	void GLStateManager::DepthMask(bool mask)
	{
		if (mask == k_DepthState.Mask)
			return;

		k_DepthState.Mask = mask;
		glDepthMask(mask);
	}

	void GLStateManager::EnableBlend()
	{
		k_CullState.Enable();
	}

	void GLStateManager::DisableBlend()
	{
		k_CullState.Disable();
	}

	void GLStateManager::BlendFunc(SrcFactor srcRgb, DestFactor destRgb)
	{
		BlendFunc((int)srcRgb, (int)destRgb);
	}

	void GLStateManager::BlendFunc(int srcRgb, int destRgb)
	{
		if (srcRgb == k_BlendState.SrcRGB && destRgb == k_BlendState.DestRGB)
			return;

		k_BlendState.SrcRGB = srcRgb;
		k_BlendState.DestRGB = destRgb;

		glBlendFunc(srcRgb, destRgb);
	}

	void GLStateManager::BlendFuncSeparate(SrcFactor srcRgb, DestFactor destRgb, SrcFactor srcAlpha, DestFactor destAlpha)
	{
		BlendFuncSeparate((int)srcRgb, (int)destRgb, (int)srcAlpha, (int)destAlpha);
	}

	void GLStateManager::BlendFuncSeparate(int srcRgb, int destRgb, int srcAlpha, int destAlpha)
	{
		if (srcRgb == k_BlendState.SrcRGB && destRgb == k_BlendState.DestRGB &&
			srcAlpha == k_BlendState.SrcAlpha && destAlpha == k_BlendState.DestAlpha)
			return;

		k_BlendState.SrcRGB = srcRgb;
		k_BlendState.DestRGB = destRgb;
		k_BlendState.SrcAlpha = srcAlpha;
		k_BlendState.DestAlpha = destAlpha;

		glBlendFuncSeparate(srcRgb, destRgb, srcAlpha, destAlpha);
	}

	void GLStateManager::InfoDump()
	{
		Logger::Info("OpenGL Info:\n\tVersion: {0}\n\tVendor: {1}\n\tDevice: {2}",
			glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	}
}