
#ifndef __BORC_CLI_BUILDCONTROLLEROPTIONS_HPP__
#define __BORC_CLI_BUILDCONTROLLEROPTIONS_HPP__

#include <string>
#include <boost/optional.hpp>

namespace borc {
    struct BuildControllerOptions {
        bool force = false;
        bool showHelp = false;
        std::string helpMessage;

        static BuildControllerOptions parse(int argc, char **argv);
    };
}

#endif