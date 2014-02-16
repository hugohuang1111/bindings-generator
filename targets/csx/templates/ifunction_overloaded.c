
## ===== instance function implementation template
void ${signature_name}(CSXContext *cx)
{
#if not $is_constructor
	## ===== get the object from top of the stack
	$namespaced_class_name* obj = cx->top()->getValue<$namespaced_class_name*>();
	cx->pop();
#end if

	size_t argc = cx->size();
## ====== Generate function calls
#for func in $implementations
#if len($func.arguments) >= $func.min_args
	#set arg_count = len($func.arguments)
	#set arg_idx = $func.min_args
	#while $arg_idx <= $arg_count
	if(argc == ${arg_idx})
	{
		## ====== Populate parameters
		#set $count = 0;
		#while $count < $arg_idx
			#set $arg = $func.arguments[$count]
		${arg} arg${count} = cx->top()->getValue<$arg>();
		cx->pop();
			#set $count = $count + 1
		#end while
		## ===== generation agument list
		#set $count = 0
		#set arg_list = ""
		#set arg_array = []
		#while $count < $arg_idx
			#set $arg = $func.arguments[$count]
			#set $arg_array += ["arg"+str(count)]
			#set $count = $count + 1
		#end while
		#set $arg_list = ", ".join($arg_array)

		## ===== Call function
		#if $func.ret_type.name != "void"
			#if $func.ret_type.is_enum
		int ret = (int)obj->${func.func_name}($arg_list);
			#else
		${func.ret_type.get_whole_name($generator)} ret = obj->${func.func_name}($arg_list);
			#end if
		Variant* retVar = new Variant();
		#if $func.ret_type.is_enum
		retVar->setValue<int>(ret);
		#else
		retVar->setValue<${func.ret_type.get_whole_name($generator)}>(ret);
		#end if
		cx->push(retVar);
		#else
		obj->${func.func_name}($arg_list);
		#end if
	}
		#set $arg_idx = $arg_idx + 1
	#end while

#end if
#end for
}
