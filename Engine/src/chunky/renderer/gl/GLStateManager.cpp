#include "GLStateManager.h"
#include "chunky/core/Logger.h"

#include "math/vector/Vector4f.h"

#include <glad/gl.h>

namespace Chunky
{
	struct GLStateInfo
	{
		GLCullState CullState;
		GLBlendState BlendState;
		GLDepthState DepthState;
		Vector4f ClearColour;
	};

	static GLStateInfo s_StateInfo;

	void GLStateManager::EnableCull()
	{
		s_StateInfo.CullState.Enable();
	}

	void GLStateManager::DisableCull()
	{
		s_StateInfo.CullState.Disable();
	}

	void GLStateManager::CullFace(CullMode mode)
	{
		CullFace((int)mode);
	}

	void GLStateManager::CullFace(int mode)
	{
		s_StateInfo.CullState.Mode = mode;
		glCullFace(mode);
	}

	void GLStateManager::EnableDepthTest()
	{
		s_StateInfo.DepthState.Enable();
	}

	void GLStateManager::DisableDepthTest()
	{
		s_StateInfo.DepthState.Disable();
	}

	void GLStateManager::DepthFunc(DepthFunction func)
	{
		DepthFunc((int)func);
	}

	void GLStateManager::DepthFunc(int func)
	{
		if (func == s_StateInfo.DepthState.Func)
			return;

		s_StateInfo.DepthState.Func = func;
		glDepthFunc(func);
	}

	void GLStateManager::DepthMask(bool mask)
	{
		if (mask == s_StateInfo.DepthState.Mask)
			return;

		s_StateInfo.DepthState.Mask = mask;
		glDepthMask(mask);
	}

	void GLStateManager::EnableBlend()
	{
		s_StateInfo.CullState.Enable();
	}

	void GLStateManager::DisableBlend()
	{
		s_StateInfo.CullState.Disable();
	}

	void GLStateManager::BlendFunc(SrcFactor srcRgb, DestFactor destRgb)
	{
		BlendFunc((int)srcRgb, (int)destRgb);
	}

	void GLStateManager::BlendFunc(int srcRgb, int destRgb)
	{
		if (srcRgb == s_StateInfo.BlendState.SrcRGB && destRgb == s_StateInfo.BlendState.DestRGB)
			return;

		s_StateInfo.BlendState.SrcRGB = srcRgb;
		s_StateInfo.BlendState.DestRGB = destRgb;

		glBlendFunc(srcRgb, destRgb);
	}

	void GLStateManager::BlendFuncSeparate(SrcFactor srcRgb, DestFactor destRgb, SrcFactor srcAlpha, DestFactor destAlpha)
	{
		BlendFuncSeparate((int)srcRgb, (int)destRgb, (int)srcAlpha, (int)destAlpha);
	}

	void GLStateManager::BlendFuncSeparate(int srcRgb, int destRgb, int srcAlpha, int destAlpha)
	{
		if (srcRgb == s_StateInfo.BlendState.SrcRGB && destRgb == s_StateInfo.BlendState.DestRGB &&
			srcAlpha == s_StateInfo.BlendState.SrcAlpha && destAlpha == s_StateInfo.BlendState.DestAlpha)
			return;

		s_StateInfo.BlendState.SrcRGB = srcRgb;
		s_StateInfo.BlendState.DestRGB = destRgb;
		s_StateInfo.BlendState.SrcAlpha = srcAlpha;
		s_StateInfo.BlendState.DestAlpha = destAlpha;

		glBlendFuncSeparate(srcRgb, destRgb, srcAlpha, destAlpha);
	}

	void GLStateManager::Clear()
	{
		int flags = GL_COLOR_BUFFER_BIT;
		if (s_StateInfo.DepthState.IsEnabled())
			flags |= GL_DEPTH_BUFFER_BIT;

		glClear(flags);
	}

	void GLStateManager::SetClearColour(float r, float g, float b, float a)
	{
		s_StateInfo.ClearColour = { r, g, b, a };
		glClearColor(r, g, b, a);
	}

	void GLStateManager::InfoDump()
	{
		Logger::Info("OpenGL Info:\n\tVersion: {0}\n\tVendor: {1}\n\tDevice: {2}",
			glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	}
}