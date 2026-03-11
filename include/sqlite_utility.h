#ifndef SQLITE_UTILS_H
#define SQLITE_UTILS_H
#define DEFAULT_FLAGS SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE
#define TEMP_FLAGS SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_DELETEONCLOSE
#define READONLY_FLAGS  SQLITE_OPEN_READONLY

#include <stdbool.h>
#include <sqlite3.h>

/** Schema  */

const char *read_schema_file(const char *path); 
int exec_schema(const char *schema_path, sqlite3 *db);

/** Connection */
sqlite3 *get_conn(const char *db, unsigned int flags);
int close_conn(sqlite3 *db);

/** Bind */
bool bind_text(sqlite3_stmt *prepared, int param_n, const char* value);
bool bind_double(sqlite3_stmt *prepared, int param_n, double number);

/** Statement */
sqlite3_stmt *stmt_prepare(sqlite3 *db, const char *statement);
bool step(sqlite3_stmt *query, bool kill_step);
int static_statement(sqlite3 *db, const char *query, char **errmsg);


#endif 