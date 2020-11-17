
#include <zip/ZipUtils.hpp>


int main()
{
	ZipUtils::compressFile("fileCompress.zip", "E:\\group.txt");

	string data = "huang\nshang\nbin";
	ZipUtils::compressData("dataCompress.zip", "dataCompress.txt", data);

	cout << "complete" << endl;

	string str;
	cin >> str;

	return 0;
}