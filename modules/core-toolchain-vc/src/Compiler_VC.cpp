
#include <bok/core/toolchain/vc/Compiler_VC.hpp>

namespace bok {
    static std::string toString(const CompileTargetArchitecture arch) {
        switch (arch) {
        case CompileTargetArchitecture::Native: return "native";
        case CompileTargetArchitecture::x86_32: return "x86_32";
        case CompileTargetArchitecture::x86_64: return "x86_64";
        default: return "<arch-unknown>";
        }
    }

    static std::string toString(const CompileLanguage lang) {
        switch (lang) {
        case CompileLanguage::Cplusplus98: return "c++98";
        case CompileLanguage::Cplusplus03: return "c++03";
        case CompileLanguage::Cplusplus11: return "c++11";
        case CompileLanguage::Cplusplus14: return "c++14";
        case CompileLanguage::Cplusplus17: return "c++17";
        case CompileLanguage::Cplusplus20: return "c++20";
        default: return "<lang-unknown>";
        }
    }

    static std::string toString(const CompileOptimization opt) {
        switch (opt) {
        case CompileOptimization::NoOptimization: return "d";
        case CompileOptimization::FavorSize: return "1";
        case CompileOptimization::FavorSpeed: return "2";
        case CompileOptimization::FullSpeed: return "3";
        default: return "<opt-unknown>";
        }
    }

    static std::string getCompilerOption(const CompileRuntimeLink runtime) {
        switch (runtime) {
        case CompileRuntimeLink::DynamicDebug: return "/MDd";
        case CompileRuntimeLink::DynamicRelease: return "/MD";
        case CompileRuntimeLink::StaticDebug: return "/MTd";
        case CompileRuntimeLink::StaticRelease: return "/MT";
        default: return "<runtime-unknown>";
        }
    }

    Compiler_VC::Compiler_VC(std::optional<std::string> path) : path(path) {}

    CompileOutput Compiler_VC::generateCompileOutput(const CompileInput& input) const {
        CompileOutput output;
        
        if (path) {
            output.compileCommand.path = *path;
        }

        output.compileCommand.name = "cl.exe";

        output.compileCommand.args.push_back("/EHsc");
        output.compileCommand.args.push_back("/c");
        output.compileCommand.args.push_back(input.sourceFilePath);
        output.compileCommand.args.push_back("/Fo " + input.outputFilePath);

        if (input.debugInformation) {
            output.compileCommand.args.push_back("/DEBUG");
        }
        
        output.compileCommand.args.push_back("/std:" + toString(input.language));
        output.compileCommand.args.push_back("/O" + toString(input.optimization));
        // output.compileCommand.args.push_back("--target-arch=" + toString(input.targetArchitecture));
        output.compileCommand.args.push_back(getCompilerOption(input.runtimeLink));
        
        for (const auto& pair : input.definitions) {
            std::string arg = "/D \"" + pair.first + "=" + pair.second + "\"";
            output.compileCommand.args.push_back(arg);
        }

        std::transform(
            input.includePaths.begin(), input.includePaths.end(), 
            std::back_inserter(output.compileCommand.args), 
            [](const std::string &includePath) { return "/I " + includePath; });

        return output;

        // const std::string standardIncludePath = installationPath + "include";
        // const std::string ucrtIncludePath = windowsKitPath + "Include\\10.0.17763.0\\ucrt";
        // const std::string umIncludePath = windowsKitPath + "Include\\10.0.17763.0\\um";
        // 
        // const std::string sharedIncludePath = windowsKitPath + "Include\\10.0.17763.0\\shared";
        // return std::make_unique<CompilerImpl> (
        //     &commandFactory, compilerCommand, compilerSwitches,
        //     CompilerConfiguration { 
        //         {"/EHsc", "/std:c++17"}, 
        //         { 
        //             "\"" + standardIncludePath + "\"", 
        //             "\"" + ucrtIncludePath + "\"",
        //             "\"" + umIncludePath + "\"",
        //             "\"" + sharedIncludePath + "\""
        //         }
        //     }
        // );
    }
}