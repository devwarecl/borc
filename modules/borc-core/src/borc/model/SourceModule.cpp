
#include "SourceModule.hpp"

#include <boost/filesystem.hpp>
#include <borc/model/Package.hpp>
#include <borc/model/Source.hpp>


namespace borc {
    SourceModule::SourceModule(Package *package) : Module(package) {}

    SourceModule::~SourceModule() {}

    void SourceModule::setPath(const boost::filesystem::path &path) {
        this->path = path;
    }

    void SourceModule::setSourcePaths(const std::vector<boost::filesystem::path> &sourcePaths) {
        this->sourcePaths = sourcePaths;
    }

    void SourceModule::setIncludePaths(const std::vector<boost::filesystem::path> &includePaths) {
        this->includePaths = includePaths;
    }

    void SourceModule::rescanSources(const boost::filesystem::path &baseFolder) {
        sources.clear();

        for (const boost::filesystem::path &sourcePath : sourcePaths) {
            const boost::filesystem::path solvedSourcePath = baseFolder / path / sourcePath;

            if (! boost::filesystem::exists(solvedSourcePath)) {
                continue;
            }

            if (boost::filesystem::is_directory(solvedSourcePath)) {
                boost::filesystem::recursive_directory_iterator it{solvedSourcePath}, end;

                while (it != end) {
                    if (! boost::filesystem::is_directory(it->path())) {
                        const auto filePath = it->path();
                        const auto relativeFilePath = boost::filesystem::relative(filePath, baseFolder);

                        auto source = new Source{this, filePath, relativeFilePath};

                        sources.emplace_back(source);
                    }

                    ++it;
                }
            } else {
                auto source = new Source(this, solvedSourcePath, solvedSourcePath);
                sources.emplace_back(source);
            }
        }
    }

    std::vector<Source*> SourceModule::getSources() const {
        std::vector<Source*> result;

        for (auto &source : sources) {
            result.push_back(source.get());
        }

        return result;
    }
}
