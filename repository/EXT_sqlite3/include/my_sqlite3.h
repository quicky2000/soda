/*
  This file is part of EXT_sqlite3, part of quicky build tool that
  allow to use sqlite3 library
  Copyright (C) 2012  Julien Thevenon ( julien_thevenon at yahoo.fr )

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef _MY_SQLITE3_H_
#define _MY_SQLITE3_H_

#include "sqlite3.h"
#if SQLITE_VERSION_NUMBER < 3007014
inline int sqlite3_close_v2(sqlite3* p_db)
{
  return sqlite3_close(p_db);
}
#endif
#if SQLITE_VERSION_NUMBER <= 3003006
inline int sqlite3_clear_bindings(sqlite3_stmt*)
{
  return SQLITE_OK;
}
#endif // Check version 

#if SQLITE_VERSION_NUMBER <= 3005000
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */

inline int sqlite3_open_v2(
                           const char *filename,   /* Database filename (UTF-8) */
                           sqlite3 **ppDb,         /* OUT: SQLite db handle */
                           int flags,              /* Flags */
                           const char *zVfs        /* Name of VFS module to use */
                           )
{
  return sqlite3_open(filename,ppDb);
}
#endif // Check version 3005000

#if SQLITE_VERSION_NUMBER <= 3003009
inline int sqlite3_prepare_v2(
                              sqlite3 *db,            /* Database handle */
                              const char *zSql,       /* SQL statement, UTF-8 encoded */
                              int nByte,              /* Maximum length of zSql in bytes. */
                              sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
                              const char **pzTail     /* OUT: Pointer to unused portion of zSql */
                              )
{
  return sqlite3_prepare(
                  db,            /* Database handle */
                  zSql,       /* SQL statement, UTF-8 encoded */
                  nByte,              /* Maximum length of zSql in bytes. */
                  ppStmt,  /* OUT: Statement handle */
                  pzTail     /* OUT: Pointer to unused portion of zSql */
                  );
}
#endif // Check version 3003009

#endif // _MY_SQLITE3_H_
// EOF
