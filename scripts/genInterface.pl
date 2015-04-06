#!/usr/bin/perl

use strict;
use warnings;
use 5.014;

my $num_args = $#ARGV + 1;
if ($num_args == 0)
{
	print STDERR "Usage: genInterface.pl {<inputfile>}\n";
	print STDERR "<inputfile>: name of input file to process\n";
	exit;
}

sub getTokens
{
	my @rt = ();
	my ($src) = @_;
	my $tok = "";
	my $ch;
	foreach $ch( split('', $src))
	{
		if ($ch =~ m/[ \t]/)
		{
			if (length( $tok) > 0)
			{
				push @rt, $tok;
				$tok = "";
			}
		}
		elsif ($ch =~ m/[a-zA-Z0-9_:.]/)
		{
			$tok .= $ch;
		}
		else
		{
			if (length( $tok) > 0)
			{
				push @rt, $tok;
				$tok = "";
			}
			push @rt, $ch;
		}
	}
	return @rt;
}

my @tokens = {};
my $ti = 0;
my $te = 0;

sub initSource
{
	my ($src) = @_;
	@tokens = getTokens( $src);
	$ti = 0;
	$te = $#tokens + 1;
}

sub nextToken()
{
	if ($ti+1 >= $te)
	{
		return "";
	}
	return $tokens[ ++$ti];
}

sub prevToken()
{
	if ($ti > 0)
	{
		--$ti;
	}
}

sub currToken()
{
	if ($ti >= $te)
	{
		return "";
	}
	return $tokens[ $ti];
}

sub hasToken()
{
	if ($ti+1 >= $te)
	{
		return 0;
	}
	return 1;
}

sub skipBrackets
{
	my ($sb,$eb) = @_;
	my $bcnt = 1;
	while ($bcnt && hasToken())
	{
		my $tok = nextToken();
		if ($tok eq $eb)
		{
			--$bcnt;
		}
		elsif ($tok eq $sb)
		{
			++$bcnt;
		}
	}
	hasToken() or die "unexpected end of file while scanning for end bracket";
}

sub joinIdent
{
	my ($orig, $suffix) = @_;
	if ($orig eq "")
	{
		$orig = $suffix;
	}
	else
	{
		$orig = $orig . " " . $suffix;
	}
}

# interfaceClasses element structure:
# <classname>%<method>%...
# <method>	= <methodname>!<paramtype>!...
# <paramtype>	= STRING
my @interfaceClasses = ();

sub parseType
{
	my $prefix = "";
	my $type = nextToken();
	while ($type eq "const" || $type eq "unsigned")
	{
		$prefix = joinIdent( $prefix, $type);
		$type = nextToken();
	}
	if ($type eq "std::vector")
	{
		$type = "";
		if (nextToken() ne "<")
		{
			die "unexpected token after std::vector";
		}
		my $bcnt = 1;
		while (hasToken() && $bcnt > 0)
		{
			my $tok = nextToken();
			if ($tok eq "<")
			{
				++$bcnt;
			}
			elsif ($tok eq ">")
			{
				--$bcnt;
			}
			elsif ($tok =~ m/[;=\{\}\(\)]/)
			{
				die "expected '>' after std::vector template argument";
			}
			else
			{
				$type = joinIdent( $type, $tok);
			}			
		}
		if (!hasToken())
		{
			die "unexpected end of file in std::vector template argument";
		}
		$type = $type . "[]";
	}
	my $tok = nextToken();
	while ($tok eq "*")
	{
		$prefix = $prefix . '^';
		$tok = nextToken();
	}
	if ($tok eq "&")
	{
		$prefix = $prefix . '&';
	}
	else
	{
		prevToken();
	}
	return joinIdent( $prefix, $type);
}

