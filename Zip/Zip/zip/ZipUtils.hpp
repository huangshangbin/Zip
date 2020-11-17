#pragma once

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

	static void compressData(string targetFilePath, string dataFileName, string& data)
	{
		zip_t * zip = zip_open(targetFilePath.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

		zip_entry_open(zip, dataFileName.c_str());//write target file path
		zip_entry_write(zip, data.c_str(), data.length());
		zip_entry_close(zip);

		zip_close(zip);
	}


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
};

