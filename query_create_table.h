#ifndef QUERY_CREATE_TABLE_H
#define QUERY_CREATE_TABLE_H

/**
 * @file query_create_table.h
 * Provides interface for 'CREATE TABLE' query
 */

#include "abstract_query.h"
#include "query_result.h"

namespace LSql {

/**
 * @brief 'CREATE TABLE' query wrapper
 */
class QueryCreateTable : public AbstractQuery
{
public:
	explicit QueryCreateTable(const QSqlDatabase &db, const QString& table, const QString& columns)
		:	AbstractQuery{table, db}, m_columns{columns}{

	}

	/**
	 * @brief execute query
	 * @return query result object @see LSqlQueryResult
	 */
	QueryResult execute()
	{
		prepareQueryString();
		if (!m_query->prepare(m_query_string)) {
			qDebug() << "failed to prepare the query: " << m_query->lastQuery();
		} else {
			m_query->exec();
		}
		return QueryResult {m_query};
	}
protected:
	/**
	 * @brief columns to be affected, separated with space
	 */
	QString m_columns{};
private:
	/**
	 * @brief Prepare query string to execute
	 */
	void prepareQueryString() override
	{
		m_query_string = QLatin1String("CREATE TABLE %1 (%2)").arg(m_tables, m_columns);
	}
};

} // namespace LSql

#endif // QUERY_CREATE_TABLE_H
