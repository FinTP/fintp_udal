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

#include "ODBCColumn.h"
#include <iostream>
#include <string>

#ifdef DB2_ONLY
#include <SQLLIB\include\sqlcli.h>
#elif defined INFORMIX_ONLY
#ifdef WIN32
#include <cli\sql.h>
#else
#include <infxcli.h>
#endif
#else
#include <sql.h>
#endif

using namespace std;

#include "Trace.h"

// ODBCColumn Implementation
//
//  - ODBCColumnBase Class
//	- ODBCColumn 	Class

namespace FinTP {

	template <>
	void ODBCColumn< string >::Sync()
	{
		if ( ( m_StoragePointer != NULL ) && ( m_BufferIndicator != SQL_NULL_DATA ) )
			m_Value = string ( ( char* )m_StoragePointer );
	}

	/// ODBCColumn implementation implementation
	template < class T >
	ODBCColumn< T >::ODBCColumn( unsigned int dimension, int scale, const string name )
		: DataColumn< T >( dimension, scale, name )
	{
		DEBUG2( "Constructor" );
	}

	template <>
	ODBCColumn< short >::ODBCColumn( unsigned int dimension, int scale, const string name )
		: DataColumn< short >( dimension, scale, name )
	{
		DEBUG2( "Constructor" );
	}

	template <>
	ODBCColumn< long >::ODBCColumn( unsigned int dimension, int scale, const string name )
		: DataColumn< long >( dimension, scale, name )
	{
		DEBUG2( "Constructor" );
	}

	template <>
	ODBCColumn< string >::ODBCColumn( unsigned int dimension, int scale, const string name )
		: DataColumn< string >( dimension, scale, name )
	{
		DEBUG2( "Constructor" );
	}

	template < class T >
	ODBCColumn< T >::~ODBCColumn()
	{
		DEBUG2( "Destructor" );
	}

	// TODO remove overrides
	template < class T >
	void ODBCColumn< T >::setValue( T value )
	{
		DataColumn< T >::setValue( value );
		//m_Value = value;
	}

	template < class T >
	T ODBCColumn< T >::getValue()
	{
		return DataColumn< T >::getValue();
		//return m_Value;
	}

	template < class T >
	DataColumnBase* ODBCColumn< T >::Clone()
	{
		//DEBUG( "Cloning column ... " );
		ODBCColumn< T >* copy = new ODBCColumn< T >( DataColumn< T >::m_Dimension, DataColumn< T >::m_Scale );

		copy->setType( this->getColType() );
		copy->setBaseType( DataColumn< T >::m_BaseType );
		copy->setValue( DataColumn< T >::m_Value );

		//DEBUG( "orig value : "  << m_Value );
		//DEBUG( "copy value : "  << copy->getValue() );
		return copy;
	}

	template < class T >
	void ODBCColumn< T >::Sync()
	{
		//do nothing;
	}
}
