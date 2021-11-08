#include "tnahpch.h"
#include "GameObject.h"


namespace tnah {
	void GameObject::SetTag(const std::string& tag)
	{
		if(HasComponent<TagComponent>())
		{
			auto& t = GetComponent<TagComponent>();
			t.Tag = tag;
		}
		else
		{
			TNAH_INFO("GameObject {0} Doesnt have a tag component!", GetID());
		}
	}

	std::string GameObject::GetTag()
	{
		if(HasComponent<TagComponent>())
		{
			auto& tag = GetComponent<TagComponent>();
			return tag.Tag;
		}
		TNAH_INFO("GameObject {0} Doesnt have a tag component!", GetID());
		return "";
	}
}
