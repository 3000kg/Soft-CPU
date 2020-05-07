#ifndef ENUMCOMMANDS_INCLUDED
#define ENUMCOMMANDS_INCLUDED

#define DEF_CMD( name, code, function ) #name##_code = (code), 

      enum CPU_COMMANDS
      {
          #include "CPU_COMMANDS.h"
          enummax
      };

#undef DEF_CMD

#endif //ENUMCOMMANDS_INCLUDED
