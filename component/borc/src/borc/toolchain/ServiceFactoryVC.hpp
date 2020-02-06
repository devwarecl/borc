
#ifndef __BORC_CORE_SERVICEFACTORYVC_HPP__
#define __BORC_CORE_SERVICEFACTORYVC_HPP__

#include "ServiceFactoryStub.hpp"

namespace borc {
    class ServiceFactoryVC : public ServiceFactoryStub {
    public:
        ServiceFactoryVC(const std::string &installationPath, const std::string &windowsKitPath);

        virtual ~ServiceFactoryVC();

    private:
        std::unique_ptr<Compiler> createCompiler(const std::string &compilerCommand, const std::string &installationPath, const std::string &windowsKitPath);

        std::unique_ptr<Linker> createLinker(const std::string &linkerCommand, const std::string &installationPath, const std::string &windowsKitPath);
    };
} 

#endif