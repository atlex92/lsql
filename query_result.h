#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

/**
 * @file query_result.h
 * @brief Query result class definition
 */

#include <QSqlQuery>
#include <QSqlError>

namespace LSql {
/**
 * @brief query result wrapper
 */
class QueryResult
{
	friend class QueryInsert;
	friend class QueryCreateTable;
	friend class QuerySelect;
public:
	/**
	 * @brief Check if query is Active
	 * @return true if query is successfully executed but not yet finished with, otherwise false
	 */
	bool isActive() const
	{
		return m_query->isActive();
	}

	/**
	 * @brief Get number of affected rows
	 * @return number of affected rows
	 */
	int rowsAffected() const
	{
		return m_query->numRowsAffected();
	}

	/**
	 * @brief Get the last Insert Object ID
	 * @return the object ID of the most recent inserted row
	 */
	QVariant lastInsertId() const
	{
		return m_query->lastInsertId();
	}

	/**
	 * @brief Get the last query error
	 * @return last query error @see QSqlError
	 */
	QSqlError lastError() const
	{
		return m_query->lastError();
	}

	/**
	 * @brief Get the last query string
	 * @return the text of the current query being used
	 */
	QString lastQuery() const
	{
		return m_query->lastQuery();
	}

	/**
	 * @brief Get the last executed query string
	 * @return  the last query that was successfully executed
	 */
	QString lastExecutedQuery() const
	{
		return m_query->executedQuery();
	}

	/**
	 * @brief Get the pointer to internal query object
	 * @return internal query object @see QSqlQuery
	 */
	const QSqlQuery *raw()
	{
		return m_query.get();
	}
protected:
	/**
	 * @brief internal query object @see QSqlQuery
	 */
	QSharedPointer<QSqlQuery> m_query{};
private:
	/**
	 * @brief Constructs new QueryResult object
	 * @param query internal query object @see QSqlQuery
	 */
	explicit QueryResult(QSharedPointer<QSqlQuery> query) : m_query{query}
	{

	}
};
} // namespace LSql



#endif // QUERY_RESULT_H
