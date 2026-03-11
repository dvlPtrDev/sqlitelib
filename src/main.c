#include <stdio.h>
#include <stdlib.h>
#include <sqlite_utility.h>

#define db_name "database.db"

int main(void) 
{
    sqlite3 *conn = get_conn(db_name, DEFAULT_FLAGS);
    int schema_result = exec_schema("schema.sql", conn);
    char *query_err = NULL;
    sqlite3_stmt *stmt = NULL; 
    sqlite3_stmt *prepared = stmt_prepare(conn, "INSERT INTO users (username, password, balance) VALUES (?, ?, ?)");
    bind_text(prepared, 1, "neymar");
    bind_text(prepared, 2, "junior");
    bind_double(prepared, 3, 50);
    step(prepared, true);
    close_conn(conn);

    return 0;
}