/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "private/utils.hpp"
#include <boost/lexical_cast.hpp>

using namespace strus;
using namespace strus::utils;

std::string utils::tostring( int val)
{
	try
	{
		return boost::lexical_cast<std::string>( val);
	}
	catch (...)
	{
		throw std::runtime_error( "failed to convert number to string");
	}
}

unsigned int utils::touint( const std::string& val)
{
	try
	{
		return boost::lexical_cast<unsigned int>( val);
	}
	catch (...)
	{
		throw std::runtime_error( "failed to convert string to number");
	}
}

