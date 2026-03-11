#include <sqlite_utility.h>
#include <stddef.h>


sqlite3 *get_conn(const char *db, unsigned int flags)
{
    sqlite3 *database;
    int can_open_conn = sqlite3_open_v2(   
        db, 
        &database, 
        flags,  
        NULL
    );
    if (can_open_conn != SQLITE_OK) {
        return NULL;
    };
    return database;
}

int close_conn(sqlite3 *db){ sqlite3_close_v2(db);};