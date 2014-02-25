
## ----- Generate Hashed IDs for cocos2d-x classes
enum
{
#for csxclass in $sorted_classes
	kcc${csxclass} = HASH("${csxclass}"),
#end for
};

## ----- End of namespace
}
\#endif