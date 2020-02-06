
#include <borc/toolchain/CompileOptions.hpp>

namespace borc {
    void CompileOptions::mergeWith(const CompileOptions &other) {
        includePaths.insert(includePaths.end(), other.includePaths.begin(), other.includePaths.end());
    }
}