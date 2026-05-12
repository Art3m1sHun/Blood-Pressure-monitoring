#include <stdio.h>
#include <sqlite3.h>

#include "database.h"

sqlite3* db_connect()
{
    sqlite3 *db;

    int rc =
        sqlite3_open("sensor.db", &db);

    if(rc)
    {
        printf("Cannot open database\n");

        return NULL;
    }

    char *err_msg = NULL;

    const char *sql =
        "CREATE TABLE IF NOT EXISTS sensor_data("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "sensor_type TEXT,"
        "sensor_id INTEGER,"
        "value REAL"
        ");";

    sqlite3_exec(db, sql, 0, 0, &err_msg);

    return db;
}

void db_insert(sqlite3 *db, const char *type, int sensor_id, double value)
{
    char sql[256];

    sprintf(sql,
            "INSERT INTO sensor_data"
            "(sensor_type, sensor_id, value)"
            "VALUES('%s', %d, %f);",
            type,
            sensor_id,
            value);
    char *err_msg = NULL;

    sqlite3_exec(db, sql, 0, 0, &err_msg);
}