#pragma once
#include <unordered_map>
#include "Utility.h"
#include <filesystem>

namespace tnah {

	/**
	 * @struct	File
	 *
	 * @brief	Structure of a file, contains a name and a extension.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */
	
	struct File
	{
		std::string FileName;
		std::string Extension;
		std::string FullFile;

		/**
		 * @fn	File() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		File() = default;

		/**
		 * @fn	File(const std::string& name, const std::string& extension)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	name	 	The file name.
		 * @param 	extension	The file extension.
		 */

		File(const std::string& name, const std::string& extension)
			:FileName(name), Extension(extension) { FullFile = FileName + Extension; }

		/**
		 * @fn	operator std::string&()
		 *
		 * @brief	Cast that converts the given  to a string&amp;
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator std::string&() { return FullFile; }
	};

	/**
	 * @typedef	std::string Directory
	 *
	 * @brief	Structure of a directory, contains a path.
	 */
	
	typedef std::string Directory;

	/**
	 * @struct	Folder
	 *
	 * @brief	Structure of a Folder, contains a vector of files inside a root folder path
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */
	
	struct Folder
	{

		/** @brief	Pathname of the files in folder */
		std::vector<File> FilesInFolder;

		/** @brief	The folder root */
		Directory FolderRoot;

		/**
		 * @fn	Folder() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		Folder() = default;
	};

	/**
	 * @struct	Project
	 *
	 * @brief	Structure of a Project, contains a root directory and vector of sub directories.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */
	
	struct Project
	{

		/** @brief	The name */
		std::string Name;

		/** @brief	Pathname of the root directory */
		Directory RootDirectory;

		/** @brief	The sub directories */
		std::vector<Directory> SubDirectories;

		/** @brief	The project files */
		std::unordered_map<Directory, Folder> ProjectFiles;

		/**
		 * @fn	Project(const Directory& root)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	root	The root.
		 */

		Project(const Directory& root)
			:RootDirectory(root) {}

		/**
		 * @fn	operator std::string&()
		 *
		 * @brief	Cast that converts the given  to a string&amp;
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator std::string&() { return RootDirectory; }

		/**
		 * @fn	operator std::vector<Directory>&()
		 *
		 * @brief	Cast that converts the given  to a vector
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	The result of the operation.
		 */

		operator std::vector<Directory>&() { return SubDirectories; }

		/**
		 * @fn	operator std::unordered_map<Directory, Folder>&()
		 *
		 * @brief	Gets the folder>&amp;
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	A std::unordered_map&lt;Directory.
		 */

		operator std::unordered_map<Directory, Folder>&() { return ProjectFiles; }
	};

	/**
	 * @enum	RType
	 *
	 * @brief	Values that represent types
	 */

	enum class RType
	{
		EMPTY, Unknown, Model, Image, Texture, Shader, Audio, Material, TNAH
	};

	/**
	 * @enum	RSubType
	 *
	 * @brief	Values that represent sub types
	 */

	enum class RSubType
	{
		EMPTY, ILLEGAL_SUBTYPE,
		PBR_Material,
		Heightmap, UI_Image, Texture_2D, Texture_3D,
		Vertex_Shader, Fragment_Shader,
		Audio_Clip,
		TNAH_Scene, TNAH_Project, TNAH_Resource, TNAH_Prefab
	};

	/**
	 * @struct	ResourceType
	 *
	 * @brief	A resource type.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	struct ResourceType
	{

		/** @brief	The type */
		RType Type = RType::EMPTY;

		/** @brief	The sub type */
		RSubType SubType = RSubType::EMPTY;

		/**
		 * @fn	ResourceType() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		ResourceType() = default;

		/**
		 * @fn	ResourceType(const RType& type, const RSubType& subType)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	type   	The type.
		 * @param 	subType	The subtype.
		 */

		ResourceType(const RType& type, const RSubType& subType)
			:Type(type)
		{
			if(type != RType::EMPTY && subType != RSubType::EMPTY)
			{
				switch (type)
				{
					case RType::Model: // No Subtype for models yet
						break;
					case RType::Image:
						if(subType != RSubType::Heightmap && subType != RSubType::UI_Image)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Texture:
						if(subType != RSubType::Texture_2D && subType != RSubType::Texture_3D)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Shader:
						if(subType != RSubType::Vertex_Shader && subType != RSubType::Fragment_Shader)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Audio:
						if(subType != RSubType::Audio_Clip)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Material:
						if(subType != RSubType::PBR_Material)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
				case RType::TNAH:
					if(subType != RSubType::TNAH_Scene && subType != RSubType::TNAH_Prefab && subType != RSubType::TNAH_Project && subType != RSubType::TNAH_Resource)
						SubType = RSubType::ILLEGAL_SUBTYPE;
					else
						SubType = subType;
					break;
					default:
						SubType = RSubType::EMPTY;
						break;
					case RType::EMPTY: break;
					case RType::Unknown: break;
				}
			}
		}

