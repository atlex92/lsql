#include <QCoreApplication>
#include <QScopedPointer>
#include "database.h"

using namespace LSql;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Database db{"QSQLITE"};
	db.setName("test.db");
	if (!db.open()) {
		qDebug() << "failed to open database";
	}

	QueryResult res =
		db.createTable("records", "id integer primary key, firstname varchar(20)");

	if (!res.isActive()) {
		qDebug() << "query failed, last error: " << res.lastError().text();
	}

	res = db.insertQuery("records").values(1, "Pechkin").values(2, "Ivanov").execute();

	if (!res.isActive()) {
		qDebug() << "query failed, last error: " << res.lastError().text();
	}

	auto select_res{db.selectQuery("*", "records").execute()};

	if (!select_res.isActive()) {
		qDebug() << "select failed, last error: " << select_res.lastError().text();
	} else {
		qDebug() << select_res.isActive();
		qDebug() << select_res.isValid();
		qDebug() << "fond " << select_res.size() << " records:";
		while (select_res.next()) {
			qDebug() << select_res.value("id") << ": " << select_res.value("firstname");
		}
	}

	return a.exec();
}
