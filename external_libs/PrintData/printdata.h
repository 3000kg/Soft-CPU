#ifndef PRINTDATA_H_INCLUDED
#define PRINTDATA_H_INCLUDED

    //for log
        #include "../LOGS/chronology.h"
        #include <typeinfo>

        extern dump_t dump;
        extern log_t logs;

        #define LOG_PRINTDATA (logs.logBox + printDataLogNum)

    //for int print_data_t(data)
        //#define data_type typeid(data)
        #define size_type typeid(size_t)
        #define c_type typeid(signed char)
        #define uc_type typeid(unsigned char)
        #define hi_type typeid(short)
        #define hu_type typeid(unsigned short)
        #define i_type typeid(int)
        #define u_type typeid(unsigned)
        #define li_type typeid(long)
        #define lu_type typeid(unsigned long)
        #define lli_type typeid(long long)
        #define llu_type typeid(unsigned long long)
        #define f_type typeid(float)
        #define lf_type typeid(double)
        #define llf_type typeid(long double)


//Definition
        #define print_data_t(data, charPtr) \
        {                                                                               \
            _dumpMacro(LOG_PRINTDATA, print_data_t);                                    \
            assert(charPtr);                                                            \
                                                                                        \
            if ((c_type == typeid(data)) or (uc_type == typeid(data)))                  \
                sprintf(charPtr, "%c", (data));                                         \
                                                                                        \
            else if (hi_type == typeid(data))                                           \
                sprintf(charPtr, "%hi", (data));                                        \
                                                                                        \
            else if (hu_type == typeid(data))                                           \
                sprintf(charPtr, "%hu", (data));                                        \
                                                                                        \
            else if (i_type == typeid(data))                                            \
                sprintf(charPtr, "%i", (data));                                         \
                                                                                        \
            else if (u_type == typeid(data))                                            \
                sprintf(charPtr, "%u", (data));                                         \
                                                                                        \
            else if (li_type == typeid(data))                                           \
                sprintf(charPtr, "%li", (data));                                        \
                                                                                        \
            else if (lu_type == typeid(data))                                           \
                sprintf(charPtr, "%lu", (data));                                        \
                                                                                        \
            else if (lli_type == typeid(data))                                          \
                sprintf(charPtr, "%lli", (data));                                       \
                                                                                        \
            else if (llu_type == typeid(data))                                          \
                sprintf(charPtr, "%llu", (data));                                       \
                                                                                        \
            else if (f_type == typeid(data))                                            \
                sprintf(charPtr, "%f", (data));                                         \
                                                                                        \
            else if (lf_type == typeid(data))                                           \
                sprintf(charPtr, "%f", (data));                                         \
                                                                                        \
            else if (llf_type == typeid(data))                                          \
                sprintf(charPtr, "%llf", (data));                                       \
                                                                                        \
            else                                                                        \
                sprintf(charPtr, "%p", (data));                                         \
                                                                                        \
            assert(LOG_PRINTDATA);                                                      \
            sprintf(_comment, "Printing element(%s)...", #data);                      \
            _writeComment(LOG_PRINTDATA, _comment);         		                          \
                                                                                        \
          _endOfFunction(LOG_PRINTDATA);\
        }


        //Outputs variable with unknown type

#endif // PRINTDATA_H_INCLUDED
