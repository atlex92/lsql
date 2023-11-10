#include "query_insert.h"

using LSql::QueryInsert;
using LSql::QueryResult;

QueryInsert &QueryInsert::values(const QVariant &value)
{
	m_currentRowInsertValues.append(value);

	if (m_rowsToInsert.empty()) {
		//! first row received, so we know number of rows
		m_rowsToInsert.resize(m_currentRowInsertValues.size());
	} else {
		Q_ASSERT_X(m_rowsToInsert.size() == m_currentRowInsertValues.size(), "QueryInsert",
				   "All insert values must have the same column number");
	}

	for (qsizetype i{}; i < m_currentRowInsertValues.size(); i++) {
		m_rowsToInsert[i].append(m_currentRowInsertValues.at(i));
	}

	m_currentRowInsertValues.clear();

	return *this;
}

QueryResult QueryInsert::execute()
{
	prepareQueryString();
	if (!m_query->prepare(m_query_string)) {
		qDebug() << "failed to prepare the query: " << m_query->lastQuery();
	} else {
		if (m_rowsToInsert.size() > 0u && m_rowsToInsert.first().size() > 1u) {
			//! if multiple rows are to be inserted
			for (qsizetype i{}; i <  m_rowsToInsert.size(); i++) {
				m_query->addBindValue(m_rowsToInsert.at(i));
			}
			m_query->execBatch();
		} else {
			for (qsizetype i{}; i <  m_rowsToInsert.size(); i++) {
				m_query->addBindValue(m_rowsToInsert.at(i).first());
			}
			m_query->exec();
		}
	}
	return QueryResult{m_query};
}

void QueryInsert::prepareQueryString()
{
	QStringList placeholderList;

	for (qsizetype i{}; i < m_rowsToInsert.size(); i++) {
		placeholderList.append(QLatin1String("?"));
	}
	const QString placeholdersString{placeholderList.join(QLatin1String(","))};
	m_query_string = QLatin1String("INSERT INTO %1 VALUES(%2)").arg(m_tables, placeholdersString);
}
