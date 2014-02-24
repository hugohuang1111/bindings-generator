
## ----- Generate Hashed IDs for cocos2d-x classes
#for csxclass in $sorted_classes
	#if $in_listed_classes(csxclass)
\#define	k${csxclass} = HASH("${csxclass}")
	#end if
#end for

\#endif