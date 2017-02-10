#include "record_offset.h"
#include <stdlib.h>
#include <iostream>

using namespace RECORD;

RecordOffset::RecordOffset(void)
{

}

RecordOffset::~RecordOffset(void)
{
	if (!fout_) 
	{
		fout_.close();		
	}
}

int32_t RecordOffset::init(const std::string &path)
{
	int32_t ret = 0;
	std::cout << "path: " << path << std::endl;
	path_ = path;
	do {
		if (path_.empty()) 
		{
			ret = -1;
			break;
		}

		std::ifstream fin;
		fin.open(path_.c_str()); 
		if (!fin) 
		{
			fin.close();
			fin.open(path_.c_str(), std::ios::out); 	// create new file
			std::cout << "str: " << data_ << std::endl;
		} 
		else
		{
			std::getline(fin, data_);
			if (!data_.empty()) 
			{
				ret = -3;
				break;
			}
		}

		fin.close();	// auto release 
		std::cout << "data_: " << data_ << std::endl;

	} while (false);

	return ret;
}

int32_t RecordOffset::setOffset(const uint64_t arr[], int32_t size)
{
	int32_t ret = 0;

	//fout_.clear();
	fout_.open(path_.c_str());
	if (!fout_) {
		std::cout << "Error!" << std::endl;
	}

	std::string result;

	for (int32_t i = 0; i != size; ++i) 
	{
		std::ostringstream oss;
		oss << arr[i];
		std::string intAsString(oss.str());
		if (i != (size - 1))
		{
			result += intAsString + "|";
		} 
		else 
		{
			result += intAsString + "\n";
		}
	}

	for (int32_t i = 0; i != size; ++i) 
	{
		std::cout << "KKK: " << arr[i] << std::endl;
	}
	std::cout << result << std::endl;

	fout_ << result << std::flush;
	fout_.close();

	return ret;
}

int32_t RecordOffset::getOffset(uint64_t arr[], int32_t size)
{
	int32_t ret = 0;

	ro_split(data_, '|', elems_);

	uint64_t elem = 0;
	int32_t i = 0;
	for (StrVec::iterator iter = elems_.begin(); iter != elems_.end(); ++iter)
	{
		elem = strtoll((*iter).c_str(), NULL, 10);
		//std::cout << "elem: " << elem << std::endl;
		if (i != size)
		{
			arr[i++] = elem;
		}
	}

	return ret;
}

void RecordOffset::ro_split(const std::string &in_str, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(in_str);
	std::string item;
	
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}

	return;
}

