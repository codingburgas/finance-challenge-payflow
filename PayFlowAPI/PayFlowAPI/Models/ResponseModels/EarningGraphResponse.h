#pragma once
#include <vector>
#include <string>
class EarningsGraphResponse {
public:
	std::vector<std::string> date;
	std::vector<double> sum;

	EarningsGraphResponse(std::vector<std::string> date, std::vector<double> sum) : date(date), sum(sum) {}
	EarningsGraphResponse() {}
};