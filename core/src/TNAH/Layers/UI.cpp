#include "tnahpch.h"
#include "UI.h"

#include <glm/gtc/type_ptr.hpp>

#include "ImGuiFileBrowser.h"
#include "imgui_internal.h"
#include "Widgets.h"

//***************************************** Variable Controls ******************************************************************
void tnah::UI::Entry(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    ImGui::Text(format, args);
    va_end(args);
}

void tnah::UI::Entry(const std::string& text)
{
    ImGui::Text(text.c_str());
}

void tnah::UI::Entry(const char* text, bool wrapped)
{
    if(wrapped)
        ImGui::TextWrapped(text);
    else
        ImGui::Text(text);
}

void tnah::UI::Entry(const std::string& text, bool wrapped)
{
    if(wrapped)
        ImGui::TextWrapped(text.c_str());
    else
        ImGui::Text(text.c_str());
}

bool tnah::UI::Entry(const char* label, std::string& value, bool readOnly, bool error)
{
    bool modified = false;
    ImGui::Text(label);
    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);

    char buffer[256];
    strcpy_s<256>(buffer, value.c_str());

    s_IDBuffer[0] = '#';
    s_IDBuffer[1] = '#';
    memset(s_IDBuffer + 2, 0, 14);
    sprintf_s(s_IDBuffer + 2, 14, "%o", s_Counter++);
    std::string name = "##";
    name += label;
		
    const int flags = readOnly ? ImGuiInputTextFlags_ReadOnly : 0; 
		
    if (error)
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
    if (ImGui::InputText(name.c_str(), buffer, 256, flags))
    {
        value = buffer;
        modified = true;
    }
    if (error)
        ImGui::PopStyleColor();
    ImGui::PopItemWidth();
    ImGui::NextColumn();

    return modified;
}

bool tnah::UI::Entry(const std::string& label, std::string& value, bool readOnly, bool error)
{
    return Entry(label.c_str(), value, readOnly, error);
}

bool tnah::UI::Entry(const char* label, float& value, bool readOnly, bool error)
{
    bool modified = false;
    float temp = value;
    ImGui::Text(label);
    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);

    s_IDBuffer[0] = '#';
    s_IDBuffer[1] = '#';
    memset(s_IDBuffer + 2, 0, 14);
    sprintf_s(s_IDBuffer + 2, 14, "%o", s_Counter++);
    std::string name = "##";
    name += label;
		
    const int flags = readOnly ? ImGuiInputTextFlags_ReadOnly : 0; 
		
    if (error)
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
    if (ImGui::InputFloat(name.c_str(), &temp, 0, 0, "%.3f", flags))
    {
        value = temp;
        modified = true;
    }
    if (error)
        ImGui::PopStyleColor();
    ImGui::PopItemWidth();
    ImGui::NextColumn();

    return modified;
}

bool tnah::UI::Entry(std::string& label, float& value, bool readOnly, bool error)
{
    return Entry(label.c_str(), value, readOnly, error);
}

bool tnah::UI::Entry(const char* label, int& value, bool readOnly, bool error)
{
    bool modified = false;
    int temp = value;
    ImGui::Text(label);
    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);

    s_IDBuffer[0] = '#';
    s_IDBuffer[1] = '#';
    memset(s_IDBuffer + 2, 0, 14);
    sprintf_s(s_IDBuffer + 2, 14, "%o", s_Counter++);
    std::string name = "##";
    name += label;
		
    const int flags = readOnly ? ImGuiInputTextFlags_ReadOnly : 0; 
		
    if (error)
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
    if (ImGui::InputInt(name.c_str(), &temp, 0, 0, flags))
    {
        value = temp;
        modified = true;
    }
    if (error)
        ImGui::PopStyleColor();
    ImGui::PopItemWidth();
    ImGui::NextColumn();

    return modified;
}

bool tnah::UI::Entry(std::string& label, int& value, bool readOnly, bool error)
{
    return Entry(label.c_str(), value, readOnly, error);
}

