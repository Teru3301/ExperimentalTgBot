
#include "config.hpp"
#include "logger.hpp"

Args parse_args(int argc, char* argv[])
{
    Args args;
    Logger lg(logging::CONSOLE);

    lg.debug(std::to_string(argc));

    if ((argc - 1) % 2 != 0)
    {
        lg.warn("Incorrect number of arguments");
        exit(1);
    }

    for (int i = 0; i < argc; i++)
    {
        lg.log(argv[i]);
    }

    return args;
}

