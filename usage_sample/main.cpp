/*
* FinTP - Financial Transactions Processing Application
* Copyright (C) 2013 Business Information Systems (Allevo) S.R.L.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>
* or contact Allevo at : 031281 Bucuresti, 23C Calea Vitan, Romania,
* phone +40212554577, office@allevo.ro <mailto:office@allevo.ro>, www.allevo.ro.
*/

#include <boost/scoped_ptr.hpp>

#include <Trace.h>

#include <ConnectionString.h>
#include <Database.h>
#include <DatabaseProvider.h>

#ifdef WITH_ODBC
#include <ODBC/ODBCDatabase.h>
#endif

using namespace FinTP;

void walkDataSet(const DataSet& data)
{
	size_t nrOfRows = data.size();
	size_t nrOfColumns;

	if (nrOfRows > 0)
		nrOfColumns = data[0]->size();
	else
	{
		cout << "No results!\n";
		return;
	}

	cout << nrOfColumns << " columns and " << nrOfRows << " rows returned\n";

	for (size_t i = 0; i < nrOfRows; i++)
	{
		cout << "Row " << i << ":\n";

		map< std::string, DataColumnBase* >::iterator it = data[ i ]->begin();
		map< std::string, DataColumnBase* >::iterator last = data[ i ]->end();

		do
		{
			DataColumnBase *crtColumn = it->second;

			cout << "Column [" << it->first << "] : Dimension : " <<  crtColumn->getDimension() << "\n";

			DataType::DATA_TYPE type = crtColumn->getType();

			switch (crtColumn->getType())
			{
				case DataType::SHORTINT_TYPE :
					cout << ((DataColumn< short >*)crtColumn)->getValue() << "\n";
					break;

				case DataType::CHAR_TYPE :
					cout << ((DataColumn< string >*)crtColumn)->getValue() << "\n";
					break;

				case DataType::LONGINT_TYPE:
					cout << ((DataColumn< long >*)crtColumn)->getValue() << "\n";
					break;
			}

			it++;
		}
		while (it != last);
	}
}

int main(int argc, char* argv[])
{
	FileOutputter::setLogPrefix(argv[0]);

	boost::scoped_ptr <Database> crtDatabase;

	try
	{
		std::string provider, databaseName, userName, password;

		cout << "Choose from \n Oracle (with Oracle Call Interface)\n DB2\n Informix\n SqlServer\n Postgres\n Type anything else for generic ODBC\n\nDatabase provider: ";
		cin >> provider;

		bool genericODBC = true;

		if (provider=="Oracle"||provider=="DB2"||provider=="Informix"||provider=="SqlServer"||provider=="Postgres")
			genericODBC = false;

		boost::scoped_ptr <DatabaseProviderFactory> databaseProvider;

		if (!genericODBC)
		{
			databaseProvider.reset(DatabaseProvider::GetFactory(provider));

			if (databaseProvider == NULL)
				throw runtime_error("Unable to create database provider");
		}

		cout << "Database name: ";
		cin >> databaseName;
		cout << "Username: ";
		cin >> userName;
		cout << "Password: ";
		cin >> password;

		ConnectionString connectionString(databaseName, userName, password);

		if (!genericODBC)
			crtDatabase.reset(databaseProvider->createDatabase());
#ifdef WITH_ODBC
		else
			crtDatabase.reset(new ODBCDatabase);
#endif

		if (crtDatabase == NULL)
			throw runtime_error("Unable to create database definition");

		crtDatabase->Connect(connectionString);

		if (crtDatabase->IsConnected())
			cout << "\nConnected to " << databaseName << "!\n\n";
		else
			throw runtime_error("Could not connect to " + databaseName + "\n");

		crtDatabase->BeginTransaction();

		cout << "Check log file for results\nType ! to exit, p to print last successful result to screen\n";

		std::string query;
		cout << "> ";

		boost::scoped_ptr <DataSet> result;

		while (1)
		{
			cin >> ws;
			getline(cin, query);

			if (query=="p")
			{
				if (result!=NULL)
					walkDataSet(*result.get());
				cout << "\n> ";
				continue;
			}

			if (query=="!")
				break;

			try
			{
				try
				{
					result.reset (crtDatabase->ExecuteQuery(DataCommand::INLINE, query));
				}
				catch (const DBWarningException& e)
				{
					cout << e.what();
				}
				
				if (result != NULL)
				{
					size_t nrOfRows = result.get()->size();

					if (nrOfRows > 0)
						Database::DisplayDataSet(result.get());

					cout << "Execution succesful!\n\n> ";
				}
			}
			catch (const DBErrorException& e)
			{
				cout << e.what();
				cout << "\nExecution failed!\n\n> ";
			}
		}

		crtDatabase->EndTransaction(TransactionType::COMMIT);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}

	if (crtDatabase != NULL && crtDatabase->IsConnected())
		crtDatabase->Disconnect();

	return 0;
}
