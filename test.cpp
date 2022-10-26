#include "argparse.h"
#include "argtypes.h"

#include <iostream>

int main(int argc, char*argv[])
{
    ArgParser arg_parser;

    int item = 0;
    arg_parser.addArgument({arg_type::int_arg, &item, "--item", "-i",
                            "This value does things."});

    if (arg_parser.parseArguments(argc, argv)){
        std::cout << "Input value was " << item << "\n";
    } else {
        arg_parser.printErrors();
    }

}