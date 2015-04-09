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
my %typeRewriteMap = ();
$typeRewriteMap{"unsigned_int"} = "unsigned int";
$typeRewriteMap{"unsigned_char"} = "unsigned char";

sub parseType
{
	my $prefix = "";
	my $type = nextToken();
	my $typeprefix = "";
	while ($type eq "const")
	{
		$prefix = joinIdent( $prefix, $type);
		$type = nextToken();
	}
	while ($type eq "unsigned")
	{
		$typeprefix = $type . '_';
		$type = nextToken();
	}
	my $bcnt = 0;
	my $typepostfix = "";
	if ($type eq "std::vector")
	{
		$typepostfix = "[]";
		$type = "";
	}
	my $tok = nextToken();
	if ($tok eq "<")
	{
		$bcnt = 1;
		while (hasToken() && $bcnt > 0)
		{
			$tok = nextToken();
			if ($tok eq "unsigned")
			{
				$typeprefix = $typeprefix . $tok . '_';
			}
			elsif ($tok eq "*")
			{
				$type .= $tok;
			}
			elsif ($tok eq "<")
			{
				++$bcnt;
			}
			elsif ($tok eq ">")
			{
				--$bcnt;
			}
			elsif ($tok =~ m/[;=\{\}\(\)]/)
			{
				die "expected '>' closing template";
			}
			else
			{
				$type = joinIdent( $type, $typeprefix . $tok);
				$typeprefix = "";
			}
		}
		if (!hasToken())
		{
			die "unexpected end of file in std::vector template argument";
		}
		$tok = nextToken();
	}
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
	return joinIdent( $prefix, $typeprefix . $type . $typepostfix);
}

sub interfaceImplementationClassName
{
	my ($classname) = @_;
	$classname =~ s/Interface$//;
	return $classname . "Impl";
}

