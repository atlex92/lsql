#ifndef QUERY_INSERT_H
#define QUERY_INSERT_H

/**
 * @file query_insert.h
 * @brief Provides class for 'INSERT' SQL query
 */

#include "abstract_query.h"
#include "query_result.h"

namespace LSql {
/**
 * @brief 'INSERT' SQL query wrapper
 */
class QueryInsert : public AbstractQuery
{
public:
	using AbstractQuery::AbstractQuery;

	/**
	 * @brief add value to insert
	 * @param value value to insert
	 * @return self object
	 */
	QueryInsert &values(const QVariant &value);

	/**
	 * @brief add values to insert, template method
	 * @param first value to insert
	 * @param rest all other values to insert
	 * @return self object
	 */
	template <typename... Rest>
	QueryInsert &values(const QVariant &first, const Rest &... rest)
	{
		m_currentRowInsertValues.append(first);
		return values(rest...);
	}

	/**
	 * @brief execute query
	 * @return query result @see QueryResult
	 */
	QueryResult execute();
private:
	/**
	 * @brief Prepare query string to execute
	 */
	void prepareQueryString() override;

	/**
	 * @brief list with new row values
	 */
	QVariantList m_currentRowInsertValues;

	/**
	 * @brief vector with rows to be inserted
	 *
	 * Vector contains N QVarianList, each of them represents one column
	 */
	QVector<QVariantList> m_rowsToInsert;
};
} // namespace LSql

#endif // QUERY_INSERT_H
