#undef UNICODE

#include "AudioAssetsPathLoader.h"
#include <windows.h>
#include <conio.h>


int SearchDirectory(std::vector<std::string> &refvecFiles,
                    const std::string        &refcstrRootDirectory,
                    const std::string        &refcstrExtension,
                    bool                     bSearchSubdirectories = true)
{
  std::string     strFilePath;             // Filepath
  std::string     strPattern;              // Pattern
  std::string     strExtension;            // Extension
  HANDLE          hFile;                   // Handle to file
  WIN32_FIND_DATA FileInformation;         // File information


  strPattern = refcstrRootDirectory + "\\*.*";

  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if(hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if(FileInformation.cFileName[0] != '.')
      {
        strFilePath.erase();
        strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

        if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          if(bSearchSubdirectories)
          {
            // Search subdirectory
            int iRC = SearchDirectory(refvecFiles,
                                      strFilePath,
                                      refcstrExtension,
                                      bSearchSubdirectories);
            if(iRC)
              return iRC;
          }
        }
        else
        {
          // Check extension
          strExtension = FileInformation.cFileName;
          strExtension = strExtension.substr(strExtension.rfind(".") + 1);

          if(strExtension == refcstrExtension)
          {
            // Save filename
            refvecFiles.push_back(strFilePath);
          }
        }
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

    // Close handle
    ::FindClose(hFile);

    DWORD dwError = ::GetLastError();
    if(dwError != ERROR_NO_MORE_FILES)
      return dwError;
  }

  return 0;
}

std::vector<std::string> AudioAssetsPathLoader::getDefaultSoundPaths()
{
	std::vector<std::string> paths;

	SearchDirectory(paths, "Assets\\Sounds", "wav", true);
	return paths;
}

std::vector<std::string> AudioAssetsPathLoader::getDefaultMusicPaths()
{
	std::vector<std::string> paths;

	SearchDirectory(paths, "Assets\\Music", "wav", false);
	return paths;
}