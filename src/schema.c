#include <sqlite_utility.h>
#include <stdlib.h>
#include <stdio.h>

const char *read_schema_file(const char *path) 
{
    char *buffer = malloc(513);
    FILE *fp = fopen(path, "r");
    if (!fp) return NULL;
    
    int i = 0, c = 0;
    while ((c = fgetc(fp)) != EOF && i < 512) {
        buffer[i] = (char)c;
        i++;
    };
    buffer[i] = '\0';
    fclose(fp);
    return (const char *)buffer;
}

int exec_schema(const char *schema_path, sqlite3 *db) 
{
    const char *schema = read_schema_file(schema_path);
    char *pperr = NULL;
    if (static_statement(db, schema, &pperr) != 0) {
        return sqlite3_errcode(db);
    }
    if (schema) free((void*) schema);
    if (pperr)  sqlite3_free(pperr);
    return SQLITE_OK;
}