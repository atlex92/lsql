#ifndef DATABASE_H
#define DATABASE_H

/**
 * @file database.h
 * @brief simple C++ wrapper for QT SQL operations
 */

#include <QSqlError>
#include <QDebug>
#include "query_create_table.h"
#include "query_insert.h"
#include "query_select.h"

namespace LSql {
/**
 * @brief Database class
 * @note Provides simple interface for SQL-databases operations
 */
class Database
{
	Q_DISABLE_COPY(Database)
public:
	/**
	 * @brief Create Database object
	 * @param db data base instance to be used @see QSqlDatabase
	 */
	explicit Database(const QSqlDatabase &db = QSqlDatabase::database())
		:   m_db{db}
	{
		if (!m_db.isValid()) {
			qDebug() << "Database not valid";
		}
	}

	/**
	 * @brief Create Database object
	 * @param driver database driver name
	 */
	explicit Database(const QString &driver = "")
		:   Database{QSqlDatabase::addDatabase(driver)}
	{

	}

	/**
	 * @brief Open data base
	 *
	 * @return Result of the operation. TRUE if it was successful, otherwise FALSE
	 *
	 */
	bool open()
	{
		if (!m_db.isOpen()) {
			return m_db.open();
		}
		return true;
	}

	/**
	 * @brief Set database name
	 * @param db_name new database name
	 */
	void setName(const QString &db_name)
	{
		m_db.setDatabaseName(db_name);
	}

	/**
	 * @brief Get last database error
	 * @return Error object @see QSqlError
	 */
	QSqlError lastError() const
	{
		return m_db.lastError();
	}

	/**
	 * @brief Constructs 'CREATE TABLE' query
	 * @param tables database tables to apply query to
	 * @return 'CREATE TABLE' query @see LSqlCreateTableQuery
	 */
	QueryResult createTable(const QString &table, const QString &columns)
	{
		return QueryCreateTable{m_db, table, columns}.execute();
	}

	/**
	 * @brief Constructs 'INSERT TABLE' query
	 * @param table database table to apply query to
	 * @return 'INSERT TABLE' query @see LSqlInsertQuery
	 */
	QueryInsert insertQuery(const QString &table)
	{

		return QueryInsert {table, m_db};
	}

	QuerySelect selectQuery(const QString &expressions, const QString &tables)
	{
		return QuerySelect{expressions, tables, m_db};
	}

private:
	/**
	 * @brief internal database object
	 */
	QSqlDatabase m_db;
};

} // namespace LSql


#endif // DATABASE_H
