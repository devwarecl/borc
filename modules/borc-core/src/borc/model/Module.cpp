
#include "Module.hpp"

namespace borc {
    Module::Module(Package *package) {
        this->package = package;
    }

    Module::~Module() {}

    void Module::setName(const std::string &name) {
        this->name = name;
    }

    void Module::setType(const Module::Type type) {
        this->type = type;
    }

    void Module::setVersion(const Version &version) {
        this->version = version;
    }

    void Module::setLanguage(const Language &lang) {
        language = lang;
    }

    void Module::setDependencies(const std::vector<const Module*> &dependentModules) {
        dependencies = dependentModules; 
    }
}
