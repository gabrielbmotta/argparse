#include "argparse.h"

#include <stdio.h>

int main(int argc, char*argv[])
{
    arg_parser_t ap = create_arg_parser("Parse Test", "v0.0.1");

    int item = 0;
    arg item_arg = {.t = int_arg, .value = &item,
                   .argument = "--item", .short_argument = "-i",
                   .description = "This value does things."};

    add_argument(ap, &item_arg);
    switch (parse_args(ap, argc, argv)){
        case success:
            printf("Item value is %d\n",item);
        case help:
            break;
        case error:
            print_errors(ap);
            break;
    }

    delete_parser(ap);
}