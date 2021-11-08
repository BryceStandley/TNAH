#include "tnahpch.h"
#include "FileManager.h"

#include <TNAH/Core/Application.h>
#include <filesystem>

namespace tnah {

	ActiveFile* FileManager::s_ActiveFile = new ActiveFile();

	bool FileManager::NewScene()
	{
		auto const wd = std::filesystem::current_path();
		s_ActiveFile->FilePath = wd.string() + "/untitledScene.tnah.scene";
		s_ActiveFile->FileName = "untitledScene";
		s_ActiveFile->IsValid = true;
		return true;
	}


	bool FileManager::OpenScene()
	{
		auto file = Application::OpenFileFromBrowser();
		if(std::strcmp(file.first.data(), "") != 0)
		{
			// the file opened is a valid file
			if(CheckValidFile(file.first))
			{
				// the file is valid, save its path and return true
				s_ActiveFile->FilePath = file.first;
				s_ActiveFile->FileName = Utility::FindFileNameFromPath(file.first);
				s_ActiveFile->IsValid = true;
				return true;
			}
			switch (file.second)
			{
				case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
				case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
				default:break;
			}
			return false;
		}
		switch (file.second)
		{
			case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
			case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
			default:break;
		}
		return false;
	}

	//could potentially merge this with openscene for open file or something, where you pass the strings for the selecting to application function
	bool FileManager::OpenAudio()
	{
		auto file = Application::OpenAudioFromBrowser();
		if(std::strcmp(file.first.data(), "") != 0)
		{
			if(file.first.find(".mp3") != std::string::npos)
			{
				// the file is valid, save its path and return true
				s_ActiveFile->FilePath = file.first;
				s_ActiveFile->FileName = Utility::FindFileNameFromPath(file.first);
				s_ActiveFile->IsValid = true;
				return true;
			}
			switch (file.second)
			{
			case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
			case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
			default:break;
			}
			return false;
		}
		switch (file.second)
		{
		case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
		case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
		default:break;
		}
		return false;
	}

	bool FileManager::OpenMesh()
	{
		auto file = Application::OpenMeshFromBrowser();
		if(std::strcmp(file.first.data(), "") != 0)
		{
			if(file.first.find(".fbx") != std::string::npos)
			{
				// the file is valid, save its path and return true
				s_ActiveFile->FilePath = file.first;
				s_ActiveFile->FileName = Utility::FindFileNameFromPath(file.first);
				s_ActiveFile->IsValid = true;
				return true;
			}
			switch (file.second)
			{
			case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
			case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
			default:break;
			}
			return false;
		}
		switch (file.second)
		{
		case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
		case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
		default:break;
		}
		return false;
	}
	
	bool FileManager::SaveScene()
	{
		if(s_ActiveFile->IsValid)
		{
			return true;
		}
		return false;
	}

	bool FileManager::SaveSceneAs()
	{
		auto file = Application::SaveFileAs(s_ActiveFile->FilePath.c_str());
		if(std::strcmp(file.first.data(), "") != 0)
		{
			if(file.first.find(".tnah.scene") == std::string::npos)
			{
				//file doesnt have the correct file extension, add it to the file path
				file.first += ".tnah.scene";
			}
			
			s_ActiveFile->FilePath = file.first;
			s_ActiveFile->FileName = Utility::FindFileNameFromPath(file.first);
			s_ActiveFile->IsValid = true;
			return true;
		}
		switch (file.second)
		{
			case 1: s_ActiveFile->FileOpenError = FileError::UserClosed; break;
			case 2: s_ActiveFile->FileOpenError = FileError::PathInvalid; break;
			default: break;
		}
		return false;
	}

	ActiveFile* FileManager::GetActiveFile()
	{
		return s_ActiveFile;
	}

	bool FileManager::CheckValidFile(const std::string& filePath)
	{
		if (filePath.find(".tnah.scene") != std::string::npos)
		{
			//The scene is of file .tnah.scene
			return true;
		}

		return false;
	}


}
