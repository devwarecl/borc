
#ifndef __BORC_SERVICES_TOOLCHAINSERVICEIMPL_HPP__
#define __BORC_SERVICES_TOOLCHAINSERVICEIMPL_HPP__

#include "ToolchainService.hpp"

namespace borc {
    class FileService;

    class ToolchainServiceImpl : public ToolchainService {
    public:
        explicit ToolchainServiceImpl(FileService *fileService);

        std::unique_ptr<Toolchain> createToolchain(const boost::filesystem::path &toolchainFolder) const override;

    private:
        FileService *fileService = nullptr;
    }; 
}

#endif
