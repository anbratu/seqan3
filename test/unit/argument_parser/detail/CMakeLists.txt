add_definitions(-DSEQAN_INCLUDE_DIR="${SEQAN3_INCLUDE_DIR}")
seqan3_test(format_help_test.cpp)
seqan3_test(format_html_test.cpp)
seqan3_test(format_man_test.cpp)
seqan3_test(version_check_debug_test.cpp)
seqan3_test(version_check_release_test.cpp)
