#include <sqlite_utility.h>
#include <stddef.h>

sqlite3_stmt *stmt_prepare(sqlite3 *db, const char *statement) 
{
    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(
        db,
        statement,  
        -1,
        &stmt,
        NULL
    );
    return stmt;
}

bool step(sqlite3_stmt *query, bool kill_step) 
{
    if (sqlite3_step(query) != SQLITE_DONE) {
        return false;
    };
    if (kill_step) {
        sqlite3_finalize(query);
    }
    return true;
}