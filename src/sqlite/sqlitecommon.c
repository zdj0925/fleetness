#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "sqlite3.h"
#include "sql.h"

#define SQLITE_DB_NUM   16

#define SQLITE_SYS      0
#define SQLITE_DUMP     1

static sqlite3 *g_conn[SQLITE_DB_NUM];

int sys_db_open ()
{
    int rv = 0;
    char *ptr = NULL;
    char dbname[256] = { 0 };
    struct stat st;

    if (g_conn[SQLITE_SYS] != NULL)
    {
        // printf("sqlite-db already open");
        return 0;
    }

    if ((ptr = getenv (SYSDB_ENV)) == NULL)
    {
        snprintf (dbname, sizeof (dbname), "%s/db/%s", getenv ("HOME"), SYSDB_NAME);
    }
    else
    {
        snprintf (dbname, sizeof (dbname), ptr);
    }
    printf ("dbname is [%s]", dbname);

    memset (&st, 0, sizeof (st));
    rv = stat (dbname, &st);
    if (rv)
    {
        printf ("error: stat [%s]:[%d],[%s]", dbname, errno, strerror (errno));
        return -1;
    }
    if (st.st_size == 0)
    {
        printf ("error: sys-db [%s] is empty", dbname);
        return -1;
    }

    /*
     * Open database 
     */
    rv = sqlite3_open (dbname, &g_conn[SQLITE_SYS]);
    if (rv)
    {
        printf ("error: can't open database: %s", sqlite3_errmsg (g_conn[SQLITE_SYS]));
        return -1;
    }

    return 0;
}

int sys_db_close ()
{
    if (g_conn[SQLITE_SYS])
    {
        sqlite3_close (g_conn[SQLITE_SYS]);
        g_conn[SQLITE_SYS] = NULL;
    }

    return 0;
}

int sys_db_exec (const char *sql, int (*callback) (void *, int, char **, char **), void *data, char **errmsg)
{
    return sqlite3_exec (g_conn[SQLITE_SYS], sql, callback, data, errmsg);
}

const char *sys_db_errmsg ()
{
    return sqlite3_errmsg (g_conn[SQLITE_SYS]);
}
  /*
   * SQL statement, UTF-8 encoded * Maximum length of zSql in bytes. * OUT: Statement handle *
   * OUT: Pointer to unused portion of zSql 
   */
int sys_db_prepare (const char *zSql, int nByte, sqlite3_stmt ** ppStmt, const char **pzTail)
{
    return sqlite3_prepare (g_conn[SQLITE_SYS], zSql, nByte, ppStmt, pzTail);
}

int dump_db_open ()
{
    int rv = 0;
    char *ptr = NULL;
    char dbname[256] = { 0 };
    struct stat st;

    if (g_conn[SQLITE_DUMP] != NULL)
    {
        printf ("sqlite-db already open");
        return 0;
    }

    if ((ptr = getenv (DUMPDB_ENV)) == NULL)
    {
        snprintf (dbname, sizeof (dbname), "%s/db/%s", getenv ("DCHOME"), DUMPDB_NAME);
    }
    else
    {
        snprintf (dbname, sizeof (dbname), ptr);
    }
    printf ("dbname is [%s]", dbname);

    memset (&st, 0, sizeof (st));
    rv = stat (dbname, &st);
    if (rv)
    {
        printf ("error: stat [%s]:[%d],[%s]", dbname, errno, strerror (errno));
        return -1;
    }
    if (st.st_size == 0)
    {
        printf ("error: sys-db [%s] is empty", dbname);
        return -1;
    }

    /*
     * Open database 
     */
    rv = sqlite3_open (dbname, &g_conn[SQLITE_DUMP]);
    if (rv)
    {
        printf ("error: can't open database: %s", sqlite3_errmsg (g_conn[SQLITE_DUMP]));
        return -1;
    }

    return 0;
}

int dump_db_close ()
{
    if (g_conn[SQLITE_DUMP])
        return sqlite3_close (g_conn[SQLITE_DUMP]);
    else
        return 0;
}

int dump_db_exec (const char *sql, int (*callback) (void *, int, char **, char **), void *data, char **errmsg)
{
    return sqlite3_exec (g_conn[SQLITE_DUMP], sql, callback, data, errmsg);
}

const char *dump_db_errmsg ()
{
    return sqlite3_errmsg (g_conn[SQLITE_DUMP]);
}

int dump_db_prepare (const char *zSql, int nByte, sqlite3_stmt ** ppStmt, const char **pzTail)
{
    return sqlite3_prepare (g_conn[SQLITE_DUMP], zSql, nByte, ppStmt, pzTail);
}

// sqlitecommon.c
