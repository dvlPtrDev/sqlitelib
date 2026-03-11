#ifndef SQLITE_UTILS_H
#define SQLITE_UTILS_H

/**
 * @file sqlite_utility.h
 * @brief helpers for working with SQLite3 in C.
 *
 * This header provides functions for:
 * - Opening and closing SQLite connections
 * - Executing SQL statements
 * - Working with prepared statements
 * - Binding parameters
 * - Loading and executing schema files
 */

#include <stdbool.h>
#include <sqlite3.h>

/**
 * @def DEFAULT_FLAGS
 * @brief Default flags used to open an SQLite database.
 *
 * Opens the database for reading and writing, creating it if it does not exist.
 */
#define DEFAULT_FLAGS SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE

/**
 * @def TEMP_FLAGS
 * @brief Flags used to create a temporary SQLite database.
 *
 * The database will be automatically deleted when the connection is closed.
 */
#define TEMP_FLAGS SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_DELETEONCLOSE

/**
 * @def READONLY_FLAGS
 * @brief Flags used to open an SQLite database in read-only mode.
 */
#define READONLY_FLAGS SQLITE_OPEN_READONLY


/* =========================================================
   Schema
   ========================================================= */

/**
 * @brief Reads an SQL schema file into memory.
 *
 * The function loads the contents of the file into a dynamically
 * allocated string buffer.
 *
 * @param path Path to the schema file.
 * @return Pointer to the schema string, or NULL if the file cannot be read.
 */
const char *read_schema_file(const char *path);

/**
 * @brief Executes a schema SQL file on the given database.
 *
 * I recommend use to initialize tables or structure.
 *
 * @param schema_path Path to the SQL schema file.
 * @param db Open SQLite database connection.
 * @return SQLITE_OK on success or an SQLite error code.
 */
int exec_schema(const char *schema_path, sqlite3 *db);


/* =========================================================
   Connection
   ========================================================= */

/**
 * @brief Opens a connection to an SQLite database.
 *
 * Internally uses sqlite3_open_v2().
 *
 * @param db Path to the database file.
 * @param flags SQLite open flags (e.g., DEFAULT_FLAGS).
 * @return Pointer to an SQLite connection or NULL if opening fails.
 */
sqlite3 *get_conn(const char *db, unsigned int flags);

/**
 * @brief Closes an SQLite database connection.
 *
 * Internally calls sqlite3_close_v2().
 *
 * @param db SQLite database connection.
 * @return SQLite result code.
 */
int close_conn(sqlite3 *db);


/* =========================================================
   Bind
   ========================================================= */

/**
 * @brief Binds a text value to a prepared statement parameter.
 *
 * @param prepared Prepared SQLite statement.
 * @param param_n Parameter index (starting at 1).
 * @param value Text value to bind.
 * @return true if binding succeeded, false otherwise.
 */
bool bind_text(sqlite3_stmt *prepared, int param_n, const char* value);

/**
 * @brief Binds a double value to a prepared statement parameter.
 *
 * @param prepared Prepared SQLite statement.
 * @param param_n Parameter index (starting at 1).
 * @param number Double value to bind.
 * @return true if binding succeeded, false otherwise.
 */
bool bind_double(sqlite3_stmt *prepared, int param_n, double number);


/* =========================================================
   Statement
   ========================================================= */

/**
 * @brief Prepares an SQL statement.
 *
 * Wrapper around sqlite3_prepare_v2().
 *
 * @param db SQLite database connection.
 * @param statement SQL query to prepare.
 * @return pointer to Prepared SQLite statementor NULL on failure.
 */
sqlite3_stmt *stmt_prepare(sqlite3 *db, const char *statement);

/**
 * @brief Executes a prepared statement step.
 *
 * Calls sqlite3_step() and optionally finalizes the statement.
 *
 * @param query Prepared statement.
 * @param finalize If true, the statement will be finalized after execution.
 * @return true if execution finished successfully (SQLITE_DONE).
 */
bool step(sqlite3_stmt *query, bool finalize);

/**
 * @brief Executes a static SQL statement.
 *
 * Wrapper around sqlite3_exec() for queries that do not require
 * prepared statements.
 *
 * @param db SQLite database connection.
 * @param query SQL query string.
 * @param errmsg Pointer that receives an SQLite error message (can be null).
 * @return SQLITE_OK on success or an SQLite error code.
 */
int static_statement(sqlite3 *db, const char *query, char **errmsg);

#endif