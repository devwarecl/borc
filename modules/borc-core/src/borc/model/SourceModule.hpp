
#ifndef __BORC_MODEL_SOURCEMODULE_HPP__
#define __BORC_MODEL_SOURCEMODULE_HPP__

#include "Module.hpp"

namespace borc {
    class Package;
    class Source;
    class SourceModule : public Module {
    public:
        explicit SourceModule(Package *package);

        ~SourceModule();

        boost::filesystem::path getPath() const {
            return path;
        }

        std::vector<boost::filesystem::path> getSourcePaths() const {
            return sourcePaths;
        }

        std::vector<boost::filesystem::path> getIncludePaths() const {
            return includePaths;
        }

        void setPath(const boost::filesystem::path &path);

        void setSourcePaths(const std::vector<boost::filesystem::path> &sourcePaths);

        void setIncludePaths(const std::vector<boost::filesystem::path> &includePaths);

        /**
         * @brief Reconstruct all the internal object Source files based on the supplied base folder
         */
        void rescanSources(const boost::filesystem::path &baseFolder);

        std::vector<Source*> getSources() const;


    private:
        boost::filesystem::path path;
        std::vector<boost::filesystem::path> sourcePaths;
        std::vector<boost::filesystem::path> includePaths;
        std::vector<std::unique_ptr<Source>> sources;
    };
}

#endif
