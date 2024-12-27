#pragma once
#include <iostream>
#include <chrono>


class Timer {
public:
	Timer (){
		m_startPoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		stop();
	}

	void stop() {
		auto m_endPoint = std::chrono::high_resolution_clock::now();
		auto startTime = std::chrono::time_point_cast <std::chrono::microseconds>(m_startPoint).time_since_epoch().count();
		auto endTime = std::chrono::time_point_cast <std::chrono::microseconds>(m_endPoint).time_since_epoch().count();

		std::cout << "Time Taken : " << (endTime - startTime) << " us"
			 << "\n";
	}


private:
	std::chrono::time_point <std::chrono::high_resolution_clock> m_startPoint;
};