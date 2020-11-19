#include <zip/ZipUtils.hpp>


int main()
{
// 	ZipUtils::compressFile("fileCompress.zip", "E:\\group.txt");
// 
// 	string data = "huang\nshang\nbin";
// 	ZipUtils::compressData("dataCompress.zip", "dataCompress.txt", data);

//	ZipUtils::decompression("dataCompress.zip", "E:\\zip");

	ZipUtils::compressDir("dir.zip", "E:\\zip");

	cout << "complete" << endl;

	string str;
	cin >> str;

	return 0;
}