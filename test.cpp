#include "argparse.h"
#include "argtypes.h"

#include <iostream>

int main(int argc, char*argv[])
{
    ArgParser arg_parser("Parse Test", "v0.0.1");

    int item = 0;
    arg_parser.addArgument({arg_type::int_arg, &item, "--item", "-i",
                            "This value does things."});

    if (arg_parser.parseArguments(argc, argv)){
        if(!arg_parser.helpMode()){
            std::cout << "Input value was " << item << "\n";
        }
    } else {
        arg_parser.printErrors();
    }
}