#include <cstdint>
#include <etl/optional.h>
#include <etl/expected.h>

using std::size_t;

namespace pqgs
{

#define NUM_ELEMS(a) (sizeof(a)/sizeof 0[a])

enum Error
{
    None = 0,
    Timeout,
    Initialization,
    NotFound,
    BadParameter,
};

using expected_void = etl::expected<void, Error>;

} // namespace pqgs