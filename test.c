#include "argparse.h"
#include "argtypes.h"

#include <stdio.h>

int main(int argc, char*argv[])
{
    arg_parser_t ap = create_arg_parser();

    int item = 0;
    arg item_arg = {.t = int_arg, .value = &item,
                   .argument = "--item", .short_argument = "-i",
                   .description = "This value does things."};

    add_argument(ap, &item_arg);
    parse_args(ap, argc, argv);

    printf("Input value was %d\n", item);
}