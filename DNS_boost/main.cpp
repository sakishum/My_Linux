/**
 * @file main.cpp
 * @Synopsis  采用boost::asio::ip::tcp::socket来建立和不同PC间的连接，
 * 同时下载’Highscore'首页--就像浏览器访问www.highscore.de时做的一样。
 * @author Saki Shum, sakishum1118@gmail.com
 * @version 0.0.1
 * @date 2015-10-26
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>

boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::socket sock(io_service);
boost::array<char, 4096> buffer;

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transfered) {
	if (!ec) {
		std::cout << std::string(buffer.data(), bytes_transfered) << std::endl;
		sock.async_read_some(boost::asio::buffer(buffer), read_handler);
	}
}

void connect_handler(const boost::system::error_code &ec) {
	if (!ec) {
		//boost::asio::write(sock, boost::asio::buffer("Get / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
		boost::asio::write(sock, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
		sock.async_read_some(boost::asio::buffer(buffer), read_handler);
	}
}

void resolver_handler(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it) {
	if (!ec) {
		// 异步域名解析
		sock.async_connect(*it, connect_handler);
	}
}

int32_t main(int32_t, char**) {
	// http的意思使用80端口
	boost::asio::ip::tcp::resolver::query query("www.highscore.de", "http");
	resolver.async_resolve(query, resolver_handler);
	io_service.run();
	exit(EXIT_SUCCESS);
}
