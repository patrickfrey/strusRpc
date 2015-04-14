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
$typeRewriteMap{"const_PostingIteratorInterface*"} = "const PostingIteratorInterface*";

my %syncMethods = ();
$syncMethods{"done"} = 1;
$syncMethods{"commit"} = 1;

my %notImplMethods = ();
$notImplMethods{"checkStorage"} = 1;           # ...ostream reference input cannot be handled
$notImplMethods{"getPostingJoinOperator"} = 1; # ...const Object return can not be handled
$notImplMethods{"getSummarizerFunction"} = 1;  # ...const Object return can not be handled
$notImplMethods{"getWeightingFunction"} = 1;   # ...const Object return can not be handled
$notImplMethods{"subExpressions"} = 1;         # ...vector of const Object return can not be handled
$notImplMethods{"getNormalizer"} = 1;          # ...const Object return can not be handled
$notImplMethods{"getTokenizer"} = 1;           # ...const Object return can not be handled
$notImplMethods{"getTextProcessor"} = 1;       # ...const Object return can not be handled
$notImplMethods{"getStorage"} = 1;             # ...const Object return can not be handled
$notImplMethods{"getQueryProcessor"} = 1;      # ...const Object return can not be handled
$notImplMethods{"getDatabase"} = 1;            # ...const Object return can not be handled

my %passOwnershipParams = ();
$passOwnershipParams{"definePostingJoinOperator"} = 1;
$passOwnershipParams{"defineWeightingFunction"} = 1;
$passOwnershipParams{"defineSummarizerFunction"} = 1;
$passOwnershipParams{"createClient"} = 1;
$passOwnershipParams{"createAlterMetaDataTable"} = 1;

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
			if ($tok eq "unsigned" || $tok eq "const")
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
	my $passbyref = 0;
	if ($param =~ m/^[\&]/)
	{
		$passbyref = 1;
		$param =~ s/^[\&]//;
	}
	$param =~ s/^[ ][ ]*//g;
	my $isreference = 0;
	if ($param =~ m/^Reference[ ]+/)
	{
		$isreference = 1;
		$param =~ s/^Reference[ ]+//;
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
	return ($paramname, $isconst, $isarray, $indirection, $passbyref, $isreference);
}

sub getVariableTypeSource
{
	my ($paramname, $isconst, $isarray, $indirection, $passbyref, $isreference) = @_;
	if ($isreference)
	{
		$paramname = "Reference<" . $paramname . ">";
	}
	if ($isarray)
	{
		$paramname = "std::vector<" . $paramname . ">";
	}
	$paramname =~ s/[\>][\>]/> >/g;
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
	return "$paramname";
}

