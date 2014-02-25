
void csx_register_all_${prefix}()
{
	#for csxclass in $sorted_classes
	#if $in_listed_classes(csxclass)
	csx_register_${csxclass}();
	#end if
	#end for
}

## ----- End of namespace
}
