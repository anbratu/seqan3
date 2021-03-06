#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <seqan3/alphabet/nucleotide/rna5.hpp>
#include <seqan3/alphabet/structure/structured_rna.hpp>
#include <seqan3/alphabet/structure/wuss.hpp>
#include <seqan3/io/structure_file/output.hpp>

int main()
{
    using seqan3::operator""_rna5;
    using seqan3::operator""_wuss51;

    seqan3::structured_rna<seqan3::rna5, seqan3::wuss51> sr{'G'_rna5, '.'_wuss51};

    seqan3::structure_file_output fout{std::ostringstream{},
                                       seqan3::format_vienna{},
                                       seqan3::fields<seqan3::field::ID, seqan3::field::STRUCTURED_SEQ>{}};

    for (int i = 0; i < 10; i++) // ...
    {
        std::string id{"test_id"};
        // vector of combined data structure
        std::vector<seqan3::structured_rna<seqan3::rna5, seqan3::wuss51>> structured_seq{sr, sr, sr, sr};

        // ...

        fout.emplace_back(id, structured_seq); // note also that the order the arguments is now different, because
        // or:                                    you specified that ID should be first in the fields template argument
        fout.push_back(std::tie(id, structured_seq));
    }
}
