
#include <bok/core/toolchain/ToolchainMock.hpp>

#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <bok/core/Version.hpp>
#include <bok/core/toolchain/CompilerMock.hpp>
#include <bok/core/toolchain/LinkerMock.hpp>

namespace bok {
    ToolchainMock::ToolchainMock() {
        compilers.emplace_back(new CompilerMock{});
        linkers.emplace_back(new LinkerMock{});
    }

    ToolchainMock::~ToolchainMock() {}

    std::vector<Compiler*> ToolchainMock::enumerateCompilers() const {
        std::vector<Compiler*> result;

        result.push_back(compilers[0].get());

        return result;
    }

    std::vector<Linker*> ToolchainMock::enumerateLinkers() const {
        std::vector<Linker*> result;

        result.push_back(linkers[0].get());

        return result;
    }

    Version ToolchainMock::detectVersion() const {
        return { 1, 0, 0 };
    }

    struct ToolchainDetectorInfo {
        std::string commandTemplate;
        std::string executableFilePath;
    };

    static ToolchainDetectorInfo getToolchainDetectorInfo() {
        return {
            "gcc other/CXXCompilerVersionDetector.cpp -O0 -o${ExecutablePath}",
            "other/CXXCompilerVersionDetector"
        };
    }


    static Version detectToolchainVersion(const ToolchainDetectorInfo& info) {
        // 1. Compile C++ version detector
        // TODO: Use a internally-generated command line template
        if (std::system("gcc other/CXXCompilerVersionDetector.cpp -O0 -oother/CXXCompilerVersionDetector") != 0) {
            throw std::runtime_error("Failed CXXCompilerVersionDetector compilation.");
        }

        // 2. Execute it, and grab the output
        boost::filesystem::path compilerPath = boost::filesystem::path("./other/CXXCompilerVersionDetector");

        if (!boost::filesystem::exists(compilerPath)) {
            throw std::runtime_error("Compiler detector not found in path '" + compilerPath.string() + "'.");
        }

        boost::process::ipstream pipeStream;
        boost::process::child childProcess{ compilerPath, boost::process::std_out > pipeStream };

        std::string line;
        std::vector<std::string> specs;

        while (pipeStream && std::getline(pipeStream, line) && !line.empty()) {
            specs.push_back(line);
        }

        childProcess.wait();

        if (specs.size() != 1) {
            throw std::runtime_error("Couldn't detect compiler type and version (unexpected output)");
        }

        std::vector<std::string> compilerDetectorOutput;

        boost::algorithm::split(compilerDetectorOutput, specs[0], boost::is_any_of("-"));

        if (compilerDetectorOutput.size() != 2) {
            throw std::runtime_error("Couldn't detect compiler type and version (unexpected output)");
        }

        // 3. Parse the output and return the result.
        return Version::parse(compilerDetectorOutput[1]);
    }
}
