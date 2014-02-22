
#set methods = $current_class.methods_clean()
#set st_methods = $current_class.static_methods_clean()

void csx_register_${current_class.class_name}()
{
	#for m in methods
	#set fn = m['impl']
	BindingBase::registerFunction("${current_class.class_name}","${m['name']}", &${fn.signature_name});
	#end for
	#for m in st_methods
	#set fn = m['impl']
	BindingBase::registerFunction("${current_class.class_name}","${m['name']}", &${fn.signature_name});
	#end for
}
