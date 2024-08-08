#include "neo/uuid.hpp"

namespace neo {

generator_64_type generator = generator_64_type(0);

uuid_distribution_type uuid_distribution = uuid_distribution_type(generator_64_type::min(), generator_64_type::max());

uuid_type
uuid()
{
    return uuid_distribution(generator);
}

}   // namespace neo
