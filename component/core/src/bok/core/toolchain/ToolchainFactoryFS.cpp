
#include "ToolchainFactoryFS.hpp"

#include <stdexcept>

#include <bok/core/Constants.hpp>
#include <bok/core/FileServiceImpl.hpp>
#include <bok/core/toolchain/ToolchainServiceImpl.hpp>

#include "ToolchainImpl.hpp"

namespace bok {
    ToolchainFactoryFS::ToolchainFactoryFS(const boost::filesystem::path &definitionPath, boost::optional<boost::filesystem::path> installationPath) {
        this->definitionPath = definitionPath;

        FileServiceImpl fileService;
        ToolchainServiceImpl toolchainService(&fileService);

        // TODO: Add auto discovery via reading the bok.json
        const std::vector<std::string> toolchainIds = this->detectAvailableToolchainIds();

        for (const std::string &toolchainId : toolchainIds) {
            const auto definitionFullPath = BOK_TOOLCHAIN_PATH_PREFIX / definitionPath / toolchainId;

            // TODO: Each toolchain should have a different installation path
            toolchainMap.insert({toolchainId, toolchainService.createToolchain(definitionFullPath, installationPath)});
        }
    }


    ToolchainFactoryFS::~ToolchainFactoryFS() {}


    Toolchain* ToolchainFactoryFS::createToolchain(const std::string &toolchainId) {
        if (auto toolchainIt = toolchainMap.find(toolchainId); toolchainIt != toolchainMap.end()) {
            return toolchainIt->second.get();
        }  

        throw std::runtime_error("Unknown toolchain: " + toolchainId);
    }


    std::vector<std::string> ToolchainFactoryFS::detectAvailableToolchainIds() const {
        return { "vc", "gcc" };
    }
}
