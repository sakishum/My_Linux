#pragma once

#include <stdint.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

namespace RECORD 
{

class File_not_found 
{
public:
	std::string filename;
	File_not_found(const std::string &filename_ = std::string()) : filename(filename_) { }
};

class Key_not_found 
{
public:
	std::string key;
	Key_not_found(const std::string &key_ = std::string()) : key(key_) { }
};

class RecordOffset 
{
	typedef std::vector<std::string> StrVec;
public:
	RecordOffset(void);
	~RecordOffset(void);
	int32_t init(const std::string &path);

	int32_t setOffset(const uint64_t arr[], int32_t size);
	int32_t getOffset(uint64_t arr[], int32_t size);

private:
	RecordOffset(const RecordOffset&);
	RecordOffset& operator=(const RecordOffset&);
	void ro_split(const std::string &in_str, char delim, StrVec &elems);

private:
	std::string path_;
	std::string data_;
	std::ofstream fout_;
	StrVec elems_;
};

}  // namespace recodeoffset