sub getMethodParamDeclarationSource
{
	my ($classname, $param) = @_;
	my ($paramname, $isconst, $isarray, $indirection, $passbyref, $isreference) = getParamProperties( $classname, $param);
	return getVariableTypeSource( $paramname, $isconst, $isarray, $indirection, $passbyref, $isreference);
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
	my ($type, $id, $isconst, $indirection, $serverSide) = @_;
	my $rt = "";
	if ($type =~ m/(.*)Interface$/)
	{
		my $objtype = $1;
		my $idx = $id;
		$idx =~ s/[^0-9]//g;
		if ($serverSide)
		{
			$rt .= "\tunsigned char classId_$idx = (unsigned char)ClassId_$objtype;\n";
			$rt .= "\tunsigned int objId_$idx = createObject( classId_$idx, $id);\n";
			$rt .= "\tmsg.packObject( classId_$idx, objId_$idx);";
		}
		else
		{
			$rt .= "\tconst RpcInterfaceStub* impl_$idx = dynamic_cast<const RpcInterfaceStub*>($id);\n";
			$rt .= "\tif (!impl_$idx) throw std::runtime_error( \"passing non RPC interface object in RPC call\");\n";
			$rt .= "\tmsg.packObject( impl_" . $idx . "->classId(), impl_" . $idx . "->objId());";
		}
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
	elsif ($type eq "char")
	{
		if ($indirection == 2)
		{
			$rt .= "msg.packCharpp( " . $id . ");";
		}
		elsif ($indirection == 1)
		{
			$rt .= "msg.packCharp( " . $id . ");";
		}
		elsif ($indirection == 0)
		{
			$rt .= "msg.packByte( " . $id . ");";
		}
		else
		{
			$rt .= "PACK_UNKNOWN( \"$type\" $id);";
		}
	}
	elsif ($type eq "std::string")
	{
		$rt .= "msg.packString( " . $id . ");";
	}
	elsif ($type eq "DatabaseOptions")
	{
		$rt .= "msg.packDatabaseOptions( " . $id . ");";
	}
	elsif ($type eq "DatabaseInterface::ConfigType")
	{
		$rt .= "msg.packDatabaseConfigType( " . $id . ");";
	}
	elsif ($type eq "StorageInterface::ConfigType")
	{
		$rt .= "msg.packStorageConfigType( " . $id . ");";
	}
	elsif ($type eq "TokenizerConfig")
	{
		$rt .= "msg.packTokenizerConfig( " . $id . ");";
	}
	elsif ($type eq "NormalizerConfig")
	{
		$rt .= "msg.packNormalizerConfig( " . $id . ");";
	}
	elsif ($type eq "SegmenterPosition")
	{
		$rt .= "msg.packGlobalCounter( " . $id . ");";
	}
	elsif ($type eq "DocumentAnalyzerInterface::FeatureOptions")
	{
		$rt .= "msg.packFeatureOptions( " . $id . ");";
	}
	elsif ($type eq "SummarizerConfig")
	{
		$rt .= "msg.packSummarizerConfig( " . $id . ");";
	}
	elsif ($type eq "WeightingConfig")
	{
		$rt .= "msg.packWeightingConfig( " . $id . ");";
	}
	elsif ($type eq "QueryInterface::CompareOperator")
	{
		$rt .= "msg.packCompareOperator( " . $id . ");";
	}
	elsif ($type eq "SummarizerFunctionInterface::FeatureParameter")
	{
		$rt .= "msg.packFeatureParameter( " . $id . ");";
	}
	elsif ($type eq "SummarizerClosureInterface::SummaryElement")
	{
		$rt .= "msg.packSummaryElement( " . $id . ");";
	}
	elsif ($type eq "DatabaseCursorInterface::Slice")
	{
		$rt .= "msg.packSlice( " . $id . ");";
	}
	elsif ($type eq "analyzer::Document")
	{
		$rt .= "msg.packAnalyzerDocument( " . $id . ");";
	}
	elsif ($type eq "analyzer::Attribute")
	{
		$rt .= "msg.packAnalyzerAttribute( " . $id . ");";
	}
	elsif ($type eq "analyzer::MetaData")
	{
		$rt .= "msg.packAnalyzerMetaData( " . $id . ");";
	}
	elsif ($type eq "analyzer::Term")
	{
		$rt .= "msg.packAnalyzerTerm( " . $id . ");";
	}
	elsif ($type eq "analyzer::Token")
	{
		$rt .= "msg.packAnalyzerToken( " . $id . ");";
	}
	elsif ($type eq "WeightedDocument")
	{
		$rt .= "msg.packWeightedDocument( " . $id . ");";
	}
	elsif ($type eq "ResultDocument")
	{
		$rt .= "msg.packResultDocument( " . $id . ");";
	}
	else
	{
		$rt .= "PACK_UNKNOWN( \"$type\" $id);";
	}
	return $rt;
}

sub unpackParameter
{
	my ($type, $id, $isconst, $indirection, $serverSide) = @_;
	my $idx = $id;
	$idx =~ s/[^0-9]//g;
	my $rt = "";
	if ($type =~ m/(.*)Interface$/)
	{
		$rt .= "unsigned char classId_$idx; unsigned int objId_$idx;\n";
		$rt .= "\tserializedMsg.unpackObject( classId_$idx, objId_$idx);\n";
		$rt .= "\tif (classId_$idx != " . getInterfaceEnumName( $type) .") throw std::runtime_error(\"error in RPC serialzed message: output parameter object type mismatch\");\n";
		if ($serverSide)
		{
			$rt .= "\t$id = getObject<$type>( classId_$idx, objId_$idx);";
		}
		else
		{
			my $implname = interfaceImplementationClassName( $type);
			$rt .= "\t$id = new $implname( objId_$idx, messaging());";
		}
	}
	elsif ($type eq "ArithmeticVariant")
	{
		$rt .= "$id = serializedMsg.unpackArithmeticVariant();";
	}
	elsif ($type eq "Index")
	{
		$rt .= "$id = serializedMsg.unpackIndex();";
	}
	elsif ($type eq "GlobalCounter")
	{
		$rt .= "$id = serializedMsg.unpackGlobalCounter();";
	}
	elsif ($type eq "int")
	{
		$rt .= "$id = serializedMsg.unpackInt();";
	}
	elsif ($type eq "unsigned int")
	{
		$rt .= "$id = serializedMsg.unpackUint();";
	}
	elsif ($type eq "float")
	{
		$rt .= "$id = serializedMsg.unpackFloat();";
	}
	elsif ($type eq "bool")
	{
		$rt .= "$id = serializedMsg.unpackBool();";
	}
	elsif ($type eq "std::size_t")
	{
		$rt .= "$id = serializedMsg.unpackSize();";
	}
	elsif ($type eq "char")
	{
		if ($indirection == 1)
		{
			if ($isconst)
			{
				if ($serverSide)
				{
					$rt .= "$id = serializedMsg.unpackConstCharp();";
				}
				else
				{
					$rt .= "$id = constConstructor()->getCharp( serializedMsg.unpackConstCharp());";
				}
			}
			else
			{
				$rt .= "UNPACK_UNKNOWN( \"$type\" $id);";
			}
		}
		elsif ($indirection == 2)
		{
			if ($isconst)
			{
				$rt .= "$id = constConstructor()->getCharpp( serializedMsg.unpackConstCharpp());";
			}
			else
			{
				$rt .= "UNPACK_UNKNOWN( \"$type\" $id);";
			}
		}
		elsif ($indirection == 0)
		{
			$rt .= "$id = serializedMsg.unpackByte();";
		}
		else
		{
			$rt .= "PACK_UNKNOWN( \"$type\" $id);";
		}
	}
	elsif ($type eq "std::string")
	{
		$rt .= "$id = serializedMsg.unpackString();";
	}
	elsif ($type eq "DatabaseOptions")
	{
		$rt .= "$id = serializedMsg.unpackDatabaseOptions();";
	}
	elsif ($type eq "DatabaseInterface::ConfigType")
	{
		$rt .= "$id = serializedMsg.unpackDatabaseConfigType();";
	}
	elsif ($type eq "StorageInterface::ConfigType")
	{
		$rt .= "$id = serializedMsg.unpackStorageConfigType();";
	}
	elsif ($type eq "TokenizerConfig")
	{
		$rt .= "$id = serializedMsg.unpackTokenizerConfig();";
	}
	elsif ($type eq "NormalizerConfig")
	{
		$rt .= "$id = serializedMsg.unpackNormalizerConfig();";
	}
	elsif ($type eq "SegmenterPosition")
	{
		$rt .= "$id = serializedMsg.unpackGlobalCounter();";
	}
	elsif ($type eq "DocumentAnalyzerInterface::FeatureOptions")
	{
		$rt .= "$id = serializedMsg.unpackFeatureOptions();";
	}
	elsif ($type eq "SummarizerConfig")
	{
		$rt .= "$id = serializedMsg.unpackSummarizerConfig();";
	}
	elsif ($type eq "WeightingConfig")
	{
		$rt .= "$id = serializedMsg.unpackWeightingConfig();";
	}
	elsif ($type eq "QueryInterface::CompareOperator")
	{
		$rt .= "$id = serializedMsg.unpackCompareOperator();";
	}
	elsif ($type eq "SummarizerFunctionInterface::FeatureParameter")
	{
		if ($serverSide)
		{
			$rt .= "\tunsigned int featclass_$idx = serializedMsg.unpackUint();\n";
			$rt .= "\tunsigned char piclassId_$idx; unsigned int piobjId_$idx;\n";
			$rt .= "\tserializedMsg.unpackObject( piclassId_$idx, piobjId_$idx);\n";
			$rt .= "\tPostingIteratorInterface* pos_$idx = getObject<PostingIteratorInterface>( piclassId_$idx, piobjId_$idx);\n";
			$rt .= "\tstd::size_t vi_$idx=0,ve_$idx = serializedMsg.unpackSize();\n";
			$rt .= "\tstd::vector<SummarizationVariable> vars_$idx;\n";
			$rt .= "\tfor (; vi_$idx != ve_$idx; ++vi_$idx)\n";
			$rt .= "\t{\n";
			$rt .= "\t\tstd::string varname = serializedMsg.unpackString();\n";
			$rt .= "\tunsigned char viclassId_$idx; unsigned int viobjId_$idx;\n";
			$rt .= "\tserializedMsg.unpackObject( viclassId_$idx, viobjId_$idx);\n";
			$rt .= "\t\tPostingIteratorInterface* varpos = getObject<PostingIteratorInterface>( viclassId_$idx, viobjId_$idx);\n";
			$rt .= "\t\tvars_$idx.push_back( SummarizationVariable( varname, varpos));\n";
			$rt .= "\t}\n";
			$rt .= "\t$id = SummarizerFunctionInterface::FeatureParameter( featclass_$idx, SummarizationFeature( pos_$idx, vars_$idx));\n";
		}
		else
		{
			$rt .= "UNPACK_UNKNOWN( \"$type\" $id);";
		}
	}
	elsif ($type eq "SummarizerClosureInterface::SummaryElement")
	{
		$rt .= "$id = serializedMsg.unpackSummaryElement();";
	}
	elsif ($type eq "DatabaseCursorInterface::Slice")
	{
		if ($serverSide)
		{
			$rt .= "$id = serializedMsg.unpackSlice();";
		}
		else
		{
			$rt .= "DatabaseCursorInterface::Slice slice$idx = serializedMsg.unpackSlice();\n";
			$rt .= "\t$id = DatabaseCursorInterface::Slice( (const char*)constConstructor()->get( slice$idx" . ".ptr(), slice$idx" . ".size()), slice$idx" . ".size());";
		}
	}
	elsif ($type eq "analyzer::Document")
	{
		$rt .= "$id = serializedMsg.unpackAnalyzerDocument();";
	}
	elsif ($type eq "analyzer::Attribute")
	{
		$rt .= "$id = serializedMsg.unpackAnalyzerAttribute();";
	}
	elsif ($type eq "analyzer::MetaData")
	{
		$rt .= "$id = serializedMsg.unpackAnalyzerMetaData();";
	}
	elsif ($type eq "analyzer::Token")
	{
		$rt .= "$id = serializedMsg.unpackAnalyzerToken();";
	}
	elsif ($type eq "analyzer::Term")
	{
		$rt .= "$id = serializedMsg.unpackAnalyzerTerm();";
	}
	elsif ($type eq "WeightedDocument")
	{
		$rt .= "$id = serializedMsg.unpackWeightedDocument();";
	}
	elsif ($type eq "ResultDocument")
	{
		$rt .= "$id = serializedMsg.unpackResultDocument();";
	}
	else
	{
		$rt .= "UNPACK_UNKNOWN( \"$type\" $id);";
	}
	return $rt;
}

sub inputParameterPackFunctionCall
{
	my ($sender_code,$receiver_code) = ("","");
	my ($classname, $param, $idx) = @_;
	my ($paramtype, $isconst, $isarray, $indirection, $passbyref, $isreference) = getParamProperties( $classname, $param);
	if ($passbyref && ($isconst == 0 || $indirection > 0))
	{
		return ("","");
	}
	elsif ($isarray)
	{
		$sender_code .= "\tmsg.packSize( p$idx" . ".size());\n";
		$sender_code .= "\tfor (unsigned int ii=0; ii < p$idx" . ".size(); ++ii) {\n";
		if ($isreference)
		{
			$sender_code .= "\t\t" . packParameter( $paramtype, "p$idx" . "[ii].get()", $isconst, $indirection+1, 0) . "\n";
		}
		else
		{
			$sender_code .= "\t\t" . packParameter( $paramtype, "p$idx" . "[ii]", $isconst, $indirection, 0) . "\n";
		}
		$sender_code .= "\t}\n";

		$receiver_code .= "\tstd::size_t n$idx = serializedMsg.unpackSize();\n";
		$receiver_code .= "\tfor (std::size_t ii=0; ii < n$idx; ++ii) {\n";
		my $indirection_prefix = "";
		my $ii;
		for ($ii=0; $ii<$indirection; ++$ii)
		{
			$indirection_prefix .= "*";
		}
		if ($isreference)
		{
			$indirection_prefix .= "*";
		}
		$receiver_code .= "\t\t" . unpackParameter( $paramtype, "$paramtype$indirection_prefix ee", $isconst, $indirection, 1) . "\n";
		$receiver_code .= "\t\tp$idx" . ".push_back( ee);\n";
		$receiver_code .= "\t}\n";
	}
	else
	{
		if ($isreference)
		{
			$sender_code .= "\t" . packParameter( $paramtype, "p$idx.get()", $isconst, $indirection, 0) . "\n";

			$receiver_code .= "\t" . unpackParameter( $paramtype, "$paramtype* e$idx", $isconst, $indirection+1, 1) . "\n";
			$receiver_code .= "p$idx = Reference<$paramtype>( e$idx);\n";
		}
		else
		{
			$sender_code .= "\t" . packParameter( $paramtype, "p$idx", $isconst, $indirection, 0) . "\n";
			$receiver_code .= "\t" . unpackParameter( $paramtype, "p$idx", $isconst, $indirection, 1) . "\n";
		}
	}
	return ($sender_code,$receiver_code);
}

sub outputParameterPackFunctionCall
{
	my ($sender_code,$receiver_code) = ("","");
	my ($classname, $param, $idx) = @_;
	my ($paramtype, $isconst, $isarray, $indirection, $passbyref, $isreference) = getParamProperties( $classname, $param);
	if ($passbyref)
	{
		if ($isconst)
		{
		}
		elsif ($isarray)
		{
			$sender_code .= "\tstd::size_t n$idx = serializedMsg.unpackSize();\n";
			$sender_code .= "\tfor (unsigned int ii=0; ii < n$idx; ++ii) {\n";
			$sender_code .= "\t\t" . unpackParameter( $paramtype, "$paramtype elem_p$idx", $isconst, $indirection+1, 0) . ";\n";
			$sender_code .= "\t\tp$idx.push_back( elem_p$idx);\n";
			$sender_code .= "\n\t}\n";

			$receiver_code .= "\tmsg.packSize( p$idx" . ".size());\n";
			$receiver_code .= "\tfor (unsigned int ii=0; ii < p$idx" . ".size(); ++ii) {\n";
			if ($isreference)
			{
				$receiver_code .= "\t\t" . packParameter( $paramtype, "p$idx" . "[ii].get()", $isconst, $indirection+1, 1) . "\n\t}\n";
			}
			else
			{
				$receiver_code .= "\t\t" . packParameter( $paramtype, "p$idx" . "[ii]", $isconst, $indirection, 1) . "\n\t}\n";
			}
		}
		else
		{
			$sender_code .= "\t" . unpackParameter( $paramtype, "p$idx", $isconst, $indirection, 0) . "\n";

			$receiver_code .= "\t" . packParameter( $paramtype, "p$idx", $isconst, $indirection, 1) . "\n";
		}
	}
	return ($sender_code,$receiver_code);
}

sub getMethodDeclarationSource
{
	my ($sender_code,$receiver_code) = ("","");
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
	$sender_code = getMethodParamDeclarationSource( $classname, $retval) . " "
			. $classname . "::" . $methodname . "( "
			. $paramlist . ")";
	if ($isconst)
	{
		$sender_code .= " const";
	}
	$sender_code .= "\n{\n";
	$receiver_code .= "RpcSerializer msg;\n";

	if ($notImplMethods{$methodname})
	{
		$sender_code .= "\tthrow std::runtime_error(\"the method '$methodname' is not implemented for RPC\");\n";

		$receiver_code .= "\tmsg.packByte( MsgTypeException_RuntimeError);\n";
		$receiver_code .= "\tmsg.packString( \"the method '$methodname' is not implemented for RPC\");\n";
		$receiver_code .= "\treturn msg.content();\n";
	}
	else
	{
		$sender_code .= "\tRpcSerializer msg;\n";
		$sender_code .= "\tmsg.packObject( classId(), objId());\n";
		$sender_code .= "\tmsg.packByte( Method_" . $methodname . ");\n";

		my $retvalassigner = "";
		if ($retval ne "void")
		{
			my $retvaltype_decl = getMethodParamDeclarationSource( $classname, $retval);
			$receiver_code .= "\t$retvaltype_decl p0;\n";
			$retvalassigner = "p0 = ";
		}
		my $receiver_paramlist = "";
		for ($pi = 0; $pi <= $#param; ++$pi)
		{
			my ($paramtype, $isconst, $isarray, $indirection, $passbyref, $isreference) = getParamProperties( $classname, $param[ $pi]);
			if ($passbyref && $isconst && $indirection == 0)
			{
				$isconst = 0;
			}
			my $paramtype_decl = getVariableTypeSource($paramtype, $isconst, $isarray, $indirection, 0, $isreference);
			$receiver_code .= "\t$paramtype_decl p" . ($pi+1) . ";\n";
			if ($receiver_paramlist ne "")
			{
				$receiver_paramlist .= ",";
			}
			$receiver_paramlist .= "p" . ($pi+1);
		}

		for ($pi = 0; $pi <= $#param; ++$pi)
		{
			if ($pi+1 <= $#param && $param[$pi] eq "const^ char" && $param[$pi+1] eq "std::size_t")
			{
				# ... exception for buffer( size, len):
				$sender_code .= "\tmsg.packBuffer( p" . ($pi+1) . ", p" . ($pi+2) . ");\n";
				$receiver_code .= "\tserializedMsg.unpackBuffer( p" . ($pi+1) . ", p" . ($pi+2) . ");\n";
				++$pi;
			}
			else
			{
				my ($snd,$rcv) = inputParameterPackFunctionCall( $classname, $param[$pi], $pi+1);
				$sender_code .= $snd;
				$receiver_code .= $rcv;
			}
		}
		$sender_code .= "\tmsg.packCrc32();\n";
		$sender_code .= "\trpc_send( msg.content());\n";
		$receiver_code .= "\ttry {\n";
		$receiver_code .= "\t\t$retvalassigner" . "obj->" . $methodname . "(" . $receiver_paramlist . ");\n";
		if ($passOwnershipParams{$methodname})
		{
			for ($pi = 0; $pi <= $#param; ++$pi)
			{
				if ($param[$pi] =~ m/Interface$/)
				{
					$receiver_code .= "\t\treleaseObject( classId_" . ($pi+1) . ", objId_" . ($pi+1) . ");\n";
				}
			}
		}
		$receiver_code .= "\t\tmsg.packByte( MsgTypeAnswer);\n";
		$receiver_code .= "\t} catch (const std::runtime_error& err) {\n";
		$receiver_code .= "\t\tmsg.packByte( MsgTypeException_RuntimeError);\n";
		$receiver_code .= "\t\tmsg.packString( err.what());\n";
		$receiver_code .= "\t\treturn msg.content();\n";
		$receiver_code .= "\t} catch (const std::bad_alloc& err) {\n";
		$receiver_code .= "\t\tmsg.packByte( MsgTypeException_BadAlloc);\n";
		$receiver_code .= "\t\tmsg.packString( \"memory allocation error\");\n";
		$receiver_code .= "\t\treturn msg.content();\n";
		$receiver_code .= "\t} catch (const std::logic_error& err) {\n";
		$receiver_code .= "\t\tmsg.packByte( MsgTypeException_LogicError);\n";
		$receiver_code .= "\t\tmsg.packString( err.what());\n";
		$receiver_code .= "\t\treturn msg.content();\n";
		$receiver_code .= "\t}\n";

		my ($sender_output,$receiver_output) = ("","");
		if ($retval ne "void")
		{
			my ($retvaltype, $isconst, $isarray, $indirection, $passbyref, $isreference) = getParamProperties( $classname, $retval);
			if ($retvaltype =~ m/Interface$/)
			{
				if ($indirection == 1)
				{
					$sender_output .= "\t" . unpackParameter( $retvaltype, "$retvaltype* p0", 0, $indirection, 0) . "\n";
					$receiver_output .= packParameter( $retvaltype, "p0", 0, $indirection, 1) . "\n";
				}
				else
				{
					$sender_output .= "UNKNOWN RETURN VALUE TYPE\n";
					$receiver_output .= "UNKNOWN RETURN VALUE TYPE\n";
				}
			}
			elsif ($isarray)
			{
				$sender_output .= "\tstd::vector<$retvaltype> p0;\n";
				$sender_output .= "\tstd::size_t n0 = serializedMsg.unpackSize();\n";
				$sender_output .= "\tfor (std::size_t ii=0; ii < n0; ++ii) {\n";
				$sender_output .= "\t\t" . unpackParameter( $retvaltype, "$retvaltype elem_p0", $isconst, $indirection, 0) . "\n";
				$sender_output .= "\t\tp0.push_back( elem_p0);\n";
				$sender_output .= "\t}\n";

				$receiver_output .= "\tmsg.packSize( p0.size());\n";
				$receiver_output .= "\tfor (std::size_t ii=0; ii < p0.size(); ++ii) {\n";
				$receiver_output .= "\t\t" . packParameter( $retvaltype, "p0[ii]", $isconst, $indirection, 1) . "\n";
				$receiver_output .= "\t}\n";

				$retvaltype = "std::vector<$retvaltype>";
			}
			else
			{
				my $retvaltype_decl = getVariableTypeSource($retvaltype, $isconst, $isarray, $indirection, 0, $isreference);
				$sender_output .= "\t" . unpackParameter( $retvaltype, "$retvaltype_decl p0", $isconst, $indirection, 0) . ";\n";
				$receiver_output .= "\t" . packParameter( $retvaltype, "p0", $isconst, $indirection, 1) . "\n";
			}
		}
		$pi = 0;
		for (; $pi <= $#param; ++$pi)
		{
			if ($pi+1 <= $#param && $param[$pi] eq "const^& char" && $param[$pi+1] eq "& std::size_t")
			{
				# ... exception for buffer( size, len):
				my $bpvar = "bp" . ($pi+1);
				$sender_output .= "\tconst char* $bpvar;\n";
				$sender_output .= "\tserializedMsg.unpackBuffer( $bpvar, p" . ($pi+2) . ");\n";
				$sender_output .= "\tp" . ($pi+1) . " = (const char*)constConstructor()->get( $bpvar, p" . ($pi+2) .");\n";

				$receiver_output .= "\tmsg.packBuffer( p" . ($pi+1) . ", p" . ($pi+2) . ");\n";
				++$pi;
			}
			else
			{
				my ($snd,$rcv) = outputParameterPackFunctionCall( $classname, $param[$pi], $pi+1);
				$sender_output .= $snd;
				$receiver_output .= $rcv;
			}
		}
		if ($sender_output ne "")
		{
			$sender_code .= "\tenter();\n";
			$sender_code .= "\tRpcDeserializer serializedMsg( rpc_recv());\n";
			$sender_code .= "\tserializedMsg.unpackByte();\n";
			$sender_code .= $sender_output;
			$receiver_code .= $receiver_output;
		}
		elsif ($syncMethods{$methodname})
		{
			$sender_code .= "\trpc_waitAnswer();\n";
		}
		if ($retval ne "void")
		{
			$sender_code .= "\treturn p0;\n";
		}
		$receiver_code .= "\tmsg.packCrc32();\n";
		$receiver_code .= "\treturn msg.content();\n";
	}
	$sender_code .= "}\n";
	return ($sender_code,$receiver_code);
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
		$rt .= "\n\tenum MethodId\n\t{";
		$rt .= "\n\t\tMethod_Destructor";
		foreach $mm( @mth)
		{
			my $callname = getMethodName( $mm);
			$rt .= ",\n\t\tMethod_" . $callname;
		}
		$rt .= "\n\t};\n";
		$rt .= "\n\tvirtual ~$classname();\n";
		$rt .= "\n\t$classname( unsigned int objId_, RpcMessagingInterface* messaging_)\n\t\t:RpcInterfaceStub( (unsigned char)" . getInterfaceEnumName($interfacename) .", objId_, messaging_){}\n";
		foreach $mm( @mth)
		{
			$rt .= "\n\t" . getMethodDeclarationHeader( $classname, $mm) .";";
		}
		$rt .= "\n};\n";
		++$ii;
	}
	return $rt;
}

sub getClassImplementationSource
{
	my ($sender_code,$receiver_code) = ("","");
	my $ii = 0;

	$receiver_code .= "\tRpcDeserializer serializedMsg( msg);\n";
	$receiver_code .= "\tif (!serializedMsg.unpackCrc32()) throw std::runtime_error(\"message CRC32 check failed\");\n";
	$receiver_code .= "\tunsigned char classId; unsigned int objId; unsigned char methodId;\n";
	$receiver_code .= "\tserializedMsg.unpackObject( classId, objId);\n";
	$receiver_code .= "\tmethodId = serializedMsg.unpackByte();\n";
	$receiver_code .= "\tswitch( (ClassId)classId)\n";
	$receiver_code .= "\t{\n";

	foreach (@interfaceClasses)
	{
		my $interfacename = getInterfaceName($_);
		my $classname = interfaceImplementationClassName( $interfacename);

		$sender_code .= "\n$classname" . "::~$classname()\n";
		$sender_code .= "{\n";
		$sender_code .= "\tRpcSerializer msg;\n";
		$sender_code .= "\tmsg.packObject( classId(), objId());\n";
		$sender_code .= "\tmsg.packByte( Method_Destructor);\n";
		$sender_code .= "\tmsg.packCrc32();\n";
		$sender_code .= "\trpc_send( msg.content());\n";
		$sender_code .= "}\n";

		$receiver_code .= "\tcase " . getInterfaceEnumName( $interfacename) . ":\n";
		$receiver_code .= "\t{\n";
		$receiver_code .= "\t$interfacename* obj = getObject<$interfacename>( classId, objId);\n";
		$receiver_code .= "\tswitch( ($classname" . "::MethodId)methodId)\n";
		$receiver_code .= "\t{\n";
		$receiver_code .= "\t\tcase $classname" . "::Method_Destructor:\n";
		$receiver_code .= "\t\t{\n";
		$receiver_code .= "\t\t\tdeleteObject( classId, objId);\n";
		$receiver_code .= "\t\t}\n";
		my @mth = split('%');
		shift( @mth);
		my $mm;
		my $mi = 0;
		foreach $mm( @mth)
		{
			my ($snd,$rcv) = getMethodDeclarationSource( $classname, $mm);
			$sender_code .= "\n" . $snd;

			my @param = split( '!', $mm);
			my $methodname = shift( @param);
			$methodname =~ s/^const //;
			$receiver_code .= "\t\tcase $classname" . "::Method_" . $methodname . ":\n";
			$receiver_code .= "\t\t{\n";
			$rcv =~ s/\n$//;
			$rcv =~ s/\n/\n\t\t/g;
			$receiver_code .= "\t\t\t$rcv\n";
			$receiver_code .= "\t\t\tbreak;\n";
			$receiver_code .= "\t\t}\n";
		}
		++$ii;
		$receiver_code .= "\t}\n";
		$receiver_code .= "\tbreak;\n";
		$receiver_code .= "\t}\n";
	}
	$receiver_code .= "\t}\n";
	$receiver_code .= "\treturn serializedMsg.content();\n";
	return ($sender_code,$receiver_code);
}


my $interfacefile = "src/serialize/rpcObjects.hpp";
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

my $sourcefile = "src/serialize/rpcObjects.cpp";
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
#include "rpcSerializer.hpp"

using namespace strus;
EOF

my ($sender_code,$receiver_code) = getClassImplementationSource();
print SRCFILE $sender_code;

print SRCFILE <<EOF;

EOF
close SRCFILE;


$sourcefile = "src/serialize/rpcRequestHandler.cpp";
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
#include "rpcRequestHandler.hpp"
#include "rpcSerializer.hpp"
#include "rpcObjects.hpp"
#include <string>

using namespace strus;
std::string RpcRequestHandler::handleRequest( const std::string& msg)
{
EOF

($sender_code,$receiver_code) = getClassImplementationSource();
print SRCFILE $receiver_code;

print SRCFILE <<EOF;
}
EOF
close SRCFILE;

#printParsedDump();

