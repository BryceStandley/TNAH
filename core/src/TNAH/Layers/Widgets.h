#pragma once
#include "imgui.h"
#include "imgui_internal.h"
//----------------------------------------------------------------------------------
// Custom Functions added to ImGui
// Incorporated by Bryce Standley
// Any functions within this file are licenced under the MIT licence
//----------------------------------------------------------------------------------

namespace ImGui {

    /**
    * @author Ocornut
    * @link https://github.com/ocornut
    */
    void ToggleButton(const char* str_id, bool* v);

#if 0
    /**
     * @author Zfedorn
     * @link https://github.com/zfedoran
     */
    static bool BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);

    /**
    * @author Zfedorn
    * @link https://github.com/zfedoran
    */
    static bool LineSpinner(const char* label, float radius, int thickness, const ImU32& color);

    /**
     * @author Ocornut
     * @link https://github.com/ocornut
     */
    static void TextSpinner();

    /**
     * @author Alexsr
     * @link https://github.com/alexsr
     */
    static void DotSpinner(const char* label, const float indicator_radius, const ImVec4& main_color, const ImVec4& backdrop_color, const int circle_count, const float speed);

#endif


}
