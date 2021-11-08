#pragma once

#include <string>

namespace tnah {

	/**
	 * @enum	FileError
	 *
	 * @brief	Values that represent file errors
	 */

	enum class FileError
	{
		None,
		UserClosed,
		PathInvalid
	};

	/**
	 * @struct	ActiveFile
	 *
	 * @brief	An active file.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	struct ActiveFile
	{

		/** @brief	Filename of the file */
		std::string FileName;
		
		/** @brief	Full pathname of the file */
		std::string FilePath;

		/** @brief	True if file is valid, false if not */
		bool IsValid = false;

		/** @brief	The file open error */
		FileError FileOpenError;

		/**
		 * @fn	ActiveFile() :FileName(""), FilePath(""), FileOpenError(FileError::None)
		 *
		 * @brief	Default constructor
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 */

		ActiveFile()
			:FileName(""), FilePath(""), FileOpenError(FileError::None)
		{}
	};

	/**
	 * @class	FileManager
	 *
	 * @brief	Manager for files.
	 *
	 * @author	Bryce Standley
	 * @date	7/09/2021
	 */

	class FileManager
	{
	public:

		/**
		 * @fn	static bool FileManager::NewScene();
		 *
		 * @brief	Creates a new scene
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool NewScene();

		/**
		 * @fn	static bool FileManager::OpenScene();
		 *
		 * @brief	Opens the scene
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool OpenScene();

		/**
		 * @fn	static bool FileManager::OpenAudio();
		 *
		 * @brief	Opens the audio
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool OpenAudio();

		/**
		 * @fn	static bool FileManager::OpenMesh();
		 *
		 * @brief	Opens the mesh
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool OpenMesh();

		/**
		 * @fn	static bool FileManager::SaveScene();
		 *
		 * @brief	Saves the scene
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool SaveScene();

		/**
		 * @fn	static bool FileManager::SaveSceneAs();
		 *
		 * @brief	Saves the scene as
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool SaveSceneAs();

		/**
		 * @fn	static ActiveFile* FileManager::GetActiveFile();
		 *
		 * @brief	Gets active file
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @returns	Null if it fails, else the active file.
		 */

		static ActiveFile* GetActiveFile();

	private:

		/**
		 * @fn	static bool FileManager::CheckValidFile(const std::string& filePath);
		 *
		 * @brief	Check valid file
		 *
		 * @author	Bryce Standley
		 * @date	7/09/2021
		 *
		 * @param 	filePath	Full pathname of the file.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool CheckValidFile(const std::string& filePath);


	private:


		/** @brief	The active file */
		static ActiveFile* s_ActiveFile;

	};

}

