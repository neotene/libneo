#pragma once

#include <functional>
#include <random>

#include <neo/config.hpp>

namespace neo {

using generator_64_type = std::mt19937_64;
using uuid_type = generator_64_type::result_type;
using uuid_distribution_type = std::uniform_int_distribution<uuid_type>;
using uuid_gen_type = std::function<uuid_type()>;

NEO_API extern generator_64_type generator;
NEO_API extern uuid_distribution_type uuid_distribution;
NEO_API extern uuid_type uuid();

}   // namespace neo
