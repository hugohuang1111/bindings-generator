
#set methods = $current_class.methods_clean()
#set st_methods = $current_class.static_methods_clean()
#set parents = $current_class.parents

void csx_register_${current_class.class_name}()
{
	#for m in methods
	#set fn = m['impl']
	Object::registerFunction("${current_class.class_name}", HASH("${current_class.class_name}"), "${m['name']}", &${fn.signature_name});
	#end for
	#for m in st_methods
	#set fn = m['impl']
	Object::registerFunction("${current_class.class_name}", HASH("${current_class.class_name}"), "${m['name']}", &${fn.signature_name});
	#end for
	#for p in parents
	Object::registerParent(HASH("${current_class.class_name}"), HASH("${p.class_name}"));
	#end for
}
