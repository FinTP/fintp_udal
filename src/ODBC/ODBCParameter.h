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

#ifndef ODBCPARAMETER_H
#define ODBCPARAMETER_H

#include "../DataParameter.h"
#include "Trace.h"

#include <string>
#include <vector>
#include <cstring>

using namespace std;

namespace FinTP
{
	/**
	 * Store parameter information used by the database instance to execute queries (select) or nonqueries (insert, update, delete)
	**/
	template < class T >
	class ExportedUdalObject ODBCParameter : public DataParameter< T >
	{
		public :

			// create DB2 parameter, implicit IN parameter
			inline ODBCParameter( DataParameterBase::PARAMETER_DIRECTION paramDirection = DataParameterBase::PARAM_IN )
				: DataParameter< T >( paramDirection ) {}

			/**
			* Constructor
			* \param paramName	type string.					The parameter name
			* \param paramDirection type PARAMETER_DIRECTION	The parameter direction (in, out or inout)
			**/
			inline ODBCParameter( const string& paramName, DataParameterBase::PARAMETER_DIRECTION paramDirection = DataParameterBase::PARAM_IN)
				: DataParameter< T >( paramName, paramDirection ) {}

			inline ODBCParameter( const ODBCParameter< T >& source ) {};

			inline ~ODBCParameter() {};

			inline void setValue( T columnValue )
			{
				DEBUG2( "Set value [" << columnValue << "]" );
				DataParameter< T >::m_Value = columnValue;
				if ( DataParameter< T >::m_Dimension == 0 )
					DataParameter< T >::m_Dimension = sizeof( DataParameter< T >::m_Value );
			}

			inline void push_back( const string& value ) { throw logic_error("Not supported by this data type"); }
			inline const string& getElement( size_t position ) const { throw logic_error("Not supported by this data type"); }

			inline T getValue() const
			{
				DEBUG2( "Get value [" << DataParameter< T >::m_Dimensionm_Value << "]" );
				return DataParameter< T >::m_Value;
			}

			inline void setDimension( const unsigned int dimension )
			{
				DataParameterBase::setDimension( dimension );
			}

			inline unsigned int getDimension() const
			{
				return DataParameterBase::getDimension();
			}
	};


	template<>
	inline void ODBCParameter< vector< string > >::push_back( const string& value )
	{
		m_Value.push_back( value );
	}

	template <>
	inline DataType::DATA_TYPE DataParameter< vector< string > >::getParamType()
	{
		return DataType::ARRAY;
	}

	template <>
	inline unsigned int ODBCParameter< vector< string > >::getDimension() const
	{
		return m_Value.size();
	}

	template <>
	inline const string& ODBCParameter< vector< string > >::getElement(  size_t position ) const
	{
		return m_Value[position];
	}

	//override for string
	template<>
	inline unsigned int ODBCParameter< string >::getDimension() const
	{
		// ODBC custom hack
		return m_Dimension + 1;
	}

	template<>
	inline void ODBCParameter< string >::setDimension( const unsigned int dimension )
	{
		//DEBUG( "Should be equal ( before resize : " ) << m_StoragePointer << " , " << ( void* )m_Value.data() );
		//m_Value.resize( dimension );
		DEBUG2( "Set dimension ["  << dimension << "]" );
		DataParameterBase::setDimension( dimension );

		if( m_StoragePointer != NULL )
			delete[] m_StoragePointer;

		m_StoragePointer = new unsigned char[ m_Dimension + 1 ];//( void * )m_Value.data();
		memset( m_StoragePointer, 0, m_Dimension + 1 );
		//DEBUG( "Should be equal ( after resize : " ) << m_StoragePointer << " , " << ( void* )m_Value.data() );
	}

	template<>
	inline void ODBCParameter< string >::setValue( string columnValue )
	{
		//DEBUG( "SetValue : "  << columnValue );
		string::size_type paramLength = columnValue.length();
		DEBUG2( "Dimension : [" << m_Dimension << "] Address : [" << m_StoragePointer << "]" );

		if( m_StoragePointer == NULL )
			dynamic_cast< ODBCParameter< string > * >( this )->setDimension( paramLength );
		DEBUG2( "Dimension : ["  << m_Dimension << "] Address : [" << m_StoragePointer << "]" );

		if( m_Dimension < paramLength )
		{
			TRACE( "Parameter storage size is less than source. Data right truncation from " << paramLength << " chars to " << m_Dimension );
			memcpy( m_StoragePointer, columnValue.c_str(), m_Dimension );
			//( ( unsigned char* )m_StoragePointer )[ m_Dimension - 1 ] = 0;
		}
		else
		{
			DEBUG2( "Storage size ok." );
			memcpy( m_StoragePointer, columnValue.c_str(), paramLength );
		}
	}

	template<>
	inline string ODBCParameter< string >::getValue() const
	{
		string returnValue = string( ( char* )m_StoragePointer, m_Dimension );

		//DEBUG( "pValue : "  << ( void* )m_Value.data() );
#ifdef WIN32
		DEBUG2( "Get value : ["  << returnValue << "]" );
#endif

		//DEBUG( "*Size : "  << strlen( ( ( char* )m_StoragePointer ) ) );
		//DEBUG( "Should be equal : "  << m_StoragePointer << " , " << ( void* )m_Value.data() );

		return returnValue;
	}

	template <>
	inline ODBCParameter< string >::~ODBCParameter()
	{
		DEBUG2( "Destructor" );
		if( m_StoragePointer != NULL )
		{
			delete[] m_StoragePointer;
			m_StoragePointer = NULL;
		}
	}
}

#endif // ODBCPARAMETER_H