sub parseInterface
{
	my ($classname) = @_;
	my @methodlist = ();
	my $bcnt = 1;
	nextToken();
	while (hasToken() && $bcnt > 0)
	{
		my $tok = currToken();
		if ($tok eq '}')
		{
			--$bcnt;
			nextToken();
		}
		elsif ($tok eq '{')
		{
			++$bcnt;
			nextToken();
		}
		elsif ($bcnt == 1 && $tok eq 'virtual')
		{
			my $tok = nextToken();
			if ($tok ne '~')
			{
				prevToken();
				my $returntype = parseType();
				my $methodname = nextToken();
				my @paramlist = ();

				if (nextToken() ne "(")
				{
					die "syntax error parsing method: oval bracket '(', start of argument list expected";
				}
				while (nextToken() ne ")")
				{
					prevToken();
					$tok = parseType();
					push @paramlist, $tok;
					$tok = nextToken();

					if ($tok =~ m/^[a-zA-Z_][a-zA-Z0-9_]*$/)
					{
						$tok = nextToken();
						if ($tok eq '=')
						{
							nextToken(); #... skip argument of assign
							$tok = nextToken();
							if ($tok eq '(')
							{
								skipBrackets( "(",")");
								$tok = nextToken();
							}
						}
					}
					if ($tok eq ")")
					{
						prevToken();
					}
					elsif ($tok ne ",")
					{
						die "expected ',' as separator or ')' as end of parameter list";
					}
				}
				$tok = nextToken();
				if ($tok eq "const")
				{
					$methodname = "const " . $methodname;
				}
				if ($#paramlist >= 0)
				{
					push( @methodlist, $methodname . "!" . $returntype . "!" . join( "!", @paramlist));
				}
				else
				{
					push( @methodlist, $methodname . "!" . $returntype);
				}
			}
		}
		else
		{
			nextToken();
		}
	}
	push( @interfaceClasses, $classname . "%" . join( "%", @methodlist));
	hasToken() or die "unexpected end of source parsing interface";
}

my @inputfiles = @ARGV;
my $inputfile;
foreach $inputfile( @inputfiles)
{
	print STDERR "process file $inputfile\n";
	open( INPUT, "<$inputfile") or die "Couldn't open file $inputfile, $!";

	my $line;
	my $src;
	while (<INPUT>)
	{
		chomp;
		if (/^[\#]/)
		{
			$line = '';
		}
		elsif (/(^.*)[\/][\/][\/]/)
		{
			$line = $1;
		}
		elsif (/(^.*)[\/][\/]/)
		{
			$line = $1;
		}
		else
		{
			$line = $_;
		}
		$line =~ s/\t+/ /g;
		$src .= $line . ' ';
	}
	$src =~ s@/\*[^\*]*\*/@@g;

	my $interfaceClass;
	initSource( $src);

	while (hasToken())
	{
		my $tok = currToken();
		if ($tok eq "class")
		{
			my $classname = nextToken();
			if (nextToken() eq "{")
			{
				if ($classname =~ m/Interface$/)
				{
					parseInterface( $classname);
				}
				else
				{
					skipBrackets( "{", "}" );
				}
			}
		}
		++$ti;
	}
}
@interfaceClasses = sort @interfaceClasses;

sub printParsedDump
{
	my $ic;
	foreach $ic( @interfaceClasses)
	{
		print "$ic\n";
	}
}

sub getInterfaceName
{
	my ($def) = @_;
	if ($def =~ m/^([^\%]*)[\%]/)
	{
		return $1;
	}
	die "illegal interface definition: $def";
}

sub getMethodName
{
	my ($def) = @_;
	if ($def =~ m/^([^\!]*)[\!]/)
	{
		my $callname = $1;
		$callname =~ s/^const //;
		return $callname;
	}
	die "illegal method definition: $def";
}

sub getInterfaceEnumName
{
	my ($interf) = @_;
	$interf =~ s/Interface$//;
	return "ClassId_" . $interf;
}

sub getClassEnumSource
{
	my $rt = "\nenum ClassId\n{";
	my $ii = 0;

	my $ci;
	foreach $ci(@interfaceClasses)
	{
		my $interfacename = getInterfaceName($ci);
		if ($ii > 0)
		{
			$rt .= ",";
		}
		$rt .= "\n\t" . getInterfaceEnumName( $interfacename);
		++$ii;
	}
	$rt .= "\n};\n";
	return $rt;
}

sub getMethodEnumSource
{
	my $rt = "\nenum CallId\n{";
	my $ii = 0;
	my $classcnt = 0;

	foreach (@interfaceClasses)
	{
		my @mth = split('%');
		my $classname = shift( @mth);
		$classcnt = $classcnt + 100;
		my $callcnt = $classcnt;
		my $mm;
		foreach $mm(@mth)
		{
			my $callname = getMethodName( $mm);
			++$callcnt;
			my $id = "CallId_" . $classname . "_" . $callname . " = $callcnt";
			if ($ii > 0)
			{
				$rt .= ",";
			}
			$rt .= "\n\t$id";
			++$ii;
		}
	}
	$rt .= "\n};\n";
	return $rt;
}

sub getMethodParamDeclarationSource
{
	my ($param) = @_;
	my $isarray = 0;
	if ($param =~ m/\[\]$/)
	{
		$isarray = 1;
		$param =~ s/\[\]$//;
	}
	my $isconst = 0;
	if ($param =~ m/^const[ \^\&]+/)
	{
		$isconst = 1;
		$param =~ s/^const[ ]*//;
	}
	my $indirection = 0;
	if ($param =~ m/^([\^]+)[^\^]/)
	{
		$indirection = length( $1);
		$param =~ s/^[\^]+([^\^]*)$/$1/;
	}
	$param =~ s/^[ ][ ]*//g;
	my $passbyref = 0;
	if ($param =~ m/^[\&]/)
	{
		$passbyref = 1;
		$param =~ s/^[\&]//;
	}
	print "2>>'$param'\n";
	my $paramlist = "";
	if ($isconst)
	{
		$paramlist .= "const ";
	}
	my @parampartlist = split( ' ', $param);
	my $gg;
	my $paramname = shift( @parampartlist);
	
	foreach $gg(@parampartlist)
	{
		$paramname .= "<" . $gg;
	}
	foreach $gg(@parampartlist)
	{
		$paramname .= "> ";
	}
	if ($isarray)
	{
		$paramlist .= "std::vector<" . $paramname . ">";
	}
	else
	{
		$paramlist .= $paramname;
	}
	my $ii;
	for ($ii=0; $ii<$indirection; ++$ii)
	{
		$paramlist .= "*";
	}
	if ($passbyref)
	{
		$paramlist .= "&";
	}
	return $paramlist;
}

sub getMethodDeclarationSource
{
	my ($method) = @_;
	my @param = split( '!', $method);
	my $methodname = shift( @param);
	my $isconst = 0;
	if ($methodname =~ m/^const /)
	{
		$isconst = 1;
		$methodname =~ s/^const //;
	}
	my $paramlist = "";
	my $retval = shift( @param);
	my $pi = 0;
	my $pp;
	foreach $pp( @param)
	{
		if ($paramlist ne "")
		{
			$paramlist .= ", ";
		}
		$paramlist .= getMethodParamDeclarationSource( $pp) . " p" . $pi;
	}
	my $rt = "virtual "
			. getMethodParamDeclarationSource( $retval) . " "
			. $methodname . "("
			. $paramlist . ")";
	if ($isconst)
	{
		$rt .= " const";
	}
	return $rt;
}

sub getClassImplementationSource
{
	my $rt = "";
	my $ii = 0;
	
	foreach (@interfaceClasses)
	{
		my $interfacename = getInterfaceName($_);
		my $classname = $interfacename;
		$classname =~ s/Interface$//;
		$classname .= "Impl";
		$rt .= "\nclass $classname\n\t\t:public RcpInterfaceStub\n\t\t,public strus:$interfacename\n{\npublic:";
		$rt .= "\n\tvirtual ~$classname(){}\n";
		$rt .= "\n\t$classname()\n\t\t:RcpInterfaceStub(" . getInterfaceEnumName($interfacename) ."){}\n";
		my @mth = split('%');
		$classname = shift( @mth);
		my $mm;
		foreach $mm( @mth)
		{
			$rt .= "\n\t" . getMethodDeclarationSource( $mm) .";";
		}
		$rt .= "\n};\n";
		++$ii;
	}
	$rt .= "\n};\n";
	return $rt;
}

my $interfacefile = "include/strus/rpcObjects.hpp";
open( CLASSFILE, ">$interfacefile") or die "Couldn't open file $interfacefile, $!";

print CLASSFILE <<EOF;
/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2013,2014 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
*/
#ifndef _STRUS_RPC_OBJECTS_HPP_INCLUDED
#define _STRUS_RPC_OBJECTS_HPP_INCLUDED

namespace strus {
namespace rpc {
EOF

print CLASSFILE getClassEnumSource();
print CLASSFILE getMethodEnumSource();
print CLASSFILE getClassImplementationSource();

print CLASSFILE <<EOF;
}} //namespace
#endif
EOF

printParsedDump();

