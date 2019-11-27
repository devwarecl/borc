
#ifndef __BORC_MODEL_MODULE_HPP__
#define __BORC_MODEL_MODULE_HPP__

#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>

#include <borc/model/Version.hpp>
#include <borc/model/Language.hpp>

namespace borc {
    class Package;
    class Module {
    public:
        struct Type {
            std::string tag;
            std::string subTag;

            bool operator== (const Type &other) const {
                return tag==other.tag && subTag==other.subTag;
            }

            bool operator!= (const Type &other) const {
                return ! (*this == other);
            }

            bool operator< (const Type &other) const {
                if (tag < other.tag) {
                    return true;
                }

                return subTag < other.subTag;
            }
        };

    public:
        explicit Module(Package *package);

        virtual ~Module() = 0;

        std::string getName() const {
            return name;
        }

        Type getType() const {
            return type;
        }

        Language getLanguage() const {
            return language;
        }

        const Package* getPackage() const {
            return package;
        }

        Version getVersion() const {
            return version;
        }

        void setName(const std::string &name);

        void setLanguage(const Language &lang);

        void setType(const Type type);

        void setVersion(const Version &version);

        std::vector<const Module*> getDependencies() const {
            return dependencies;
        }

        void setDependencies(const std::vector<const Module*> &dependentModules);

    protected:
        Package *package = nullptr;
        std::string name;
        Type type;
        Version version;
        Language language;
        std::vector<const Module*> dependencies;
    };
}

#endif
