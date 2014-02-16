
#set methods = $current_class.methods_clean()

void csx_register_${current_class.class_name}()
{
	#for m in methods
	#set fn = m['impl']
	csxBindingObject::registerFunction("${current_class.class_name}","${m['name']}", &${fn.signature_name});
	#end for
}
