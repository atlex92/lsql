#ifndef SELECT_QUERY_RESULT_H
#define SELECT_QUERY_RESULT_H

/**
 * @file select_query_result.h
 * Provides class for SELECT query result
 */

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "query_result.h"
namespace LSql {

/**
 * @brief SELECT query result wrapper
 */
class SelectQueryResult : public QueryResult
{
public:
	using QueryResult::QueryResult;
	SelectQueryResult(const SelectQueryResult &other) = delete;

	/**
	 * @brief Return the value of field column in the current record
	 * @param column column to get the value from
	 * @return value of field column in the current record
	 */
	QVariant value(const int column) const
	{
		return m_query->value(column);
	}

	/**
	 * @brief Return the value of field column in the current record
	 * @param column column to get the value from
	 * @return value of field column in the current record
	 */
	QVariant value(const QString &column) const
	{
		return m_query->value(column);
	}

	/**
	 * @brief Retrieves the next record in the result, if available,
	 * and positions the query on the retrieved record
	 * @return TRUE if the record is successfully retrieved, otherwise FALSE
	 */
	bool next()
	{
		return m_query->next();
	}

	/**
	 * @brief Retrieves the previous record in the result, if available,
	 * and positions the query on the retrieved record.
	 * @return TRUE if the record is successfully retrieved, otherwise FALSE
	 */
	bool previous()
	{
		return m_query->previous();
	}

	/**
	 * @brief Discards the current result set and navigates to the next if available.
	 * @return  FALSE if a new result set isn't available, otherwise TRUE
	 */
	bool nextResultSet()
	{
		return m_query->nextResult();
	}

	/**
	 * @brief Retrieves the first record in the result, if available, and positions the query on the retrieved record.
	 * @return TRUE if the record is successfully retrieved, otherwise FALSE
	 */
	bool first()
	{
		return m_query->first();
	}

	/**
	 * @brief Retrieves the last record in the result, if available, and positions the query on the retrieved record.
	 * @return TRUE if the record is successfully retrieved, otherwise FALSE
	 */
	bool last()
	{
		return m_query->last();
	}

	/**
	 * @brief Retrieves the record at position index, if available, and positions the query on the retrieved record
	 * @param index position to seek
	 * @param relative flag for index interpretation
	 * @return TRUE if the record is successfully retrieved, otherwise FALSE
	 */
	bool seek(const int index, const bool relative = false)
	{
		return m_query->seek(index, relative);
	}

	/**
	 * @brief Returns the current internal position of the query
	 * @return current internal position of the query
	 */
	int currentPosition() const
	{
		return m_query->at();
	}

	/**
	 * @brief Check if query is positioned on a valid record
	 * @return true if the query is currently positioned on a valid record, otherwise returns false
	 */
	bool isValid() const
	{
		return m_query->isValid();
	}

	/**
	 * @brief Check if the query if forward only
	 * @return true if you can only scroll forward through a result set; otherwise returns false.
	 */
	bool isForwardOnly() const
	{
		return m_query->isForwardOnly();
	}

	/**
	 * @brief Get number of rows
	 * @return the size of the result (number of rows returned), or -1 if the size cannot be determined or if the database does not support reporting information about query sizes
	 */
	int size() const
	{
		return m_query->size();
	}

	/**
	 * @brief Get bound value
	 * @param column number of column for the record
	 * @return the value for the placeholder at position column
	 */
	QVariant boundValue(const int column) const
	{
		return m_query->boundValue(column);
	}

	/**
	 * @brief Get bound value
	 * @param column alias
	 * @return the value for the aliasName
	 */
	QVariant boundValue(const QString &aliasName) const
	{
		return m_query->boundValue(aliasName);
	}

	/**
	 * @brief Returns a list of bound values
	 * @return list of bound values
	 */
	QVariantList boundValues() const
	{
		return m_query->boundValues();
	}

};

#endif // SELECT_QUERY_RESULT_H

}
