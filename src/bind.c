#include <sqlite_utility.h>

bool bind_text(sqlite3_stmt *prepared, int param_n, const char* value) 
{
    return sqlite3_bind_text(prepared, param_n, value, -1, SQLITE_STATIC) == SQLITE_OK;
}

bool bind_double(sqlite3_stmt *prepared, int param_n, double number) 
{
    return sqlite3_bind_double(prepared, param_n, number) == SQLITE_OK;    
}