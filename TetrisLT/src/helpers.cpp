#include "../h/helpers.hpp"

namespace Helpers {
	std::string MStoMM_SSformat(int ms) {
		using namespace std::chrono;
		auto d = (milliseconds)ms;
		auto m = duration_cast<minutes>(d);
		d -= m;
		auto s = duration_cast<seconds>(d);

		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << m.count() << ":" << std::setw(2) << std::setfill('0') << s.count();

		return ss.str();
	}
}