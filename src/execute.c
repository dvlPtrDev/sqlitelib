#include <stdio.h>
#include <sqlite_utility.h>

int static_statement(sqlite3 *db, const char *query, char **errmsg) 
{
    int result = sqlite3_exec(db, query, NULL, NULL, errmsg);
    if (result != SQLITE_OK) {
        return sqlite3_errcode(db);
    }
    
    return SQLITE_OK;
}