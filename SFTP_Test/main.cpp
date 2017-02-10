#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sstream>		// std::stringstream
#include <iostream>
#include <string>
#include <vector>
#include <inttypes.h>	// PRId64

#include "record_offset.h"

using namespace RECORD;

enum marquee_time_interval
{
	MARQUEE_REDIS_TIME_INTERVAL = 60 * 30,		// 间隔时间
};

void nb_split(const std::string &in_str, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(in_str);
	std::string item;
	
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return;
}

uint32_t get_date(time_t now)
{
    uint32_t the_day = 0;
    struct tm tm_the_day;
    char stoday[256] = { 0 };
    localtime_r(&now, &tm_the_day);
    strftime(stoday, sizeof stoday, "%Y%m%d", &tm_the_day);
    the_day = strtol(stoday, NULL, 10);
    return the_day;
}

int32_t replaceStrByNum(std::string &str, const std::string &search, const std::string &target) {
	int32_t ret = 0;
	size_t pos = 0;
	while ((pos = str.find(search, pos)) != std::string::npos) 
	{
		str.replace(pos, search.length(), target);
		pos += target.length(); 
		ret = 1; 
	}
	return ret;
}

static const std::string TGP_TARGET_TYPE_INFO[] = {
        "",
        "有【X】场对局中获得过五杀",
        "有【X】场对局中获得过四杀及以上",
        "有 X 场对局中获得过三杀及以上",
        "完成累计击杀英雄 X 次",
        "完成累计击杀小兵 X 次",
        "完成累计击杀中立生物 X 次",
        "完成累计摧毁防御塔 X 次",
        "胜利 X 场",
        "失败 X 场",
        "完成累计助攻数 X 次",
        "完成累计死亡数 X 次",
        "完成同吧五黑 X 场",
        "完成MVP X 场",
        "完成超神 X 场",
        "完成连胜 X 场",
        "完成单局击杀英雄 X 次",
        "完成单局击杀小兵 X 次",
        "完成单局摧毁防御塔 X 次",
        "完成单局助攻数 X 次 ",
        "完成单局死亡数 X 次",
        "完成同吧十黑 X 场",
        "完成同吧十黑胜 X 场",
        "完成同吧十黑负 X 场",
        "完成连败 X 场",
        "完成首胜"
    };

int32_t main(int32_t, char**) 
{
	std::string str("Enter");
	std::cout << str.c_str() << std::endl;
	std::vector<std::string> elems;
	std::string exist_value("1|1456847999");
    nb_split(exist_value, '|', elems);

    uint32_t exist = strtoul(elems[0].c_str(), NULL, 10);
    uint32_t redis_time = 0;
    std::cout << "exist: " << exist << std::endl;
    if (elems.size() > 1)
	{
		redis_time = strtoul(elems[1].c_str(), NULL, 10);
	}
	std::cout << "time: " << (time(0) - redis_time) << std::endl;
	std::cout << "outtime: " << MARQUEE_REDIS_TIME_INTERVAL << std::endl;
	std::cout << "time now: " << time(0) <<std::endl;
	// exist & outtime
	if (exist && ((time(NULL) - redis_time) > MARQUEE_REDIS_TIME_INTERVAL))
	{
		std::cout << "redis_time: " << redis_time << ", outtime: " << MARQUEE_REDIS_TIME_INTERVAL << std::endl;
		std::cout << "Refrash." << std::endl;
	}

	// uint64 打印，需要设置 -D__STDC_FORMAT_MACROS
	uint64_t uint64 = 1212;
	printf("%"PRId64"\n", uint64); 

	// 时间转换 time_t => 20160203
 	time_t now = time(NULL);
	std::cout << "Today is: " << get_date(now) << std::endl;

	//std::string str1 = strinfo[2];
	//std::cout << "strinfo[2] = " << str1 << std::endl;
	//char desc[200] = {0};
	//sprintf(desc, str1.c_str(), 3);
	//printf("%s\n", desc);

	std::string str2 = TGP_TARGET_TYPE_INFO[1];
	std::stringstream ss;
	ss << 42;
	replaceStrByNum(str2, "X", ss.str());
	std::cout << "TGP_TARGET_TYPE_INFO[1] = " << str2 << std::endl;

	uint64_t arr[4] = {0};
	//{
		RecordOffset ro;
		ro.init("/Users/sakishum1118/MyLinux/SFTP_Test/record.txt");
		
		
	

		ro.getOffset(arr, sizeof(arr)/sizeof(arr[0]));
		for (int32_t i = 0; i != 4; ++i)
		{
			std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
 		}

 		
 		ro.setOffset(arr, sizeof(arr)/sizeof(arr[0]));

 		
	//}
 	int64_t incr = 1;
	while (true) 
 	{
 		for (int32_t i = 0; i != 4; ++i) 
		{
			arr[i] = (i + incr++)*100;
		}
		ro.setOffset(arr, sizeof(arr)/sizeof(arr[0]));
 		sleep(1);
 	}
	exit(EXIT_SUCCESS);
}
