#ifndef ABSTRACT_QUERY_H
#define ABSTRACT_QUERY_H

/**
 * @file abstract_query.h
 * @brief Base query class definiton
 */

#include <QSqlQuery>
#include <QString>

namespace LSql {
/**
 * @brief Base abstract query class
 *
 * All query classes should be inherited from AbstractQuery class
 */
class AbstractQuery
{
public:
	/**
	 * @brief Create new AbstractQuery object
	 * @param tables database tables to apply query to
	 * @param db database object to apply query to
	 */
	explicit AbstractQuery(const QString tables, const QSqlDatabase &db) : m_tables{tables}, m_query{new QSqlQuery{db}}
	{

	}
protected:
	/**
	 * @brief Prepare query string to execute
	 */
	virtual void prepareQueryString() = 0;

	/**
	 * @brief Tables list to apply query to
	 */
	QString m_tables{};

	/**
	 * @brief Internal query object @see QSqlQuery
	 */
	QSharedPointer<QSqlQuery> m_query{};

	/**
	 * @brief Query string to be executed
	 */
	QString m_query_string{};
};
} // namespace LSql

#endif // ABSTRACT_QUERY_H
