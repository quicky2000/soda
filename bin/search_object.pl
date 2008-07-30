eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}' # -*-perl-*-
& eval 'exec perl -S $0 $argv:q'
if 0;

use strict;


#print "Nb args = $#ARGV\n";

if($#ARGV <0 || $#ARGV > 1 )
  {
    die("Usage is search_object.pl object_name [version]");
  }

if( $ENV{QUICKY_REPOSITORY} eq '')
  {
    die("QUICKY_REPOSITORY doesn`t exist");
  }
#print "Repository is located in $ENV{QUICKY_REPOSITORY}\n";

my @repository_paths = split(/:/,$ENV{QUICKY_REPOSITORY});
my $repository_path = "";
my $search_string = "";

if($#ARGV >=0)
  {
    $search_string = $ARGV[0];
  }
if($#ARGV ==1)
  {
    $search_string .= "/".$ARGV[1];
  }

#print "Search string : $search_string\n" ;
my $result = "unknown";
my $index = 0;
do
  {
    my $tmp_path = $repository_paths[$index]."/".$search_string;
    $tmp_path =~ s/\/\//\//g;
    #print "Testing $tmp_path\n";
    if( -d $tmp_path )
      {
	$result = $tmp_path;
      }
    $index++;
}while($result == "unknown" && $index <= $#repository_paths);

print "$result\n"
