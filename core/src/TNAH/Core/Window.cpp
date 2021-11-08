#include "tnahpch.h"
#include "TNAH/Core/Window.h"

#ifdef TNAH_PLATFORM_WINDOWS
#include "Platform/Windows/WinWindow.h"
#endif

namespace tnah
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef TNAH_PLATFORM_WINDOWS
			return CreateScope<WinWindow>(props);
		#else
			TNAH_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}