bool tnah::UI::Entry(const char* label, bool& value, bool readOnly)
{
    return EntryCheckbox(label, value, readOnly);
}

bool tnah::UI::Entry(std::string& label, bool& value, bool readOnly)
{
    return EntryCheckbox(label.c_str(), value, readOnly);
}

bool tnah::UI::Entry(const char* label, glm::vec2& value, bool readOnly, float resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::InputFloat2("##XY", glm::value_ptr(value));
    else ImGui::InputFloat2("##XY", glm::value_ptr(value), "%.3f", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = {resetValue, resetValue};
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::Entry(std::string& label, glm::vec2& value, bool readOnly, float resetValue)
{
    return Entry(label.c_str(), value, readOnly, resetValue);
}

bool tnah::UI::Entry(const char* label, glm::vec3& value, bool readOnly, float resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::InputFloat3("##XYZ", glm::value_ptr(value));
    else ImGui::InputFloat3("##XYZ", glm::value_ptr(value), "%.3f", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = {resetValue, resetValue, resetValue};
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::Entry(std::string& label, glm::vec3& value, bool readOnly, float resetValue)
{
    return Entry(label.c_str(), value, readOnly, resetValue);
}

bool tnah::UI::Entry(const char* label, glm::vec4& value, bool readOnly, float resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::InputFloat4("##XYZW", glm::value_ptr(value));
    else ImGui::InputFloat4("##XYZW", glm::value_ptr(value), "%.3f", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = {resetValue, resetValue, resetValue, resetValue};
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::Entry(std::string& label, glm::vec4& value, bool readOnly, float resetValue)
{
    return Entry(label.c_str(), value, readOnly, resetValue);
}

//***************************************** Slider Controls ******************************************************************
bool tnah::UI::EntrySlider(const char* label, int& value, bool readOnly, int min, int max, int resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::SliderInt("##V", &value, min, max);
    else ImGui::SliderInt("##V", &value, min,max, "%d", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = resetValue;
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::EntrySlider(const std::string& label, int& value, bool readOnly, int min, int max , int resetValue)
{
    return EntrySlider(label.c_str(), value, readOnly, min, max, resetValue);
}

bool tnah::UI::EntrySlider(const char* label, float& value, bool readOnly, float min, float max, float resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::SliderFloat("##V", &value, min, max);
    else ImGui::SliderFloat("##V", &value, min,max, "%d", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = resetValue;
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::EntrySlider(const std::string& label, float& value,bool readOnly, float min, float max, float resetValue)
{
    return EntrySlider(label.c_str(), value, readOnly, min, max, resetValue);
}

bool tnah::UI::EntrySlider(const char* label, glm::vec2& value,bool readOnly, float min, float max, float resetValue)
{
     bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##X", &value.x, min, max,  "%.2f");
		else ImGui::Text("%.3f", value.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##Y", &value.y, min, max, "%.2f");
		else ImGui::Text("%.3f", value.y);
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
		ImGui::NewLine();

		return modified;
}

bool tnah::UI::EntrySlider(const std::string& label, glm::vec2& value,bool readOnly, float min, float max, float resetValue)
{
    return EntrySlider(label.c_str(), value, readOnly, min, max, resetValue);
}

bool tnah::UI::EntrySlider(const char* label, glm::vec3& value,bool readOnly, float min, float max, float resetValue)
{
    bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##X", &value.x, min, max,  "%.2f");
		else ImGui::Text("%.3f", value.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##Y", &value.y, min, max, "%.2f");
		else ImGui::Text("%.3f", value.y);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Z", buttonSize))
		{
			value.z = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##Z", &value.z, min, max, "%.2f");
		else ImGui::Text("%.3f", value.z);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
		ImGui::NewLine();

		return modified;
}

bool tnah::UI::EntrySlider(const std::string& label, glm::vec3& value,bool readOnly, float min, float max, float resetValue)
{
	return EntrySlider(label.c_str(), value, readOnly, min, max, resetValue);
}

bool tnah::UI::EntrySlider(const char* label, glm::vec4& value,bool readOnly, float min, float max, float resetValue)
{
    bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##X", &value.x, min, max,  "%.2f");
		else ImGui::Text("%.3f", value.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##Y", &value.y, min, max, "%.2f");
		else ImGui::Text("%.3f", value.y);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Z", buttonSize))
		{
			value.z = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##Z", &value.z, min, max, "%.2f");
		else ImGui::Text("%.3f", value.z);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("W", buttonSize))
		{
			value.w = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::SliderFloat("##W", &value.w, min, max, "%.2f");
		else ImGui::Text("%.3f", value.w);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

		return modified;
}

bool tnah::UI::EntrySlider(const std::string& label, glm::vec4& value,bool readOnly, float min, float max, float resetValue)
{
    return EntrySlider(label.c_str(), value, readOnly, min, max, resetValue);
}


//***************************************** Drag Controls ******************************************************************

bool tnah::UI::EntryDrag(const char* label, int& value, bool readOnly, int speed, int min, int max, int resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::SliderInt("##V", &value, min, max);
    else ImGui::DragInt("##V", &value, speed, min,max, "%d", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = resetValue;
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::EntryDrag(const std::string& label, int& value, bool readOnly, int speed, int min, int max, int resetValue)
{
    return EntryDrag(label.c_str(), value, readOnly, speed, min, max, resetValue);
}

bool tnah::UI::EntryDrag(const char* label, float& value, bool readOnly, float speed, float min, float max, float resetValue)
{
    bool modified = false;
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, 100.0f);
    ImGui::Text(label);
    ImGui::NextColumn();
    
    if(!readOnly) modified |= ImGui::DragFloat("##V", &value, speed, min, max);
    else ImGui::DragFloat("##V", &value, speed, min,max, "%d", ImGuiInputTextFlags_ReadOnly);

    if(!readOnly)
    {
        const ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        ImGui::SameLine();
        if(ImGui::Button("Reset", buttonSize))
        {
            value = resetValue;
            modified = true;
        }
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    return modified;
}

bool tnah::UI::EntryDrag(const std::string& label, float& value,bool readOnly, float speed, float min, float max, float resetValue)
{
    return EntryDrag(label.c_str(), value, readOnly,speed, min, max, resetValue);
}

bool tnah::UI::EntryDrag(const char* label, glm::vec2& value,bool readOnly, float speed, float min, float max, float resetValue)
{
     bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##X", &value.x, speed, min, max,  "%.2f");
		else ImGui::Text("%.3f", value.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Y", &value.y,speed, min, max, "%.2f");
		else ImGui::Text("%.3f", value.y);
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
		ImGui::NewLine();

		return modified;
}

bool tnah::UI::EntryDrag(const std::string& label, glm::vec2& value,bool readOnly, float speed, float min, float max, float resetValue)
{
    return EntryDrag(label.c_str(), value, readOnly, speed, min, max, resetValue);
}

bool tnah::UI::EntryDrag(const char* label, glm::vec3& value,bool readOnly, float speed, float min, float max, float resetValue)
{
    bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##X", &value.x, speed, min, max,  "%.2f");
		else ImGui::Text("%.3f", value.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Y", &value.y, speed, min, max, "%.2f");
		else ImGui::Text("%.3f", value.y);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Z", buttonSize))
		{
			value.z = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Z", &value.z, speed, min, max, "%.2f");
		else ImGui::Text("%.3f", value.z);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
		ImGui::NewLine();

		return modified;
}

bool tnah::UI::EntryDrag(const std::string& label, glm::vec3& value,bool readOnly, float speed, float min, float max, float resetValue)
{
	return EntryDrag(label.c_str(), value, readOnly, speed,  min, max, resetValue);
}

bool tnah::UI::EntryDrag(const char* label, glm::vec4& value,bool readOnly, float speed, float min, float max, float resetValue)
{
    bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			value.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##X", &value.x, speed, min, max,  "%.2f");
		else ImGui::Text("%.3f", value.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Y", &value.y, speed, min, max, "%.2f");
		else ImGui::Text("%.3f", value.y);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Z", buttonSize))
		{
			value.z = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Z", &value.z, speed, min, max, "%.2f");
		else ImGui::Text("%.3f", value.z);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("W", buttonSize))
		{
			value.w = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##W", &value.w, speed, min, max, "%.2f");
		else ImGui::Text("%.3f", value.w);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

		return modified;
}

bool tnah::UI::EntryDrag(const std::string& label, glm::vec4& value,bool readOnly, float speed, float min, float max, float resetValue)
{
    return EntryDrag(label.c_str(), value, readOnly, speed, min, max, resetValue);
}


//***************************************** Color Controls ******************************************************************
bool tnah::UI::EntryColor(const char* label, glm::vec3& value, bool readOnly)
{
	bool modified = false;
	ImGui::PushID(label);
	ImGui::Text(label);
	ImGui::NextColumn();
	ImGui::PushItemWidth(-1);
		
	if(!readOnly)
	{
		if(ImGui::ColorEdit3("##C", glm::value_ptr(value)))
			modified = true;
	}
	else
	{
		ImGui::InputFloat3("##C", glm::value_ptr(value), "%.3f", ImGuiInputTextFlags_ReadOnly);
	}
	ImGui::PopItemWidth();
	ImGui::NextColumn();
	ImGui::PopID();
		
	return modified;
}

bool tnah::UI::EntryColor(const std::string& label, glm::vec3& value, bool readOnly)
{
	return EntryColor(label.c_str(), value, readOnly);
}

bool tnah::UI::EntryColor(const char* label, glm::vec4& value, bool readOnly)
{
	bool modified = false;
	ImGui::PushID(label);
	ImGui::Text(label);
	ImGui::NextColumn();
	ImGui::PushItemWidth(-1);
		
	if(!readOnly)
	{
		if(ImGui::ColorEdit4("##C", glm::value_ptr(value)))
			modified = true;
	}
	else
	{
		ImGui::InputFloat4("##C", glm::value_ptr(value), "%.3f", ImGuiInputTextFlags_ReadOnly);
	}
	ImGui::PopItemWidth();
	ImGui::NextColumn();
	ImGui::PopID();
		
	return modified;
}

bool tnah::UI::EntryColor(const std::string& label, glm::vec4& value, bool readOnly)
{
	return EntryColor(label.c_str(), value, readOnly);
}

//***************************************** Checkbox Controls ******************************************************************

bool tnah::UI::EntryCheckbox(const char* label, bool& value, bool readOnly)
{
	bool modified = false;
	ImGui::PushID(label);
	ImGui::Text(label);
	ImGui::NextColumn();
	ImGui::PushItemWidth(-1);
	if(!readOnly)
	{
		if(ImGui::Checkbox("##CK", &value))
		{
			modified = true;
		}
	}
	else
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		static bool disabled = value;
		if(ImGui::Checkbox("##Ck", &disabled))
		{
			//always keep the value to the original
			disabled = value;
		}
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
	return modified;
}

bool tnah::UI::EntryCheckbox(const std::string& label, bool& value, bool readOnly)
{
	return EntryCheckbox(label.c_str(), value, readOnly);
}


//***************************************** Dropdown Controls ******************************************************************
bool tnah::UI::EntryDropdown(const char* label, const char** options, uint32_t optionCount, uint32_t* selectedOption)
{
	const char* current = options[*selectedOption];
	ImGui::Text(label);
	ImGui::NextColumn();
	ImGui::PushItemWidth(-1);

	bool changed = false;

	const std::string id = "##" + std::string(label);
	if (ImGui::BeginCombo(id.c_str(), current))
	{
		for (uint32_t i = 0; i < optionCount; i++)
		{
			const bool is_selected = (current == options[i]);
			if (ImGui::Selectable(options[i], is_selected))
			{
				current = options[i];
				*selectedOption = i;
				changed = true;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PopItemWidth();
	ImGui::NextColumn();

	return changed;
}

bool tnah::UI::EntryDropdown(const std::string& label, const char** options, uint32_t optionCount,
    uint32_t* selectedOption)
{
	return EntryDropdown(label.c_str(), options, optionCount, selectedOption);
}

bool tnah::UI::EntryDropdown(const char* label, const std::vector<std::string>& options, uint32_t optionCount,
    uint32_t* selectedOption)
{
	const char* current = options[*selectedOption].c_str();
	ImGui::Text(label);
	ImGui::NextColumn();
	ImGui::PushItemWidth(-1);

	bool changed = false;

	const std::string id = "##" + std::string(label);
	if (ImGui::BeginCombo(id.c_str(), current))
	{
		for (uint32_t i = 0; i < optionCount; i++)
		{
			const bool is_selected = (current == options[i]);
			if (ImGui::Selectable(options[i].c_str(), is_selected))
			{
				current = options[i].c_str();
				*selectedOption = i;
				changed = true;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PopItemWidth();
	ImGui::NextColumn();

	return changed;
}

bool tnah::UI::EntryDropdown(const std::string& label, const std::vector<std::string>& options, uint32_t optionCount,
    uint32_t* selectedOption)
{
	return EntryDropdown(label.c_str(), options, optionCount, selectedOption);
}


//***************************************** Organisation ******************************************************************
bool tnah::UI::EntryCollapsable(const char* label)
{
	return ImGui::CollapsingHeader(label);
}

bool tnah::UI::EntryCollapsable(const std::string& label)
{
	return  EntryCollapsable(label.c_str());
}

bool tnah::UI::BeginTable(const char* label, int columnCount, ImGuiTableFlags flags)
{
	return ImGui::BeginTable(label, columnCount, flags);
}

bool tnah::UI::BeginTable(const std::string& label, int columnCount, ImGuiTableFlags flags)
{
	return BeginTable(label.c_str(), columnCount, flags);
}

void tnah::UI::EndTable()
{
	ImGui::EndTable();
}

//***************************************** Images and Image Buttons ******************************************************************
void tnah::UI::Image(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1,
	const ImVec4& tint_color, const ImVec4& border_color)
{
	ImGui::Image((ImTextureID)(size_t)texture->GetRendererID(), size, uv0, uv1, tint_color, border_color);
}

bool tnah::UI::ImageButton(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1,
    int frame_padding, const ImVec4& bg_color, const ImVec4& tint_color)
{
	return ImGui::ImageButton((ImTextureID)(size_t)texture->GetRendererID(), size, uv0, uv1, frame_padding, bg_color, tint_color);
}


//***************************************** Window Controls ******************************************************************

void tnah::UI::BeginDockingWindow(const std::string& label, bool& open, ImGuiWindowFlags flags)
{
}

void tnah::UI::EndDockingWindow()
{
}

void tnah::UI::BeginWindow(const char* label, bool& open, ImGuiWindowFlags flags)
{
	ImGui::Begin(label, &open, flags);
}

void tnah::UI::BeginWindow(const std::string& label, bool& open, ImGuiWindowFlags flags)
{
	ImGui::Begin(label.c_str(), &open, flags);
}

void tnah::UI::EndWindow()
{
	ImGui::End();
}

void tnah::UI::BeginSubWindow(const std::string& label, ImVec2 size, bool border, ImGuiWindowFlags flags)
{
	ImGui::BeginChild(label.c_str(), size, border, flags);
}
void tnah::UI::BeginSubWindow(const char* label, ImVec2 size, bool border, ImGuiWindowFlags flags)
{
	ImGui::BeginChild(label, size, border, flags);
}

void tnah::UI::EndSubWindow()
{
	ImGui::EndChild();
}

bool tnah::UI::BeginMenuBar()
{
	return ImGui::BeginMainMenuBar();
}

void tnah::UI::EndMenuBar()
{
	ImGui::EndMainMenuBar();
}

bool tnah::UI::BeginSubMenu(const std::string& label)
{
	return ImGui::BeginMenu(label.c_str());
}

bool tnah::UI::BeginSubMenu(const char* label)
{
	return ImGui::BeginMenu(label);
}

void tnah::UI::EndSubMenu()
{
	ImGui::EndMenu();
}

bool tnah::UI::EntryMenu(const char* label, const char* shortcut, bool selected, bool enabled)
{
	return ImGui::MenuItem(label, shortcut, selected, enabled);
}

bool tnah::UI::EntryMenu(const std::string& label, const char* shortcut, bool selected, bool enabled)
{
	return EntryMenu(label.c_str(), shortcut, selected, enabled);
}

bool tnah::UI::EntryMenu(const std::string& label, const std::string& shortcut, bool selected, bool enabled)
{
	return EntryMenu(label.c_str(), shortcut.c_str(), selected, enabled);
}

void tnah::UI::EntrySeparator(SeparatorStyle style)
{
	switch (style)
	{
	case SeparatorStyle::Line:
		ImGui::Separator();
		break;
	case SeparatorStyle::Space:
		ImGui::NewLine();
		break;
	default: break;
	}
}

void tnah::UI::EntryLine(LineFlag flag)
{
	switch (flag)
	{
	case LineFlag::SameLine:
		ImGui::SameLine();
		break;
	case LineFlag::NextLine:
		ImGui::NewLine();
		break;
	default: break;
	}
}

void tnah::UI::PushID(ImGuiStyleVar id)
{
	ImGui::PushID(id);
}

void tnah::UI::PopID()
{
	ImGui::PopID();
}

void tnah::UI::PushStyle(ImGuiStyleVar idx, ImVec2 value)
{
	ImGui::PushStyleVar(idx, value);
}

void tnah::UI::PushStyle(ImGuiStyleVar idx, float value)
{
	ImGui::PushStyleVar(idx, value);
}

void tnah::UI::PopStyle(int count)
{
	ImGui::PopStyleVar(count);
}

void tnah::UI::PushColor(ImGuiColorEditFlags idx, ImVec4 value)
{
	ImGui::PushStyleColor(idx, value);
}

void tnah::UI::PopColor(int count)
{
	ImGui::PopStyleColor(count);
}

bool tnah::UI::IsFocused()
{
	return ImGui::IsWindowFocused();
}

void tnah::UI::SetWindowPosition(const ImVec2& position)
{
	ImGui::SetNextWindowPos(position);
}

void tnah::UI::SetWindowPosition(const glm::vec2& position)
{
	ImGui::SetWindowPos({position.x, position.y});
}

void tnah::UI::SetWindowPosition(const float& x, const float& y)
{
	ImGui::SetNextWindowPos({x,y});
}

glm::vec2 tnah::UI::GetWindowPosition()
{
	return glm::vec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
}

glm::vec2 tnah::UI::GetWindowMinPosition()
{
	auto pos = ImGui::GetItemRectMin();
	return glm::vec2(pos.x, pos.y);
}

glm::vec2 tnah::UI::GetWindowMaxPosition()
{
	auto pos = ImGui::GetItemRectMax();
	return glm::vec2(pos.x, pos.y);
}

void tnah::UI::SetWindowSize(const ImVec2& size)
{
	ImGui::SetNextWindowSize(size);
}

void tnah::UI::SetWindowSize(const glm::vec2& size)
{
	ImGui::SetNextWindowSize({size.x, size.y});
}

void tnah::UI::SetWindowSize(const float& x, const float& y)
{
	ImGui::SetNextWindowSize({x, y});
}

glm::vec2 tnah::UI::GetWindowSize()
{
	auto size = ImGui::GetWindowSize();
	return glm::vec2(size.x, size.y);
}

void tnah::UI::SetCursorPosition(const ImVec2& position)
{
	ImGui::SetCursorPos(position);
}

void tnah::UI::SetCursorPosition(const glm::vec2& position)
{
	ImGui::SetCursorPos({position.x, position.y});
}

void tnah::UI::SetCursorPosition(const float& x, const float& y)
{
	ImGui::SetCursorPos({x,y});
}

void tnah::UI::SetWindowAlpha(const float& alpha)
{
	ImGui::SetNextWindowBgAlpha(alpha);
}

void tnah::UI::SetWindowBackgroundColor(const ImVec4& bg_color)
{
	PushColor(ImGuiCol_WindowBg, bg_color);
}

void tnah::UI::SetWindowBackgroundColor(const glm::vec4& bg_color)
{
	PushColor(ImGuiCol_WindowBg, {bg_color.x, bg_color.y, bg_color.z, bg_color.w});
}

void tnah::UI::SetWindowBackgroundColor(const glm::vec3& bg_color, const float& alpha)
{
	ImVec4 col = {bg_color.x, bg_color.y, bg_color.z, alpha};
	PushColor(ImGuiCol_WindowBg, col);
}

void tnah::UI::SetWindowRounding(const float& value)
{
	PushStyle(ImGuiStyleVar_WindowRounding, value);
}

void tnah::UI::SetWindowPadding(const ImVec2& value)
{
	PushStyle(ImGuiStyleVar_WindowPadding, value);
}

void tnah::UI::SetWindowPadding(const glm::vec2& value)
{
	PushStyle(ImGuiStyleVar_WindowPadding, {value.x, value.y});
}

void tnah::UI::ClearWindowRounding()
{
	PopStyle();
}

void tnah::UI::ClearWindowPadding()
{
	PopStyle();
}

glm::vec2 tnah::UI::GetContentSpaceAvailable()
{
	auto s = ImGui::GetContentRegionAvail();
	return glm::vec2(s.x, s.y);
}

//***************************************** Buttons ******************************************************************

bool tnah::UI::Button(const std::string& label, const ImVec2& size)
{
	return ImGui::Button(label.c_str(), size);
}

bool tnah::UI::Button(const char* label, const ImVec2& size)
{
	return ImGui::Button(label, size);
}

void tnah::UI::SetButtonColors(const ImVec4& idleColor, const ImVec4& hoverColor, const ImVec4& pressedColor)
{
	ImGui::PushStyleColor(ImGuiCol_Button, idleColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, pressedColor);
}

void tnah::UI::SetButtonColors(const glm::vec4& idleColor, const glm::vec4& hoverColor, const glm::vec4& pressedColor)
{
	ImVec4 i = {idleColor.x, idleColor.y, idleColor.z, idleColor.w};
	ImVec4 h = {hoverColor.x, hoverColor.y, hoverColor.z, hoverColor.w};
	ImVec4 p = {pressedColor.x, pressedColor.y, pressedColor.z, pressedColor.w};
	SetButtonColors(i, h, p);
}

void tnah::UI::SetButtonStateColor(const ImVec4& color, ImGuiCol buttonState)
{
	PushColor(buttonState, color);
}

void tnah::UI::SetButtonStateColor(const glm::vec4& color, ImGuiCol buttonState)
{
	ImVec4 b = {color.x, color.y, color.z, color.w};
	PushColor(buttonState, b);
}

void tnah::UI::SetButtonIdleColor(const ImVec4& color)
{
	PushColor(ImGuiCol_Button, color);
}

void tnah::UI::SetButtonIdleColor(const glm::vec4& color)
{
	ImVec4 b = {color.x, color.y, color.z, color.w};
	PushColor(ImGuiCol_Button, b);
}

void tnah::UI::SetButtonHoverColor(const ImVec4& color)
{
	PushColor(ImGuiCol_ButtonHovered, color);
}

void tnah::UI::SetButtonHoverColor(const glm::vec4& color)
{
	ImVec4 b = {color.x, color.y, color.z, color.w};
	PushColor(ImGuiCol_ButtonHovered, b);
}

void tnah::UI::SetButtonPressedColor(const ImVec4& color)
{
	PushColor(ImGuiCol_ButtonActive, color);
}

void tnah::UI::SetButtonPressedColor(const glm::vec4& color)
{
	ImVec4 b = {color.x, color.y, color.z, color.w};
	PushColor(ImGuiCol_ButtonActive, b);
}

void tnah::UI::ClearButtonIdleColor()
{
	PopColor();
}

void tnah::UI::ClearButtonHoverColor()
{
	PopColor();
}

void tnah::UI::ClearButtonPressedColor()
{
	PopColor();
}

void tnah::UI::ClearButtonColors()
{
	PopColor(3);
}

void tnah::UI::ClearButtonColor()
{
	PopColor();
}

//***************************************** Fonts ******************************************************************

void tnah::UI::SetFont(ImFont* font)
{
	ImGui::PushFont(font);
}

ImFont* tnah::UI::LoadFont(const char* fontPath, float size_pixels)
{
	ImGuiIO& io = ImGui::GetIO();
	return io.Fonts->AddFontFromFileTTF(fontPath, size_pixels);
}

void tnah::UI::LoadFonts(const char* rootFontPath, float size_pixels)
{
	// TODO: find all files in this directory and load them as normal
}

ImFont* tnah::UI::LoadFont(const std::string& fontPath, float size_pixels)
{
	return LoadFont(fontPath.c_str(), size_pixels);
}

void tnah::UI::LoadFonts(const std::string& rootFontPath, float size_pixels)
{
	LoadFonts(rootFontPath.c_str(), size_pixels);
}

std::vector<ImFont*> tnah::UI::LoadFonts(const std::vector<std::string>& fontPaths, float size_pixels)
{
	std::vector<ImFont*> fonts;
	for(auto p : fontPaths)
	{
		fonts.emplace_back(LoadFont(p.c_str(), size_pixels));
	}
	return fonts;
}

std::list<ImFont*> tnah::UI::LoadFonts(const std::list<std::string>& fontPaths, float size_pixels)
{
	std::list<ImFont*> fonts;
	for(auto p : fontPaths)
	{
		fonts.emplace_back(LoadFont(p.c_str(), size_pixels));
	}
	return fonts;
}

void tnah::UI::SetDefaultFont(const char* fontPath, float size_pixels)
{
	ImGuiIO& io = ImGui::GetIO();
	io.FontDefault = LoadFont(fontPath, size_pixels);
}

void tnah::UI::SetDefaultFont(ImFont* font)
{
	ImGuiIO& io = ImGui::GetIO();
	io.FontDefault = font;
}

//***************************************** Misc Widgets ******************************************************************
std::string tnah::UI::OpenFileBrowser(const char* browserLabel, const FileBrowserMode& mode, const ImVec2& position, const char* validTypes)
{
	imgui_addons::ImGuiFileBrowser browser = imgui_addons::ImGuiFileBrowser();
	if(mode == FileBrowserMode::Open)
	{
		if(browser.showFileDialog(browserLabel, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, position, validTypes))
		{
			return browser.selected_path;
		}

		return "";
	}

	if(mode == FileBrowserMode::Save)
	{
		if(browser.showFileDialog(browserLabel, imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, position, validTypes))
		{
			return browser.selected_path;
		}
		return "";
	}
	
	return "";
}

void tnah::UI::EntryToggleCheckbox(const char* id, bool& value)
{
	ImGui::ToggleButton(id, &value);
}
