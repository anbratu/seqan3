#include <seqan3/core/pod_tuple.hpp>
#include <seqan3/core/debug_stream.hpp>

int main()
{
    seqan3::pod_tuple<int, float> t{3, 4.7};
    static_assert(std::is_pod_v<seqan3::pod_tuple<int, float>>);

    // template parameters are automatically deduced:
    seqan3::pod_tuple t2{17, 3.7f, 19l};

    seqan3::debug_stream << std::get<0>(t2) << '\n'; // 17

    auto [ i, f, l ] = t2; // creates an int i with value 17, float f...
}
