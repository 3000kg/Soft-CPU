#ifndef ERRORNUMS_H_INCLUDED
#define ERRORNUMS_H_INCLUDED

enum errs
{
    //Common
        UNKNOWN_ERROR          = 0x0001,
        DEAD_POINTER           = 0x0002,
        NOT_ENOUGH_SPACE       = 0x0003,

        NAN_POISON             = 0x0004,
        NOT_A_NUMBER,
        LEFT_WALL_BROKEN,
        RIGHT_WALL_BROKEN,

        SIZE_OVER_CAPACITY     = 0x0009,

        TYPE_MISSMATCH,

        UNEXPECTED_CONDITIONS,



    //Print Data
        UNPRINTEABLE_DATA_TYPE = 0x200A,



    //Stack structure
        STACK_MEM_FAIL         = 0x1003,
        CAP_IS_NAN             = 0x1006,
        SIZE_IS_NAN            = 0x1007,
        EXPTO_IS_NAN           = 0x1008,
        ADD_MEM_FAIL           = 0x100C,
        CAP_OVER_EXPTO         = 0x100D,
        STACK_UNDERFLOW        = 0x100E,
        BAD_DEFAULT_LEN        = 0x1010,
        BAD_VALUE_TYPE         = 0x1011,
        WRONG_REMOVEMEM_CALL   = 0x1012,
        REMOVE_MEM_FAIL        = 0x1013,
        CANT_PRINT_STACK       = 0x1014,
        BAD_MULTIPLIER,

    //Text structure
        CANT_OPEN_FILE,
        FILE_IS_CLOSED,
        TEXT_CLOSED_INCORRECTLY,

    //CPU
        INCORRECT_ASM_LINE,
        WRONG_MARK,
        CMD_ASSERTION_FAIL,

    //List Structure
        NULLPTR_LIST_DATA,
        NO_FREE_SPACE,
        INCORRECT_FREE_SPACE,
        PLACE_IS_OUT_OF_RANGE,
        LIST_IS_EMPTY,
        INCORRECT_REMOVE_ELEMENT
};

#endif // ERRORNUMS_H_INCLUDED
