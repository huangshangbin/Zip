#pragma once

#include <io.h>

#include <iostream>
#include <string>

using namespace std;

#include <zip/zip.h>

class ZipUtils
{
public:
	static void compressFile(string targetFilePath, string srcFilePath)
	{
		zip_t * zip = zip_open(targetFilePath.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

		zip_entry_open(zip, getFileOrDirName(srcFilePath).c_str());//write target file path
		zip_entry_fwrite(zip, srcFilePath.c_str());//src file path
		zip_entry_close(zip);

		zip_close(zip);
	}

	static void compressDir(string targetFilePath, string dirPath)
	{
		zip_t* zip = zip_open(targetFilePath.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

		compressDirHelp(zip, dirPath, dirPath);

		zip_close(zip);
	}

	static void compressData(string targetFilePath, string dataFileName, string& data)
	{
		zip_t * zip = zip_open(targetFilePath.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

		zip_entry_open(zip, dataFileName.c_str());//write target file path
		zip_entry_write(zip, data.c_str(), data.length());
		zip_entry_close(zip);

		zip_close(zip);
	}

	static void decompression(string zipFilePath, string targetPath)
	{
		int arg = 2;
		zip_extract(zipFilePath.c_str(), targetPath.c_str(), [](const char* fileName, void* arg) {
			return 0;
		}, &arg);
	}

//compressFile
private:
	static string getFileOrDirName(string path)
	{
		int index;
		for (int i = path.length(); i > 0; i--)
		{
			if (i == 0)
			{
				return path;
			}

			if (path[i] == '\\')
			{
				index = i;
				break;
			}
		}

		string result = path.substr(index + 1, path.length() - index);
		return result;
	}


//compressDir
private:
	static void compressDirHelp(zip_t* zip, string baseDirPath, string compressdDirPath)
	{
		string path = compressdDirPath + "\\*.*";

		_finddata_t findData;
		intptr_t findHandle = _findfirst(path.c_str(), &findData);
		intptr_t flag = findHandle;

		string dirName;
		while (flag != -1)
		{
			if (findData.attrib == _A_SUBDIR)
			{
				dirName = findData.name;
				if (dirName != "." && dirName != "..")
				{
					string newDirPath = compressdDirPath + "\\" + dirName;

					compressDirHelp(zip, baseDirPath, newDirPath);
				}
			}
			else
			{
				string relativePath = compressdDirPath.substr(baseDirPath.length(), compressdDirPath.length()) + 
					"\\" + findData.name;
				relativePath = getFileOrDirName(baseDirPath) + "\\" + relativePath;

				string filePath = compressdDirPath + "\\" + findData.name;

				zip_entry_open(zip, relativePath.c_str());//write target file path
				zip_entry_fwrite(zip, filePath.c_str());//src file path
				zip_entry_close(zip);
			}

			flag = _findnext(findHandle, &findData);
		}

		_findclose(findHandle);
	}
};