sub parseInterface
{
	my ($interfacename) = @_;
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
					die "syntax error parsing method: start of argument list expected";
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
		elsif ($bcnt == 1 && ($tok eq "class" || $tok eq "struct" || $tok eq "enum"))
		{
			my $subClassName = nextToken();
			my $subClassNameComplete = "$interfacename" . "::" . $subClassName;
			$typeRewriteMap{ $subClassName } = $subClassNameComplete;
			$typeRewriteMap{ interfaceImplementationClassName( $interfacename) . "::" . $subClassName } = $subClassNameComplete;
		}
		else
		{
			nextToken();
		}
	}
	push( @interfaceClasses, $interfacename . "%" . join( "%", @methodlist));
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
			my $interfacename = nextToken();
			if (nextToken() eq "{")
			{
				if ($interfacename =~ m/Interface$/)
				{
					parseInterface( $interfacename);
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

sub getParamProperties
{
	my ($classname,$param) = @_;
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
	my $paramlist = "";
	my @parampartlist = split( ' ', $param);
	my $gg;
	my $paramname = shift( @parampartlist);
	if ($typeRewriteMap{ $classname . "::" . $paramname})
	{
		$paramname = $typeRewriteMap{$classname . "::" . $paramname};
	}
	elsif ($typeRewriteMap{$paramname})
	{
		$paramname = $typeRewriteMap{$paramname};
	}
	foreach $gg(@parampartlist)
	{
		if ($typeRewriteMap{$gg})
		{
			$paramname .= "<" . $typeRewriteMap{$gg};
		}
		else
		{
			$paramname .= "<" . $gg;
		}
	}
	foreach $gg(@parampartlist)
	{
		$paramname .= "> ";
	}
	return ($paramname, $isconst, $isarray, $indirection, $passbyref);
}

sub getMethodParamDeclarationSource
{
	my ($classname, $param) = @_;
	my ($paramname, $isconst, $isarray, $indirection, $passbyref) = getParamProperties( $classname, $param);
	if ($isarray)
	{
		$paramname = "std::vector<" . $paramname . ">";
	}
	if ($isconst)
	{
		$paramname = "const " . $paramname;
	}
	my $ii;
	for ($ii=0; $ii<$indirection; ++$ii)
	{
		$paramname .= "*";
	}
	if ($passbyref)
	{
		$paramname .= "&";
	}
	return $paramname;
}

sub getMethodDeclarationHeader
{
	my ($classname, $method) = @_;
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
		++$pi;
		$paramlist .= getMethodParamDeclarationSource( $classname, $pp) . " p" . $pi;
	}
	my $rt = "virtual "
			. getMethodParamDeclarationSource( $classname, $retval) . " "
			. $methodname . "( "
			. $paramlist . ")";
	if ($isconst)
	{
		$rt .= " const";
	}
	return $rt;
}

sub packParameter
{
	my ($type, $id) = @_;
	my $rt = "";
	if ($type =~ m/(.*)Interface$/)
	{
		$rt .= "const $1" . "Impl* impl_$id = dynamic_cast<const $1" . "Impl*>($id);";
		$rt .= "\n\tif (!impl_$id) throw std::runtime_error( \"passing non RPC interface object in RPC call\");";
		$rt .= "\n\tmsg.packObject( impl_" . $id . "->classId(), impl_" . $id . "->objId());";
	}
	elsif ($type eq "ArithmeticVariant")
	{
		$rt .= "msg.packArithmeticVariant( " . $id . ");";
	}
	elsif ($type eq "Index")
	{
		$rt .= "msg.packIndex( " . $id . ");";
	}
	elsif ($type eq "GlobalCounter")
	{
		$rt .= "msg.packGlobalCounter( " . $id . ");";
	}
	elsif ($type eq "int")
	{
		$rt .= "msg.packInt( " . $id . ");";
	}
	elsif ($type eq "unsigned int")
	{
		$rt .= "msg.packUint( " . $id . ");";
	}
	elsif ($type eq "float")
	{
		$rt .= "msg.packFloat( " . $id . ");";
	}
	elsif ($type eq "bool")
	{
		$rt .= "msg.packBool( " . $id . ");";
	}
	elsif ($type eq "std::size_t")
	{
		$rt .= "msg.packSize( " . $id . ");";
	}
	elsif ($type eq "char*")
	{
		$rt .= "msg.packCharp( " . $id . ");";
	}
	elsif ($type eq "std::string")
	{
		$rt .= "msg.packString( " . $id . ");";
	}

#	PACK_UNKNOWN( "DatabaseOptions");
#	PACK_UNKNOWN( "DatabaseInterface::ConfigType");
#	PACK_UNKNOWN( "StorageInterface::ConfigType");
#	PACK_UNKNOWN( "TokenizerConfig");
#	PACK_UNKNOWN( "NormalizerConfig");
#	PACK_UNKNOWN( "DocumentAnalyzerInterface::FeatureOptions");
#	PACK_UNKNOWN( "Reference<PostingIteratorInterface>");
#	PACK_UNKNOWN( "SummarizerConfig");
#	PACK_UNKNOWN( "WeightingConfig");
#	PACK_UNKNOWN( "QueryInterface::CompareOperator");
#	PACK_UNKNOWN( "SummarizerFunctionInterface::FeatureParameter");

	else
	{
		$rt .= "PACK_UNKNOWN( \"$type\" $id);";
	}
	return $rt;
}

sub inputParameterPackFunctionCall
{
	my $rt = "";
	my ($classname, $param, $idx) = @_;
	my ($paramtype, $isconst, $isarray, $indirection, $passbyref) = getParamProperties( $classname, $param);
	if ($passbyref && ($isconst == 0 || $indirection > 0))
	{
		return "";
	}
	if ($indirection == 2)
	{
		$rt .= "\tfor (unsigned int ii=0; p$idx" . "[ii]; ++ii);\n";
		$rt .= "\tpackUint( ii);\n";
		$rt .= "\tfor (unsigned int ii=0; p$idx" . "[ii]; ++ii) {\n";
		$rt .= "\t\t" . packParameter( $paramtype, "p$idx" . "[ii]") . "\n\t}\n";
	}
	elsif ($isarray)
	{
		$rt .= "\tpackSize( p$idx" . ".size());\n";
		$rt .= "\tfor (unsigned int ii=0; ii < p$idx" . ".size(); ++ii) {\n";
		$rt .= "\t\t" . packParameter( $paramtype, "p$idx" . "[ii]") . "\n\t}\n";
	}
	elsif ($indirection == 1 && $paramtype eq 'char' && $passbyref == 0)
	{
		$rt .= "\t" . packParameter( "$paramtype*", "p$idx") . "\n";
	}
	else
	{
		$rt .= "\t" . packParameter( $paramtype, "p$idx") . "\n";
	}
	return $rt;
}

sub getMethodDeclarationSource
{
	my ($classname, $method) = @_;
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
		++$pi;
		$paramlist .= getMethodParamDeclarationSource( $classname, $pp) . " p" . $pi;
	}
	my $rt = getMethodParamDeclarationSource( $classname, $retval) . " "
			. $classname . "::" . $methodname . "( "
			. $paramlist . ")";
	if ($isconst)
	{
		$rt .= " const";
	}
	$rt .= "\n{\n\tRpcMessage msg;\n";
	$rt .= "\tmsg.packObject( classId(), objId());\n";
	$rt .= "\tmsg.packByte( Method_" . $methodname . ");\n";

	$pi = 0;
	for (; $pi <= $#param; ++$pi)
	{
		if ($pi+1 <= $#param && $param[$pi] eq "const^ char" && $param[$pi+1] eq "std::size_t")
		{
			# ... exception for buffer( size, len):
			$rt .= "\tmsg.packBuffer( p" . ($pi+1) . ", p" . ($pi+2) . ");\n";
			++$pi;
		}
		else
		{
			$rt .= inputParameterPackFunctionCall( $classname, $param[$pi], $pi+1);
		}
	}
	$rt .= "\tmsg.packCrc32();\n";
	$rt .= "}\n";
	return $rt;
}

sub getClassHeaderSource
{
	my $rt = "";
	my $ii = 0;
	
	foreach (@interfaceClasses)
	{
		my $interfacename = getInterfaceName($_);
		my $classname = interfaceImplementationClassName( $interfacename);
		$rt .= "\nclass $classname\n\t\t:public RpcInterfaceStub\n\t\t,public strus::$interfacename\n{\npublic:";

		my @mth = split('%');
		shift( @mth);
		my $mm;
		my $mi = 0;
		$rt .= "\n\tenum MethodId\n\t{";
		foreach $mm( @mth)
		{
			my $callname = getMethodName( $mm);
			if ($mi++ > 0)
			{
				$rt .= ",\n\t\t";
			}
			else
			{
				$rt .= "\n\t\t";
			}
			$rt .= "Method_" . $callname;
		}
		$rt .= "\n\t};\n";
		$rt .= "\n\tvirtual ~$classname(){}\n";
		$rt .= "\n\t$classname( const RpcRemoteEndPoint* endpoint_)\n\t\t:RpcInterfaceStub( (unsigned char)" . getInterfaceEnumName($interfacename) .", endpoint_){}\n";
		foreach $mm( @mth)
		{
			$rt .= "\n\t" . getMethodDeclarationHeader( $classname, $mm) .";";
		}
		$rt .= "\n};\n";
		++$ii;
	}
	$rt .= "\n};\n";
	return $rt;
}

sub getClassImplementationSource
{
	my $rt = "";
	my $ii = 0;
	
	foreach (@interfaceClasses)
	{
		my $interfacename = getInterfaceName($_);
		my $classname = interfaceImplementationClassName( $interfacename);

		my @mth = split('%');
		shift( @mth);
		my $mm;
		my $mi = 0;
		foreach $mm( @mth)
		{
			$rt .= "\n" . getMethodDeclarationSource( $classname, $mm);
		}
		++$ii;
	}
	return $rt;
}


my $interfacefile = "src/rpcObjects.hpp";
open( HDRFILE, ">$interfacefile") or die "Couldn't open file $interfacefile, $!";

print HDRFILE <<EOF;
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
#include "rpcInterfaceStub.hpp"
EOF
foreach $inputfile( @inputfiles)
{
	if ($inputfile =~ m/[\/]([a-zA-z0-9_]+[\.]hpp)$/)
	{
		print HDRFILE "#include \"strus/" . $1 ."\"\n";
	}
	else
	{
		die "input file has unknown name pattern: $inputfile";
	}
}
print HDRFILE "\n";
print HDRFILE "namespace strus {\n";

print HDRFILE getClassEnumSource();
print HDRFILE getClassHeaderSource();

print HDRFILE <<EOF;
} //namespace
#endif
EOF
close HDRFILE;

my $sourcefile = "src/rpcObjects.cpp";
open( SRCFILE, ">$sourcefile") or die "Couldn't open file $sourcefile, $!";

print SRCFILE <<EOF;
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
#include "rpcObjects.hpp"

using namespace strus;
EOF

print SRCFILE getClassImplementationSource();

print SRCFILE <<EOF;

EOF
close SRCFILE;

#printParsedDump();

