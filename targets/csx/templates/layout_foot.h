
## ----- Generate Hashed IDs for cocos2d-x classes
enum
{
#for csxclass in $sorted_classes
	#if $in_listed_classes(csxclass)
	kcc${csxclass} = HASH("${csxclass}"),
	#end if
#end for
};

## ----- End of namespace
}
\#endif