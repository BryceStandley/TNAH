#pragma once
#include <memory>

#ifdef TNAH_PLATFORM_WINDOWS
	#if TNAH_DYNAMIC_LINK
		#ifdef TNAH_BUILD_DLL
			#define TNAH_API _declspec(dllexport)
		#else
			#define TNAH_API _declspec(dllimport)
		#endif
	#else
		#define TNAH_API
	#endif
#else
	#error TNAH-Engine only supports Windows x64!
#endif


#define TNAH_EXPAND_MACRO(x) x
#define TNAH_STRINGIFY_MACRO(x) #x


#define BIT(x) (1 << x)

#define TNAH_BIND_EVENTS_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace tnah {


	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}

#ifdef TNAH_DEBUG
#if defined(TNAH_PLATFORM_WINDOWS)
#define TNAH_DEBUGBREAK() __debugbreak()
#elif defined(TNAH_PLATFORM_LINUX)
#include <signal.h>
#define TNAH_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define TNAH_ENABLE_ASSERTS
#else
#define TNAH_DEBUGBREAK()
#endif



#ifdef TNAH_ENABLE_ASSERTS

// Alternatively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define TNAH_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { TNAH##type##ERROR(msg, __VA_ARGS__); TNAH_DEBUGBREAK(); } }
#define TNAH_INTERNAL_ASSERT_WITH_MSG(type, check, ...) TNAH_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define TNAH_INTERNAL_ASSERT_NO_MSG(type, check) TNAH_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", TNAH_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define TNAH_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define TNAH_INTERNAL_ASSERT_GET_MACRO(...) TNAH_EXPAND_MACRO( TNAH_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, TNAH_INTERNAL_ASSERT_WITH_MSG, TNAH_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define TNAH_ASSERT(...) TNAH_EXPAND_MACRO( TNAH_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define TNAH_CORE_ASSERT(...) TNAH_EXPAND_MACRO( TNAH_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define TNAH_ASSERT(...)
#define TNAH_CORE_ASSERT(...)
#endif



