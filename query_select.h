#ifndef QUERY_SELECT_H
#define QUERY_SELECT_H

/**
 * @file query_select.h
 * Provides interface for 'SELECT' query
 */

#include "abstract_query.h"
#include "select_query_result.h"

namespace LSql {

/**
 * @brief 'SELECT' query wrapper
 */
class QuerySelect : public AbstractQuery
{
public:
	explicit QuerySelect(const QString &expressions, const QString table,
						 const QSqlDatabase &db) : AbstractQuery{table, db}, m_expressions{expressions}
	{

	}

	QuerySelect &where(const QString &where)
	{
		m_where = where;
		return *this;
	}

	/**
	 * @brief Prepare query string to execute
	 */
	void prepareQueryString() override
	{
		m_query_string = QLatin1String("SELECT %1 FROM %2").arg(m_expressions, m_tables);
		if (!m_where.isEmpty()) {
			(void)m_query_string.append(" WHERE %1").arg(m_where);
		}
	}

	/**
	 * @brief execute query
	 * @return query result @see SelectQueryResult
	 */
	SelectQueryResult execute()
	{
		prepareQueryString();
		qDebug() << "query = " << m_query_string;
		if (!m_query->prepare(m_query_string)) {
			qDebug() << "failed to prepare the query: " << m_query->lastQuery();
		} else {
			m_query->exec();
		}
		return SelectQueryResult {m_query};
	}

private:
	/**
	 * @brief 'expressions' string
	 */
	QString m_expressions{};

	/**
	 * @brief 'where' string
	 */
	QString m_where{};
};
} // namespace LSql

#endif // QUERY_SELECT_H