		/**
		 * @fn	static RType GuessType(const std::string& fileExtension)
		 *
		 * @brief	Guess type of the file from its extension
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	fileExtension	The file extension.
		 *
		 * @returns	A RType.
		 */

		static RType GuessType(const std::string& fileExtension)
		{
			std::string modelGuess[] = {
				"fbx", "obj", "c4d", "3ds",
				"dae"
			};

			std::string imageGuess[] = {
				"jpg", "png", "tga", "gif", "tiff",
				"raw", "bmp", "jpeg", "tif", "ktx",
				"ktx2"
			};

			std::string audioGuess[] = {
				"mp3", "wav"
			};

			std::string shaderGuess[] = {
				"glsl", "vert", "frag",
				"txt"
			};

			std::string materialGuess[] = {
				"material", "mat", "pbr"
			};

			std::string customGuess[] = {
				"tnah.scene", "tnahproj", "tnah.resource"
				, "tnah.meta", "tnah.prefab"
			};

			for(auto s : modelGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Model;
			}

			for(auto s : imageGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Image;
			}
			for(auto s : audioGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Audio;
			}
			for(auto s : shaderGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Shader;
			}
			for(auto s : materialGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Material;
			}

			for(auto s : customGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::TNAH;
			}

			return RType::Unknown;
		}
	};

	/**
	 * @struct	Resource
	 *
	 * @brief	A resource.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	struct Resource
	{

		/** @brief	CustomName of the resource */
		std::string CustomName = "";

		/** @brief	Pathname of the relative directory */
		Directory RelativeDirectory = Directory("");

		/** @brief	Pathname of the root directory */
		Directory RootDirectory = Directory("");

		/** @brief	Pathname of the absolute directory */
		Directory AbsoluteDirectory = Directory("");

		/** @brief	Filename of the file */
		File FileName = File("", "");

		/** @brief	The type */
		ResourceType Type = ResourceType(RType::EMPTY, RSubType::EMPTY);

		/**
		 * @fn	Resource() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		Resource() = default;

		/**
		 * @fn	Resource(const Directory& fileDirectory, const File& fileName, const ResourceType& resourceType)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	fileDirectory	Pathname of the file directory.
		 * @param 	fileName	 	Filename of the file.
		 * @param 	resourceType 	Type of the resource.
		 */

		Resource(const Directory& fileDirectory, const File& fileName, const ResourceType& resourceType)
			:RootDirectory(fileDirectory), FileName(fileName), Type(resourceType)
		{
			AbsoluteDirectory = RootDirectory + "/" + FileName.FullFile;
		}

		/**
		 * @fn	Resource(const std::string& fileDirectory, const std::string& fileName, const ResourceType& resourceType)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	fileDirectory	Pathname of the file directory.
		 * @param 	fileName	 	Filename of the file.
		 * @param 	resourceType 	Type of the resource.
		 */

		Resource(const std::string& fileDirectory, const std::string& fileName, const ResourceType& resourceType)
			:RootDirectory(fileDirectory), Type(resourceType)
		{
			auto n = Utility::SplitFileNameAndExtension(fileName);
			FileName.FileName = n.first;
			FileName.Extension = n.second;
			FileName.FullFile = fileName;
			AbsoluteDirectory = RootDirectory + "/" + fileName;
		}

		/**
		 * @fn	Resource(const std::string& relativeFilePath)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	relativeFilePath	Full pathname of the relative file.
		 */

		Resource(const std::string& relativeFilePath)
		{
			if(relativeFilePath.find("\\/") != std::string::npos)
			{
				auto dirSplit = Utility::SplitDirectoryAndFilePath(relativeFilePath);
				RootDirectory = dirSplit.first;
				FileName.FullFile = dirSplit.second;
				auto nameSplit = Utility::SplitFileNameAndExtension(dirSplit.second);
				FileName.FileName = nameSplit.first;
				FileName.Extension = nameSplit.second;
				Type.Type = ResourceType::GuessType(FileName.Extension);
				AbsoluteDirectory = relativeFilePath;
				RelativeDirectory = Utility::RelativePathFromAbsolute(relativeFilePath);
				CustomName = nameSplit.first;
			}
			else
			{
				auto dirSplit = Utility::SplitDirectoryAndFilePath(relativeFilePath);
				RootDirectory = dirSplit.first;
				FileName.FullFile = dirSplit.second;
				auto nameSplit = Utility::SplitFileNameAndExtension(dirSplit.second);
				FileName.FileName = nameSplit.first;
				FileName.Extension = nameSplit.second;
				Type.Type = ResourceType::GuessType(FileName.Extension);
				AbsoluteDirectory = Utility::AbsolutePathFromRelative(relativeFilePath);
				RelativeDirectory = relativeFilePath;
				CustomName = nameSplit.first;
			}
		}


		
		
	};
}