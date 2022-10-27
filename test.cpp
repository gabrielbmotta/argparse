#include "argparse.h"

#include <iostream>

int main(int argc, char*argv[])
{
    ArgParser arg_parser("Parse Test", "v0.0.1");

    int item = 0;
    arg_parser.addArgument({arg_type::int_arg, &item, "--item", "-i",
                            "This value does things."});

    switch (arg_parser.parseArguments(argc, argv)){
        case success:
            std::cout << "Item value is " << item << "\n";
        case help:
            break;
        case error:
            arg_parser.printErrors();
            break;
    }
}