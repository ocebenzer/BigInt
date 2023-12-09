#include <string>

namespace ocb {

enum class negativity : uint8_t {
    pp = 0,
    pn = 1,
    np = 2,
    nn = 3
};
negativity calculate_negativity (bool n1, bool n2);

void trim_zeros (std::string&);

std::string add (const std::string&, const std::string&);
std::string sub (const std::string&, const std::string&);

bool is_less_than (const std::string&, const std::string&);

} // namespace ocb
